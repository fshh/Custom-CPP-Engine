#include "editor/PlatformerEditorLevel.hpp"

#include "base/SpriteSheetRenderComponent.hpp"
#include "base/RectRenderComponent.hpp"
#include "base/GetResourcePath.hpp"
#include "base/Resource.hpp"
#include "editor/EditorInput.hpp"
#include <iostream>
#include <fstream>

PlatformerEditorLevel::PlatformerEditorLevel(const std::string& jsonPath):
	EditorLevel(jsonPath) {}

void PlatformerEditorLevel::load() {
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;
	file.close();

	lastSaved = data;

	size = data["size"].asFloat();

	// SPRITES
	const Json::Value spriteSheets = data["spriteSheets"];
	for (unsigned int ii = 0; ii < spriteSheets.size(); ++ii) {
		Json::Value sheetData = spriteSheets[ii];
		if (ResourceManager::get<SDLSpriteSheetResource>(sheetData["name"].asString())) { return; }

		SDLSpriteSheetResource* sheet = new SDLSpriteSheetResource(
				sheetData["name"].asString(),
				getResourcePath("sprites") + sheetData["file"].asString(),
				sheetData["spriteSize"].asInt());
		ResourceManager::add<SDLSpriteSheetResource>(sheet);
	}

	// BLOCKS
	blockSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(data["blocks"]["spriteSheet"].asString());
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
			std::shared_ptr<GameObject> block;
			if (blockType == 'g') {
				block = std::make_shared<SpriteSheetEditorObject>(jj * size, ii * size, size, ObjectType::GRASS, blockSpriteSheet, 97);
			}
			else if (blockType == 's') {
				block = std::make_shared<SpriteSheetEditorObject>(jj * size, ii * size, size, ObjectType::STONE, blockSpriteSheet, 1);
			}
			else {
				block = std::make_shared<SpriteSheetEditorObject>(jj * size, ii * size, size, ObjectType::SKY, blockSpriteSheet, 43);
			}
			addObject(block);
		}
	}

	// PLAYER
	const Json::Value playerData = data["player"];
	playerSpriteSheet = ResourceManager::get<SDLSpriteSheetResource>(playerData["spriteSheet"].asString());
	std::shared_ptr<GameObject> player = std::make_shared<SpriteSheetEditorObject>(
		playerData.get("x", 0).asFloat(),
		playerData.get("y", 0).asFloat(),
		size,
		ObjectType::PLAYER,
		playerSpriteSheet,
		8
	);
	addObject(player);

	// GOAL
	Json::Value goalData = data["goal"];
	std::shared_ptr<GameObject> goal = std::make_shared<RectEditorObject>(
		goalData.get("x", 0).asFloat(),
		goalData.get("y", 0).asFloat(),
		size,
		ObjectType::GOAL,
		0x99, 0x99, 0x00
	);
	addObject(goal);

	// COLLECTIBLES
	Json::Value collectiblesData = data["collectibles"];
	for (unsigned int i = 0; i < collectiblesData.size(); i++) {
		Json::Value collectibleData = collectiblesData[i];
		std::shared_ptr<GameObject> collectible = std::make_shared<SpriteSheetEditorObject>(
			collectibleData.get("x", 0).asFloat(),
			collectibleData.get("y", 0).asFloat(),
			size,
			ObjectType::COLLECTIBLE,
			blockSpriteSheet,
			217
		);
		addObject(collectible);
	}

	// ENEMIES
	Json::Value enemiesData = data["enemies"];
	for (unsigned int i = 0; i < enemiesData.size(); i++) {
		Json::Value enemyData = enemiesData[i];
		std::shared_ptr<GameObject> enemy = std::make_shared<RectEditorObject>(
			enemyData.get("x", 0).asFloat(),
			enemyData.get("y", 0).asFloat(),
			size,
			ObjectType::ENEMY,
			0x99, 0x00, 0x00
		);
		addObject(enemy);
	}

	addObject(std::make_shared<EditorInput>(GameType::PLATFORMER));
}

std::shared_ptr<EditorObject> PlatformerEditorLevel::addEditorObject(float x, float y, ObjectType type, bool cursor) {
	std::shared_ptr<EditorObject> obj;
	switch(type) {
		case ObjectType::PLAYER:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, playerSpriteSheet, 8);
			break;
		case ObjectType::GOAL:
			obj = std::make_shared<RectEditorObject>(x, y, size, type, 0x99, 0x99, 0x00);
			break;
		case ObjectType::COLLECTIBLE:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 217);
			break;
		case ObjectType::ENEMY:
			obj = std::make_shared<RectEditorObject>(x, y, size, type, 0x99, 0x00, 0x00);
			break;
		case ObjectType::SKY:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 43);
			break;
		case ObjectType::STONE:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 1);
			break;
		case ObjectType::GRASS:
			obj = std::make_shared<SpriteSheetEditorObject>(x, y, size, type, blockSpriteSheet, 97);
			break;
		default:
			std::cout << "Trying to add unsupported ObjectType" << std::endl;
			return nullptr;
	}
	addObject(obj);
	return obj;
}

void PlatformerEditorLevel::save(std::shared_ptr<EditorObject> dontSave) {
	std::cout << "Saving" << std::endl;
	Json::Value blockgrid = lastSaved["blocks"]["grid"];
	Json::Value player = lastSaved["player"];
	Json::Value goal = lastSaved["goal"];
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
			case ObjectType::GOAL:
				// Just take this one if there are multiple
				goal["x"] = obj->x();
				goal["y"] = obj->y();
				break;
			case ObjectType::COLLECTIBLE:
			{ // Brackets for variable scope
				int next = collectibles.size();
				collectibles[next]["x"] = obj->x();
				collectibles[next]["y"] = obj->y();
				break;
			}
			case ObjectType::ENEMY:
			{
				int next = enemies.size();
				enemies[next]["x"] = obj->x();
				enemies[next]["y"] = obj->y();
				break;
			}
			case ObjectType::STONE:
			{
				char* row = const_cast<char*>(blockgrid[(int)(obj->y() / size)].asCString());
				row[(int)(obj->x() / size)] = 's';
				blockgrid[(int)(obj->y() / size)] = row;
				break;
			}
			case ObjectType::GRASS:
			{
				char* row = const_cast<char*>(blockgrid[(int)(obj->y() / size)].asCString());
				row[(int)(obj->x() / size)] = 'g';
				blockgrid[(int)(obj->y() / size)] = row;
				break;
			}
			default:
				break;// Grid is already full of sky
		}
	}

	lastSaved["blocks"]["grid"] = blockgrid;
	lastSaved["player"] = player;
	lastSaved["goal"] = goal;
	lastSaved["collectibles"] = collectibles;
	lastSaved["enemies"] = enemies;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";

	std::ofstream file(getDataPath(), std::ofstream::out);
	file << Json::writeString(builder, lastSaved);
	file.close();
}
