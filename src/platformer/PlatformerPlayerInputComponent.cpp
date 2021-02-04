#include "platformer/PlatformerPlayerInputComponent.hpp"
#include "base/AudioManager.hpp"
#include "base/InputManager.hpp"
#include "base/ResourceManager.hpp"
#include "base/GetResourcePath.hpp"
#include "base/Timer.hpp"

PlatformerPlayerInputComponent::PlatformerPlayerInputComponent(GameObject& _gameObject, float _speed, float _jumpSpeed, float _gravity,
		SDLMixChunkResource* jumpSound):
	GenericComponent(_gameObject), speed(_speed), jumpSpeed(_jumpSpeed), gravity(_gravity), mJumpSound(jumpSound)
{
}

void
PlatformerPlayerInputComponent::update(Level& level) {
	bool left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
	bool right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
	bool jump = InputManager::getInstance().isKeyDown(SDLK_UP);

	GameObject& gameObject = getGameObject();
	std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

	if (left && !right) {
		pc->setVx(-speed * Timer::deltaTime());
	} else if (!left && right) {
		pc->setVx(speed * Timer::deltaTime());
	} else {
		pc->setVx(0.0f);
	}

	if (jump && pc->vy() >= 0.0f) {
		bool onGround = false;
		float groundedWindow = 2.0f;
		std::vector<std::shared_ptr<GameObject>> objects;
		if (level.getCollisions(gameObject.x() + 0.1f, gameObject.y() + gameObject.h() + groundedWindow, objects)) {
			for (auto obj : objects) {
				if (obj->physicsComponent()) {
					if (obj->physicsComponent()->isSolid()) {
						onGround = true;
						break;
					}
				}
			}
		}
		if (level.getCollisions(gameObject.x() + gameObject.w() - 0.1f, gameObject.y() + gameObject.h() + groundedWindow, objects)) {
			for (auto obj : objects) {
				if (obj->physicsComponent()) {
					if (obj->physicsComponent()->isSolid()) {
						onGround = true;
						break;
					}
				}
			}
		}
		if (onGround) {
			AudioManager::playSound(mJumpSound);
			pc->setVy(-jumpSpeed);
			return;
		}
	}

	pc->setVy(pc->vy() + gravity * Timer::deltaTime());
}

