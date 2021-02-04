#include "platformer/PlatformerLevel.hpp"
#include "base/ResourceManager.hpp"
#include "base/AudioManager.hpp"
#include "base/GetResourcePath.hpp"
#include "base/Localization.hpp"
#include "platformer/Block.hpp"
#include "platformer/PlatformerPlayer.hpp"
#include "platformer/PlatformerGoal.hpp"
#include "platformer/PlatformerCollectible.hpp"
#include "platformer/PlatformerEnemy.hpp"
#include "platformer/PlatformerBackground.hpp"
#include "platformer/PickupCollectibleComponent.hpp"
#include "platformer/PlatformerScore.hpp"
#include <string>
#include <algorithm>
#include <fstream>

PlatformerLevel::PlatformerLevel(const std::string& jsonPath):
	Level(jsonPath) {}

void
PlatformerLevel::render(SDL_Renderer* renderer)
{
	Level::render(renderer);
	if (isWon()) { winText->render(renderer); }
	else if (isLost()) { loseText->render(renderer); }
}

void PlatformerLevel::load() {
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;
	file.close();

	const float SIZE = data["size"].asFloat();
	const int TAG_PLAYER = 1;
	const int TAG_GOAL = 2;
	const int TAG_TERRAIN = 3;
	const int TAG_ENEMY = 4;
	const int TAG_COLLECTIBLE = 5;
	const int TAG_BACKGROUND = 6;
	const int TAG_TEXT = 7;

	{
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
	}

	{
		// SPRITES
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
	}

	{
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

		winSound = ResourceManager::get<SDLMixChunkResource>(data["winSound"].asString());
		loseSound = ResourceManager::get<SDLMixChunkResource>(data["loseSound"].asString());
	}

	{
		// MUSIC
		const Json::Value musicData = data["music"];
		SDLMixMusicResource* music = new SDLMixMusicResource(
				musicData["name"].asString(),
				getResourcePath("sounds") + musicData["file"].asString());
		ResourceManager::add<SDLMixMusicResource>(music);
		AudioManager::playMusic(music);
	}

	SDLSpriteSheetResource* blockSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(data["blocks"]["spriteSheet"].asString());
	{
		// BLOCKS
		const Json::Value rows = data["blocks"]["grid"];
		// track height of the level
		height = rows.size() * SIZE;
		width = strlen(rows[0].asCString()) * SIZE;

		// BACKGROUND
		addObject(std::make_shared<PlatformerBackground>(
				width,
				height,
				TAG_BACKGROUND,
				blockSpriteSheet,
				25));

		for (unsigned int ii = 0; ii < rows.size(); ++ii) {
			const char* cols = rows[ii].asCString();
			for (unsigned int jj = 0; jj < strlen(cols); ++jj) {
				// construct block object from blockType
				const char blockType = cols[jj];
				if (blockType == 'g') {
					addObject(std::make_shared<PlatformerBlockGrass>(jj * SIZE, ii * SIZE, SIZE, TAG_TERRAIN, blockSpriteSheet));
				}
				else if (blockType == 's') {
					addObject(std::make_shared<PlatformerBlockStone>(jj * SIZE, ii * SIZE, SIZE, TAG_TERRAIN, blockSpriteSheet));
				}
			}
		}
	}

	std::shared_ptr<PickupCollectibleComponent> scoreTracker;
	{
		// PLAYER
		const Json::Value playerData = data["player"];
		SDLSpriteSheetResource* playerSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(playerData["spriteSheet"].asString());
		SDLMixChunkResource* jumpSound = ResourceManager::get<SDLMixChunkResource>(playerData["jumpSound"].asString());
		SDLMixChunkResource* collectibleSound = ResourceManager::get<SDLMixChunkResource>(playerData["pickupCollectibleSound"].asString());
		// load player values
		std::shared_ptr<PlatformerPlayer> player = std::make_shared<PlatformerPlayer>(
			playerData.get("x", 0).asFloat(),
			playerData.get("y", 0).asFloat(),
			SIZE - 4,
			SIZE,
			TAG_PLAYER,
			TAG_GOAL,
			TAG_COLLECTIBLE,
			playerData.get("speed", 200).asFloat(),
			playerData.get("jumpSpeed", 1000).asFloat(),
			playerData.get("gravity", 50).asFloat(),
			playerSpriteSheet,
			jumpSound,
			collectibleSound);
		addObject(player);

		scoreTracker = player->getGenericComponent<PickupCollectibleComponent>();
	}

	{
		// GOAL
		Json::Value goalData = data["goal"];
		std::shared_ptr<PlatformerGoal> goal = std::make_shared<PlatformerGoal>(
			goalData.get("x", 0).asFloat(),
			goalData.get("y", 0).asFloat(),
			SIZE,
			TAG_GOAL
		);
		addObject(goal);
	}

	{
		// COLLECTIBLES - MIGHT NEED TO IMPLEMENT TRACKING HOW MANY IF WE WANT TO REQUIRE A CERTAIN AMOUNT TO CLEAR LEVEL
		Json::Value collectiblesData = data["collectibles"];
		for (unsigned int i = 0; i < collectiblesData.size(); i++) {
			Json::Value collectibleData = collectiblesData[i];
			std::shared_ptr<PlatformerCollectible> collectible = std::make_shared<PlatformerCollectible>(
				collectibleData.get("x", 0).asFloat(),
				collectibleData.get("y", 0).asFloat(),
				SIZE,
				TAG_COLLECTIBLE,
				blockSpriteSheet,
				217
			);
			addObject(collectible);
		}
	}

	{
		// ENEMIES
		Json::Value enemiesData = data["enemies"];
		for (unsigned int i = 0; i < enemiesData.size(); i++) {;
			Json::Value enemyData = enemiesData[i];
			std::shared_ptr<PlatformerEnemy> enemy = std::make_shared<PlatformerEnemy>(
				enemyData.get("x", 0).asFloat(),
				enemyData.get("y", 0).asFloat(),
				enemyData.get("x", 0).asFloat() + 8 * SIZE,
				enemyData.get("y", 0).asFloat(),
				SIZE,
				TAG_ENEMY,
				TAG_PLAYER
			);
			addObject(enemy);
		}
	}

	{
		// SCORE
		Json::Value scoreData = data["score"];
		SDLTextResource* scoreText = ResourceManager::get<SDLTextResource>(scoreData["text"].asString());
		std::shared_ptr<PlatformerScore> score = std::make_shared<PlatformerScore>(
				scoreData["x"].asInt(),
				scoreData["y"].asInt(),
				TAG_TEXT,
				scoreText,
				scoreTracker);
		addObject(score);
	}

	{
		// WIN TEXT
		Json::Value winTextData = data["winText"];
		SDLTextResource* winTextResource = ResourceManager::get<SDLTextResource>(winTextData["text"].asString());
		std::shared_ptr<TextObject> winTextObj = std::make_shared<TextObject>(
				winTextData["x"].asInt(),
				winTextData["y"].asInt(),
				TAG_TEXT,
				winTextResource);
		winText = winTextObj;
	}

	{
		// LOSE TEXT
		Json::Value loseTextData = data["loseText"];
		SDLTextResource* loseTextResource = ResourceManager::get<SDLTextResource>(loseTextData["text"].asString());
		std::shared_ptr<TextObject> loseTextObj = std::make_shared<TextObject>(
				loseTextData["x"].asInt(),
				loseTextData["y"].asInt(),
				TAG_TEXT,
				loseTextResource);
		loseText = loseTextObj;
	}
}

