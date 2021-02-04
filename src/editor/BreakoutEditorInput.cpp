#include "base/InputManager.hpp"
#include "editor/BreakoutEditorInput.hpp"
#include <SDL.h>

ObjectType BreakoutEditorInputComponent::handleKey() {
	bool block = InputManager::getInstance().isKeyDown(SDLK_1);
	bool empty = InputManager::getInstance().isKeyDown(SDLK_2);

	if (block) {
		return ObjectType::BLOCK;
	} else if (empty) {
		return ObjectType::EMPTY;
	}
	return ObjectType::INVALID;
}
