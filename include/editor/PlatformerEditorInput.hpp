#ifndef INCLUDE_EDITOR_PLATFORMEREDITORINPUT_HPP_
#define INCLUDE_EDITOR_PLATFORMEREDITORINPUT_HPP_

#include "base/Level.hpp"
#include "editor/EditorInput.hpp"
#include "editor/EditorObject.hpp"

//! \brief A component that handles the input for the level editor.
class PlatformerEditorInputComponent : public EditorInputComponent {
public:
	PlatformerEditorInputComponent(GameObject& _gameObject):
		EditorInputComponent(_gameObject)
	{
		currType = ObjectType::SKY;
		cursor = nullptr;
	}

	ObjectType handleKey() override;
};

#endif /* INCLUDE_EDITOR_PLATFORMEREDITORINPUT_HPP_ */
