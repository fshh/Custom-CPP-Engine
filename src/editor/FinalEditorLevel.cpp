#include "editor/FinalEditorLevel.hpp"

#include "base/SpriteSheetRenderComponent.hpp"
#include "base/RectRenderComponent.hpp"
#include "base/GetResourcePath.hpp"
#include "base/Resource.hpp"
#include "editor/EditorInput.hpp"
#include <iostream>
#include <fstream>

FinalEditorLevel::FinalEditorLevel(const std::string& jsonPath):
	EditorLevel(jsonPath) {}

void FinalEditorLevel::load() {
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;
	file.close();

	lastSaved = data;

	size = data["size"].asFloat();

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

	blockSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(data["blocks"]["spriteSheet"].asString());

	// BLOCKS (UNPASSABLE TERRAIN)
	const Json::Value rows = data["blocks"]["grid"];
	// track height of the level
	height = rows.size() * size;
	for (unsigned int ii = 0; ii < rows.size(); ++ii) {
		const char* cols = rows[ii].asCString();
		// track width of the level
		width = std::max(width, (unsigned int)strlen(cols) * (unsigned int)size);
		for (unsigned int jj = 0; jj < strlen(cols); ++jj) {
			// construct block object from blockType
			const char blockType = cols[jj];
			if (blockType == ' ') {
				addObject(std::make_shared<SpriteSheetEditorObject>(jj * size, ii * size, size, ObjectType::EMPTY, blockSpriteSheet, 0));
			}
			else if (blockType == 'x') {
				addObject(std::make_shared<SpriteSheetEditorObject>(jj * size, ii * size, size, ObjectType::BLOCK, blockSpriteSheet, 5));
			}
		}
	}

	// PLAYER
	const Json::Value playerData = data["player"];
	playerSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(playerData["spriteSheet"].asString());
	// load player values
	player = std::make_shared<SpriteSheetEditorObject>(
		playerData.get("x", 0).asFloat(),
		playerData.get("y", 0).asFloat(),
		//size - 4,
		size,
		ObjectType::PLAYER,
		playerSpriteSheet,
		0);
	addObject(player);

	// COLLECTIBLES
	// TODO: Setup for different types of collectibles. For now, assumes all are health packs (with the same values)
	Json::Value collectiblesData = data["collectibles"];
	for (unsigned int i = 0; i < collectiblesData.size(); i++) {
		healthPickup = collectiblesData[i];
		collectibleSheet = ResourceManager::get<SDLSpriteSheetResource>(healthPickup["spriteSheet"].asString());
		std::shared_ptr<SpriteSheetEditorObject> collectible = std::make_shared<SpriteSheetEditorObject>(
			healthPickup.get("x", 0).asFloat(),
			healthPickup.get("y", 0).asFloat(),
			collectibleSheet->getSpriteSize() * 2,
			ObjectType::HEALTH,
			collectibleSheet,
			healthPickup.get("spriteID", 0).asInt()
		);
		addObject(collectible);
	}

	// GOAL
	Json::Value goalData = data["goal"];
	goalSprite = ResourceManager::get<SDLTextureResource>(goalData["sprite"].asString());
	goal = std::make_shared<SpriteEditorObject>(
		goalData.get("x", 0).asFloat(),
		goalData.get("y", 0).asFloat(),
		size,
		ObjectType::GOAL,
		goalSprite
	);
	addObject(goal);

	// ENEMIES
	/* TODO: Implement enemy patrol editing.
	Json::Value enemiesData = data["enemies"];
	for (unsigned int i = 0; i < enemiesData.size(); i++) {
		Json::Value enemyData = enemiesData[i];
		if (enemyData.get("type", 1) == 1) { // Create enemy of type 1
			std::shared_ptr<FinalEnemyOne> enemy = std::make_shared<FinalEnemyOne>( //float x1, float y1, float x2, float y2, float size, std::weak_ptr<GameObject> player, int enemyOneTag, int bulletTag, int health
				enemyData.get("x1", 0).asFloat(),
				enemyData.get("y1", 0).asFloat(),
				enemyData.get("x2", 0).asFloat(),
				enemyData.get("y2", 0).asFloat(),
				SIZE,
				player,
				TAG_ENEMY,
				TAG_BULLET,
				enemyData.get("health", 10).asFloat()
			);
			addObject(enemy);
		}
	}*/

	addObject(std::make_shared<EditorInput>(GameType::BONETHRONE));
}

std::shared_ptr<EditorObject> FinalEditorLevel::addEditorObject(float x, float y, ObjectType type, bool cursor) {
	std::shared_ptr<EditorObject> obj;
	switch(type) {
		case ObjectType::PLAYER:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, playerSpriteSheet, 0);
			if (!cursor){
				removeObject(player);
				player = obj;
			}
			break;
		case ObjectType::HEALTH:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, collectibleSheet, healthPickup.get("spriteID", 0).asInt());
			break;
		case ObjectType::EMPTY:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 0);
			break;
		case ObjectType::BLOCK:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 5);
			break;
		case ObjectType::GOAL:
			obj = std::make_shared<SpriteEditorObject>(x, y, size, type, goalSprite);
			if (!cursor){
				removeObject(goal);
				goal = obj;
			}
			break;
		default:
			std::cout << "Trying to add unsupported ObjectType" << std::endl;
			return nullptr;
	}
	addObject(obj);
	return obj;
}

void FinalEditorLevel::save(std::shared_ptr<EditorObject> dontSave) {
	std::cout << "Saving" << std::endl;
	Json::Value blockgrid = lastSaved["blocks"]["grid"];
	Json::Value player = lastSaved["player"];
	Json::Value collectibles; // Clear out the old list
	Json::Value enemies; // Clear out the old list

	// Initialize blocks to a level full of sky
	for (unsigned int i = 0; i < blockgrid.size(); i++) {
		blockgrid[i] = std::string(strlen(blockgrid[i].asCString()), ' ');
	}

	for (std::shared_ptr<GameObject> gameObj : objects) {
		std::shared_ptr<EditorObject> obj = std::dynamic_pointer_cast<EditorObject>(gameObj);
		if (!obj || obj == dontSave) {
			continue;
		}
		ObjectType type = obj->getObjectType();
		switch(type) {
			case ObjectType::PLAYER:
				// Just take this one if there are multiple
				player["x"] = obj->x();
				player["y"] = obj->y();
				break;
			case ObjectType::COLLECTIBLE:
			{ // Brackets for variable scope
				int next = collectibles.size();
				collectibles[next]["x"] = obj->x();
				collectibles[next]["y"] = obj->y();
				collectibles[next]["health"] = healthPickup["health"];
				collectibles[next]["spriteSheet"] = healthPickup["spriteSheet"];
				collectibles[next]["spriteID"] = healthPickup["spriteID"];
				break;
			}
			case ObjectType::BLOCK:
			{
				char* row = const_cast<char*>(blockgrid[(int)(obj->y() / size)].asCString());
				row[(int)(obj->x() / size)] = 'x';
				blockgrid[(int)(obj->y() / size)] = row;
				break;
			}
			default:
				break;// Grid is already full of sky
		}
	}

	lastSaved["blocks"]["grid"] = blockgrid;
	lastSaved["player"] = player;
	lastSaved["collectibles"] = collectibles;
	lastSaved["enemies"] = enemies;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";

	std::ofstream file(getDataPath(), std::ofstream::out);
	file << Json::writeString(builder, lastSaved);
	file.close();
}
