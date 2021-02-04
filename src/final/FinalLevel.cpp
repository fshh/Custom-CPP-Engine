#include "final/FinalLevel.hpp"
#include "base/ResourceManager.hpp"
#include "base/AudioManager.hpp"
#include "base/GetResourcePath.hpp"
#include "base/Localization.hpp"
#include "final/FinalPlayer.hpp"
#include "final/FinalEnemyOne.hpp"
#include "final/FinalEnemyTwo.hpp"
#include "final/FinalEnemyThree.hpp"
#include "final/FinalBlock.hpp"
#include "final/FinalHealthCollectible.hpp"
#include "final/FinalHealthComponent.hpp"
#include "final/FinalHealthHUD.hpp"
#include "final/FinalHealthBar.hpp"
#include "final/FinalCrosshair.hpp"
#include "final/FinalGoal.hpp"
#include "final/FinalPistolComponent.hpp"
#include "final/FinalShotgunComponent.hpp"
#include "final/FinalGunHUD.hpp"
#include "final/FinalGunManagerComponent.hpp"
#include "base/AnimationState.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>

FinalLevel::FinalLevel(const std::string& jsonPath):
	Level(jsonPath), enemyTag(-1), clearPercent(0.0f), initialEnemies(0), enemiesCleared(0) {}

void
FinalLevel::render(SDL_Renderer* renderer)
{
	Level::render(renderer);
	if (isWon()) { winText->render(renderer); }
	else if (isLost()) { loseText->render(renderer); }
}

void FinalLevel::initTags() {
	Tags::addTag("Player", 1);
	Tags::addTag("Goal", 2);
	Tags::addTag("Terrain", 3);
	Tags::addTag("Enemy", 4);
	Tags::addTag("Collectible", 5);
	Tags::addTag("UI", 6);
	Tags::addTag("Player_Bullet", 7);
	Tags::addTag("Enemy_Bullet", 8);
}

void
FinalLevel::removeObject(std::shared_ptr<GameObject> object) {
	if (object->tag() == enemyTag) {
		enemiesCleared++;
		float enemyPercent = (float)enemiesCleared / (float)initialEnemies;
		if (enemyPercent - clearPercent >= -0.001) {
			addObject(portal);
		}
	}
	Level::removeObject(object);
}


std::vector<AnimationState>
loadAnimations(Json::Value animations) {
	std::vector<AnimationState> states;
	for (unsigned int ii = 0; ii < animations.size(); ++ii) {
		Json::Value state = animations[ii];
		states.push_back(AnimationState(
				state["name"].asString(),
				state["beginID"].asInt(),
				state["endID"].asInt(),
				state["priority"].asInt(),
				state["loops"].asBool()));
	}
	return states;
}


