#ifndef INCLUDE_EDITOR_EDITORLEVEL_HPP_
#define INCLUDE_EDITOR_EDITORLEVEL_HPP_

#include "editor/PlatformerEditorInput.hpp"
#include "editor/BreakoutEditorInput.hpp"
#include "editor/FinalEditorInput.hpp"
#include "editor/EditorObject.hpp"
#include "base/Level.hpp"

//! \brief A simple GameObject that contains a EditorInput component.
class EditorInput : public GameObject {
public:
	EditorInput(GameType game) : GameObject(0,0,0,0,TAG_EDITOR) {
		if (game == GameType::PLATFORMER){
			addGenericComponent(std::make_shared<PlatformerEditorInputComponent>(*this));
		}
		else if (game == GameType::BREAKOUT){
			addGenericComponent(std::make_shared<BreakoutEditorInputComponent>(*this));
		}
		else if (game == GameType::BONETHRONE) {
			addGenericComponent(std::make_shared<FinalEditorInputComponent>(*this));
		}
	}
};


//! \brief A representation of the level being edited.
class EditorLevel: public Level {
public:
	EditorLevel(const std::string& jsonPath): Level(jsonPath) { size = 0; }
	virtual ~EditorLevel() {}

	virtual void load() override = 0;

	//! \brief Adds in an editor object of the given type at the given coordinates.
	//! Returns a shared pointer to the EditorObject just added to the level.
	virtual std::shared_ptr<EditorObject> addEditorObject(float x, float y, ObjectType type, bool cursor = false) = 0;

	//! \brief Returns the size of the level.
	int getSize() { return size; };

	//! \brief Saves out the current state of the level to the original json file.
	virtual void save(std::shared_ptr<EditorObject> dontSave) = 0;

protected:
	Json::Value lastSaved;

	int size;
};


#endif /* INCLUDE_EDITOR_EDITORLEVEL_HPP_ */
