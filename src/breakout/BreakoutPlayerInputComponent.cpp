/*
 * BreakoutPlayerInputComponent.cpp
 *
 *  Created on: Mar 30, 2020
 */
#include "breakout/BreakoutPlayerInputComponent.hpp"
#include "base/InputManager.hpp"
#include "base/GetResourcePath.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Timer.hpp"

BreakoutPlayerInputComponent::BreakoutPlayerInputComponent(GameObject& _gameObject, float _speed):
	GenericComponent(_gameObject), speed(_speed)
{
}

void
BreakoutPlayerInputComponent::update(Level& level) {
	bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
	bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);

	GameObject& gameObject = getGameObject();
	std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

	if (left && !right) {
		pc->setVx(-speed * Timer::deltaTime());
	} else if (!left && right) {
		pc->setVx(speed * Timer::deltaTime());
	} else {
		pc->setVx(0.0f);
	}
}