void FinalLevel::load() {
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;
	file.close();

	const float SIZE = data["size"].asFloat();

	this->enemyTag = Tags::tagOf("Enemy");
	this->enemiesCleared = 0;
	this->initialEnemies = 0;

	// TEXT
	const Json::Value texts = data["text"];
	for (unsigned int ii = 0; ii < texts.size(); ++ii) {
		Json::Value textData = texts[ii];
		if (ResourceManager::get<SDLTextResource>(textData["name"].asString())) { continue; }

		Json::Value colorData = textData["color"];
		SDLTextResource* text = new SDLTextResource(
				textData["name"].asString(),
				getResourcePath() + Localization::fontFile,
				textData["tag"].asString(),
				SDL_Color{
					(unsigned char)colorData["r"].asUInt(), (unsigned char)colorData["g"].asUInt(),
					(unsigned char)colorData["b"].asUInt(), (unsigned char)colorData["a"].asUInt()
				},
				textData["size"].asInt());
		ResourceManager::add<SDLTextResource>(text);
	}

	// ANIMATIONS
	std::unordered_map<std::string, std::vector<AnimationState>> animationTable;
	const Json::Value animationSets = data["animations"];
	for (unsigned int ii = 0; ii < animationSets.size(); ++ii) {
		Json::Value animationSet = animationSets[ii];
		std::vector<AnimationState> states = loadAnimations(animationSet["states"]);
		animationTable.emplace(animationSet["name"].asString(), states);
	}

	// SOUNDS
	const Json::Value sounds = data["sounds"];
	for (unsigned int ii = 0; ii < sounds.size(); ++ii) {
		Json::Value soundData = sounds[ii];
		if (ResourceManager::get<SDLMixChunkResource>(soundData["name"].asString())) { continue; }

		SDLMixChunkResource* sound = new SDLMixChunkResource(
				soundData["name"].asString(),
				getResourcePath("sounds") + soundData["file"].asString());
		ResourceManager::add<SDLMixChunkResource>(sound);
	}

	this->winSound = ResourceManager::get<SDLMixChunkResource>(data["winSound"].asString());
	this->loseSound = nullptr;

	// MUSIC
	const Json::Value musicData = data["music"];
	SDLMixMusicResource* music = new SDLMixMusicResource(
			musicData["name"].asString(),
			getResourcePath("sounds") + musicData["file"].asString());
	ResourceManager::add<SDLMixMusicResource>(music);
	AudioManager::playMusic(music);

	// SPRITE SHEETS
	const Json::Value spriteSheets = data["spriteSheets"];
	for (unsigned int ii = 0; ii < spriteSheets.size(); ++ii) {
		Json::Value sheetData = spriteSheets[ii];
		if (ResourceManager::get<SDLSpriteSheetResource>(sheetData["name"].asString())) { continue; }

		SDLSpriteSheetResource* sheet = new SDLSpriteSheetResource(
				sheetData["name"].asString(),
				getResourcePath("sprites") + sheetData["file"].asString(),
				sheetData["spriteSize"].asInt());
		ResourceManager::add<SDLSpriteSheetResource>(sheet);
	}

	// SPRITES
	const Json::Value sprites = data["sprites"];
	for (unsigned int ii = 0; ii < sprites.size(); ++ii) {
		Json::Value spriteData = sprites[ii];
		if (ResourceManager::get<SDLTextureResource>(spriteData["name"].asString())) { continue; }

		SDLTextureResource* sheet = new SDLTextureResource(
				spriteData["name"].asString(),
				getResourcePath("sprites") + spriteData["file"].asString());
		ResourceManager::add<SDLTextureResource>(sheet);
	}

	SDLSpriteSheetResource* blockSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(data["blocks"]["spriteSheet"].asString());

	// BLOCKS (UNPASSABLE TERRAIN)
	const Json::Value rows = data["blocks"]["grid"];
	// track height of the level
	height = rows.size() * SIZE;
	for (unsigned int ii = 0; ii < rows.size(); ++ii) {
		const char* cols = rows[ii].asCString();
		// track width of the level
		width = std::max(width, (unsigned int)strlen(cols) * (unsigned int)SIZE);
		for (unsigned int jj = 0; jj < strlen(cols); ++jj) {
			// construct block object from blockType
			const char blockType = cols[jj];
			if (blockType == ' ') {
				addObject(std::make_shared<FinalBlockFloor>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet));

				// randomly add decorations
				if (rand() % 40 == 0) { addObject(std::make_shared<FinalBlockDecoration>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }

				// add borders to clean up walls
				bool wallAbove = ii > 0 && rows[ii - 1].asCString()[jj] == 'x';
				bool wallBelow = ii < rows.size() - 1 && rows[ii + 1].asCString()[jj] == 'x';
				bool wallToRight = jj < strlen(cols) - 1 && cols[jj + 1] == 'x';
				bool wallToLeft = jj > 0 && cols[jj - 1] == 'x';
				bool wallTopRightCorner = ii < rows.size() - 1 && jj < strlen(cols) - 1 && rows[ii - 1].asCString()[jj + 1] == 'x';
				bool wallTopLeftCorner = ii > 0 && jj > 0 && rows[ii - 1].asCString()[jj - 1] == 'x';
				if (wallAbove) { addObject(std::make_shared<FinalBlockWallBorderBottom>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
				if (wallBelow) { addObject(std::make_shared<FinalBlockWallBorderTop>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
				if (wallToRight) { addObject(std::make_shared<FinalBlockWallBorderLeft>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
				if (wallToLeft) { addObject(std::make_shared<FinalBlockWallBorderRight>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
				if (wallTopRightCorner && !wallBelow && !wallToRight) { addObject(std::make_shared<FinalBlockWallBorderBottomLeft>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
				if (wallTopLeftCorner && !wallAbove && !wallToLeft) { addObject(std::make_shared<FinalBlockWallBorderBottomRight>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet)); }
			}
			else if (blockType == 'x') {
				addObject(std::make_shared<FinalBlockWall>(jj * SIZE, ii * SIZE, SIZE, Tags::tagOf("Terrain"), blockSpriteSheet));
			}
		}
	}

	std::shared_ptr<FinalHealthComponent> healthTracker;
	std::shared_ptr<GunManagerComponent> gunManager;
	// PLAYER
	const Json::Value playerData = data["player"];
	SDLSpriteSheetResource* playerSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(playerData["spriteSheet"].asString());
	SDLMixChunkResource* collectibleSound = ResourceManager::get<SDLMixChunkResource>(playerData["pickupHealthSound"].asString());
	SDLMixChunkResource* hurtSound = ResourceManager::get<SDLMixChunkResource>(playerData["hurtSound"].asString());
	SDLMixChunkResource* deathSound = ResourceManager::get<SDLMixChunkResource>(playerData["deathSound"].asString());
	std::vector<std::shared_ptr<FinalAbstractGunComponent>> guns;
	std::vector<AnimationState> playerAnimations = animationTable.at(playerData["animations"].asString());
	// load player values
	std::shared_ptr<FinalPlayer> player = std::make_shared<FinalPlayer>(
		playerData.get("x", 0).asFloat(),
		playerData.get("y", 0).asFloat(),
		SIZE - 4,
		SIZE,
		Tags::tagOf("Player"),
		playerData.get("speed", 200).asFloat(),
		playerData.get("dashSpeed", 200).asFloat(),
		playerData.get("dashDistance", 200).asFloat(),
		playerData.get("dashCooldown", 200).asFloat(),
		playerData.get("health", 100).asFloat(),
		playerData.get("hurtCooldown", 0.5f).asFloat(),
		playerSpriteSheet,
		collectibleSound,
		guns,
		hurtSound,
		deathSound,
		playerAnimations);
	addObject(player);

	healthTracker = player->getGenericComponent<FinalHealthComponent>();
	gunManager = player->getGenericComponent<GunManagerComponent>();


	// Add the starting guns
	const Json::Value gunData = data["guns"];
	SDLTextureResource* pistolBulletSprite = ResourceManager::get<SDLTextureResource>(gunData["pistol"]["bulletSprite"].asString());
	SDLMixChunkResource* pistolSound = ResourceManager::get<SDLMixChunkResource>(gunData["pistol"]["shootingSound"].asString());
	SDLTextureResource* shotgunBulletSprite = ResourceManager::get<SDLTextureResource>(gunData["shotgun"]["bulletSprite"].asString());
	SDLMixChunkResource* shotgunSound = ResourceManager::get<SDLMixChunkResource>(gunData["shotgun"]["shootingSound"].asString());
	gunManager->addGun(GunType::PISTOL, Tags::tagOf("Player_Bullet"), pistolBulletSprite, pistolSound, gunData["pistol"]["hudSprite"].asString());
	gunManager->addGun(GunType::SHOTGUN, Tags::tagOf("Player_Bullet"), shotgunBulletSprite, shotgunSound, gunData["shotgun"]["hudSprite"].asString());

	// GOAL
	Json::Value goalData = data["goal"];
	SDLTextureResource* goalSprite = ResourceManager::get<SDLTextureResource>(goalData["sprite"].asString());
	std::shared_ptr<FinalGoal> goal = std::make_shared<FinalGoal>(
		goalData.get("x", 0).asFloat(),
		goalData.get("y", 0).asFloat(),
		SIZE,
		Tags::tagOf("Goal"),
		goalSprite
	);
	this->portal = goal;

	// COLLECTIBLES
	// TODO: Setup for different types of collectibles. For now, assumes all are health packs
	Json::Value collectiblesData = data["collectibles"];
	for (unsigned int i = 0; i < collectiblesData.size(); i++) {
		Json::Value collectibleData = collectiblesData[i];
		SDLSpriteSheetResource* collectibleSheet = ResourceManager::get<SDLSpriteSheetResource>(collectibleData["spriteSheet"].asString());
		std::shared_ptr<FinalHealthCollectible> collectible = std::make_shared<FinalHealthCollectible>( // float x, float y, float size, int tag, int health, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID
			collectibleData.get("x", 0).asFloat(),
			collectibleData.get("y", 0).asFloat(),
			collectibleSheet->getSpriteSize() * 2,
			Tags::tagOf("Collectible"),
			collectibleData.get("health", 10).asFloat(),
			collectibleSheet,
			collectibleData.get("spriteID", 0).asInt()
		);
		addObject(collectible);
	}

	// ENEMIES
	Json::Value enemiesData = data["enemies"];
	this->initialEnemies = enemiesData.size();
	for (unsigned int i = 0; i < enemiesData.size(); i++) {
		Json::Value enemyData = enemiesData[i];
		SDLSpriteSheetResource* enemySpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(enemyData["spriteSheet"].asString());
		SDLMixChunkResource* hurtSound = ResourceManager::get<SDLMixChunkResource>(enemyData["hurtSound"].asString());
		SDLMixChunkResource* deathSound = ResourceManager::get<SDLMixChunkResource>(enemyData["deathSound"].asString());
		SDLTextureResource* enemyBulletSprite = ResourceManager::get<SDLTextureResource>(enemyData["bulletSprite"].asString());
		SDLMixChunkResource* enemyGunSound = ResourceManager::get<SDLMixChunkResource>(enemyData["shootingSound"].asString());
		std::vector<AnimationState> enemyAnimations = animationTable.at(enemyData["animations"].asString());
		if (enemyData.get("type", 1) == 1) { // Create enemy of type 1
			std::shared_ptr<FinalEnemyOne> enemy = std::make_shared<FinalEnemyOne>(
				enemyData.get("x1", 0).asFloat(),
				enemyData.get("y1", 0).asFloat(),
				enemyData.get("x2", 0).asFloat(),
				enemyData.get("y2", 0).asFloat(),
				enemySpriteSheet->getSpriteSize(),
				player,
				Tags::tagOf("Enemy"),
				enemyData.get("health", 10).asFloat(),
				enemyData.get("hurtCooldown", 0.0f).asFloat(),
				hurtSound,
				deathSound,
				enemySpriteSheet,
				enemyAnimations
			);
			addObject(enemy);
		}
		if (enemyData.get("type", 2) == 2) { // Create enemy of type 2
			std::shared_ptr<FinalEnemyTwo> enemy = std::make_shared<FinalEnemyTwo>(
				enemyData.get("x1", 0).asFloat(),
				enemyData.get("y1", 0).asFloat(),
				enemySpriteSheet->getSpriteSize(),
				player,
				Tags::tagOf("Enemy"),
				enemyData.get("health", 10).asFloat(),
				enemyData.get("hurtCooldown", 0.0f).asFloat(),
				enemyBulletSprite,
				enemyGunSound,
				hurtSound,
				deathSound,
				enemySpriteSheet,
				enemyAnimations
			);
			addObject(enemy);
		}
		if (enemyData.get("type", 3) == 3) { // Create enemy of type 3
			std::shared_ptr<FinalEnemyThree> enemy = std::make_shared<FinalEnemyThree>(
				enemyData.get("x1", 0).asFloat(),
				enemyData.get("y1", 0).asFloat(),
				enemySpriteSheet->getSpriteSize(),
				player,
				Tags::tagOf("Enemy"),
				enemyData.get("health", 10).asFloat(),
				enemyData.get("hurtCooldown", 0.0f).asFloat(),
				enemyBulletSprite,
				enemyGunSound,
				hurtSound,
				deathSound,
				enemySpriteSheet,
				enemyAnimations
			);
			addObject(enemy);
		}
	}

	// WIN TEXT
	Json::Value winTextData = data["winText"];
	SDLTextResource* winTextResource = ResourceManager::get<SDLTextResource>(winTextData["text"].asString());
	std::shared_ptr<TextObject> winTextObj = std::make_shared<TextObject>(
			winTextData["x"].asInt(),
			winTextData["y"].asInt(),
			Tags::tagOf("UI"),
			winTextResource);
	this->winText = winTextObj;

	// LOSE TEXT
	Json::Value loseTextData = data["loseText"];
	SDLTextResource* loseTextResource = ResourceManager::get<SDLTextResource>(loseTextData["text"].asString());
	std::shared_ptr<TextObject> loseTextObj = std::make_shared<TextObject>(
			loseTextData["x"].asInt(),
			loseTextData["y"].asInt(),
			Tags::tagOf("UI"),
			loseTextResource);
	this->loseText = loseTextObj;

	// HEALTH HUD
	Json::Value healthHUDData = data["healthHUD"];
	SDLTextureResource* healthHUDTextureResource = ResourceManager::get<SDLTextureResource>(healthHUDData["sprite"].asString());
	std::shared_ptr<FinalHealthHUD> healthHUD = std::make_shared<FinalHealthHUD>(
			healthHUDData["x"].asInt(),
			healthHUDData["y"].asInt(),
			healthHUDData["w"].asInt(),
			healthHUDData["h"].asInt(),
			Tags::tagOf("UI"),
			healthHUDTextureResource);
	addObject(healthHUD);

	// HEALTH BAR
	Json::Value healthBarData = data["healthBar"];
	SDLTextureResource* healthBarTextureResource = ResourceManager::get<SDLTextureResource>(healthBarData["sprite"].asString());
	std::shared_ptr<FinalHealthBar> healthBar = std::make_shared<FinalHealthBar>(
			healthBarData["x"].asInt(),
			healthBarData["y"].asInt(),
			healthBarData["w"].asInt(),
			healthBarData["h"].asInt(),
			Tags::tagOf("UI"),
			healthBarTextureResource,
			healthTracker);
	addObject(healthBar);

	// GUN HUD
	Json::Value gunHUDData = data["gunHUD"];
	SDLTextureResource* gunHUDTextureResource = ResourceManager::get<SDLTextureResource>(gunHUDData["sprite"].asString());
	std::shared_ptr<FinalGunHUD> gunHUD = std::make_shared<FinalGunHUD>(
			gunHUDData["x"].asInt(),
			gunHUDData["y"].asInt(),
			gunHUDData["w"].asInt(),
			gunHUDData["h"].asInt(),
			Tags::tagOf("UI"),
			gunHUDTextureResource,
			gunManager);
	addObject(gunHUD);

	// CROSSHAIR
	Json::Value crosshairData = data["crosshair"];
	SDLTextureResource* crosshairTextureResource = ResourceManager::get<SDLTextureResource>(crosshairData["sprite"].asString());
	std::shared_ptr<FinalCrosshair> crosshair = std::make_shared<FinalCrosshair>(
			crosshairData["size"].asInt(),
			Tags::tagOf("UI"),
			crosshairTextureResource);
	addObject(crosshair);

	// CLEAR PERCENT
	this->clearPercent = data["clearPercent"].asFloat() / 100.0f;
}
