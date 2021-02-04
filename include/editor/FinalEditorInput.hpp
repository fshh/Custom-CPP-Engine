#ifndef INCLUDE_EDITOR_FINALEDITORINPUT_HPP_
#define INCLUDE_EDITOR_FINALEDITORINPUT_HPP_

#include "base/Level.hpp"
#include "editor/EditorInput.hpp"

//! \brief A component that handles the input for the level editor.
class FinalEditorInputComponent: public EditorInputComponent {
public:
	FinalEditorInputComponent(GameObject& _gameObject):
		EditorInputComponent(_gameObject)
	{
		currType = ObjectType::BLOCK;
		cursor = nullptr;
	}

	virtual ObjectType handleKey() override;

};

#endif /* INCLUDE_EDITOR_FINALEDITORINPUT_HPP_ */
