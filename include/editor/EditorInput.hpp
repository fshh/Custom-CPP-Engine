#ifndef INCLUDE_EDITOR_EDITORINPUT_HPP_
#define INCLUDE_EDITOR_EDITORINPUT_HPP_

#include "editor/EditorObject.hpp"

enum class GameType {
	BREAKOUT = 0,
	PLATFORMER = 1,
	BONETHRONE = 2
};

//! \brief A component that handles the input for the level editor.
class EditorInputComponent : public GenericComponent {
public:
	EditorInputComponent(GameObject& _gameObject):
		GenericComponent(_gameObject)
	{
		currType = ObjectType::INVALID;
		cursor = nullptr;
		addedObj = nullptr;
	}

	//! \brief Handles the user input.
	virtual void update(Level& level) override;

	//! \brief Returns the ObjectType associated with a key press, INVALID otherwise
	virtual ObjectType handleKey() = 0;
protected:
	ObjectType currType;
	std::shared_ptr<EditorObject> cursor;

	std::shared_ptr<EditorObject> addedObj;
};

#endif /* INCLUDE_EDITOR_EDITORINPUT_HPP_ */
