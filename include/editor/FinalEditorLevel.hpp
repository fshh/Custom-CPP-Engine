#ifndef INCLUDE_EDITOR_FINALEDITORLEVEL_HPP_
#define INCLUDE_EDITOR_FINALEDITORLEVEL_HPP_

#include "editor/EditorObject.hpp"
#include "editor/EditorLevel.hpp"
#include "base/ResourceManager.hpp"

class FinalEditorLevel : public EditorLevel {
public:
	FinalEditorLevel(const std::string& jsonPath);
	virtual ~FinalEditorLevel() {}

	void load() override;

	std::shared_ptr<EditorObject> addEditorObject(float x, float y, ObjectType type, bool cursor = false) override;

	void save(std::shared_ptr<EditorObject> dontSave) override;

private:
	SDLSpriteSheetResource* blockSpriteSheet;
	SDLSpriteSheetResource* playerSpriteSheet;
	SDLSpriteSheetResource* collectibleSheet;
	SDLTextureResource* goalSprite;

	std::shared_ptr<EditorObject> player;
	std::shared_ptr<EditorObject> goal;

	Json::Value healthPickup;
};

#endif /* INCLUDE_EDITOR_FINALEDITORLEVEL_HPP_ */
