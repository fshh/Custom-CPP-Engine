#include "base/InputManager.hpp"
#include "editor/FinalEditorInput.hpp"
#include <SDL.h>

ObjectType FinalEditorInputComponent::handleKey() {
	bool empty = InputManager::getInstance().isKeyDown(SDLK_1);
	bool block = InputManager::getInstance().isKeyDown(SDLK_2);
	bool health = InputManager::getInstance().isKeyDown(SDLK_3);
	bool player = InputManager::getInstance().isKeyDown(SDLK_4);
	bool goal = InputManager::getInstance().isKeyDown(SDLK_5);

	if (block) {
		return ObjectType::BLOCK;
	} else if (empty) {
		return ObjectType::EMPTY;
	} else if (health) {
		return ObjectType::HEALTH;
	} else if (player) {
		return ObjectType::PLAYER;
	} else if (goal) {
		return ObjectType::GOAL;
	}
	return ObjectType::INVALID;
}
