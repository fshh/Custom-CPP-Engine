#include "base/InputManager.hpp"
#include "editor/PlatformerEditorInput.hpp"
#include <SDL.h>

ObjectType PlatformerEditorInputComponent::handleKey() {
	bool player = InputManager::getInstance().isKeyDown(SDLK_1);
	bool goal = InputManager::getInstance().isKeyDown(SDLK_2);
	bool collectible = InputManager::getInstance().isKeyDown(SDLK_3);
	bool enemy = InputManager::getInstance().isKeyDown(SDLK_4);
	bool sky = InputManager::getInstance().isKeyDown(SDLK_5);
	bool stone = InputManager::getInstance().isKeyDown(SDLK_6);
	bool grass = InputManager::getInstance().isKeyDown(SDLK_7);

	if (player) {
		return ObjectType::PLAYER;
	} else if (goal) {
		return ObjectType::GOAL;
	} else if (collectible) {
		return ObjectType::COLLECTIBLE;
	} else if (enemy) {
		return ObjectType::ENEMY;
	} else if (sky) {
		return ObjectType::SKY;
	} else if (stone) {
		return ObjectType::STONE;
	} else if (grass) {
		return ObjectType::GRASS;
	}
	return ObjectType::INVALID;
}
