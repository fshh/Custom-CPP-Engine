#ifndef INCLUDE_EDITOR_PLATFORMEREDITORLEVEL_HPP_
#define INCLUDE_EDITOR_PLATFORMEREDITORLEVEL_HPP_

#include "editor/EditorObject.hpp"
#include "editor/EditorLevel.hpp"
#include "base/ResourceManager.hpp"

class PlatformerEditorLevel : public EditorLevel {
public:
	PlatformerEditorLevel(const std::string& jsonPath);
	virtual ~PlatformerEditorLevel() {}

	void load() override;

	std::shared_ptr<EditorObject> addEditorObject(float x, float y, ObjectType type, bool cursor = false) override;

	void save(std::shared_ptr<EditorObject> dontSave) override;

private:
	SDLSpriteSheetResource* blockSpriteSheet;
	SDLSpriteSheetResource* playerSpriteSheet;
};


#endif /* INCLUDE_EDITOR_PLATFORMEREDITORLEVEL_HPP_ */
