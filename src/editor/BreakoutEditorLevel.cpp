#include "editor/BreakoutEditorLevel.hpp"
#include "editor/EditorInput.hpp"
#include "base/GetResourcePath.hpp"
#include <fstream>

BreakoutEditorLevel::BreakoutEditorLevel(const std::string& jsonPath): EditorLevel(jsonPath) {}

void BreakoutEditorLevel::load() {
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;

	lastSaved = data;

	size = data["size"].asFloat();

	// SPRITES
	const Json::Value sprites = data["sprites"];
	for (unsigned int ii = 0; ii < sprites.size(); ++ii) {
		Json::Value spriteData = sprites[ii];
		if (ResourceManager::get<SDLTextureResource>(spriteData["name"].asString())) { continue; }
		ResourceManager::add<SDLTextureResource>(new SDLTextureResource(spriteData["name"].asString(), getResourcePath("sprites") + spriteData["file"].asString()));
	}

	// BLOCKS
	SDLTextureResource* blockSprite = ResourceManager::get<SDLTextureResource>(data["blocks"]["sprite"].asString());
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
			if (blockType == 'x') {
				block = std::make_shared<SpriteEditorObject>(jj * size, ii * size, size, ObjectType::BLOCK, blockSprite);
			}
			else {
				block = std::make_shared<RectEditorObject>(jj * size, ii * size, size, ObjectType::EMPTY, 0xFF, 0xFF, 0xFF);
			}
			addObject(block);
		}
	}

	addObject(std::make_shared<EditorInput>(GameType::BREAKOUT));
}

std::shared_ptr<EditorObject> BreakoutEditorLevel::addEditorObject(float x, float y, ObjectType type, bool cursor) {
	std::shared_ptr<EditorObject> obj;
	if (type == ObjectType::BLOCK) {
		SDLTextureResource* blockSprite = ResourceManager::get<SDLTextureResource>(lastSaved["blocks"]["sprite"].asString());
		obj = std::make_shared<SpriteEditorObject>(x, y, size, ObjectType::BLOCK, blockSprite);
	}
	else if (type == ObjectType::EMPTY) {
		obj = std::make_shared<RectEditorObject>(x, y, size, ObjectType::EMPTY, 0xFF, 0xFF, 0xFF);
	}
	else {
		std::cout << "Trying to add unsupported ObjectType" << std::endl;
		return nullptr;
	}
	addObject(obj);
	return obj;
}

void BreakoutEditorLevel::save(std::shared_ptr<EditorObject> dontSave) {
	std::cout << "Saving" << std::endl;

	Json::Value blockgrid = lastSaved["blocks"]["grid"];

	// Initialize empty grid
	for (unsigned int i = 0; i < blockgrid.size(); i++) {
		blockgrid[i] = std::string(strlen(blockgrid[i].asCString()), ' ');
	}

	for (std::shared_ptr<GameObject> gameObj : objects) {
		std::shared_ptr<EditorObject> obj = std::dynamic_pointer_cast<EditorObject>(gameObj);
		if (!obj || obj == dontSave) {
			continue;
		}
		if (obj->getObjectType() == ObjectType::BLOCK) {
			char* row = const_cast<char*>(blockgrid[(int)(obj->y() / size)].asCString());
			row[(int)(obj->x() / size)] = 'x';
			blockgrid[(int)(obj->y() / size)] = row;
		}
	}

	lastSaved["blocks"]["grid"] = blockgrid;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "  ";

	std::ofstream file(getDataPath(), std::ofstream::out);
	file << Json::writeString(builder, lastSaved);
	file.close();
}
