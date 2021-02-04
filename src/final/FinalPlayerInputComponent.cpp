#include "base/InputManager.hpp"
#include "final/FinalPlayerInputComponent.hpp"
#include "base/GetResourcePath.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Timer.hpp"
#include <cmath>

FinalPlayerInputComponent::FinalPlayerInputComponent(GameObject& _gameObject, float _speed,
		float _dashSpeed, float _dashDistance, float _dashCooldown,
		std::shared_ptr<SpriteSheetRenderComponent> _renderComponent,
		std::shared_ptr<FinalHealthComponent> _healthComponent,
		std::shared_ptr<AnimatorComponent> _animatorComponent):
	GenericComponent(_gameObject), speed(_speed), dashSpeed(_dashSpeed), dashDistance(_dashDistance), dashCooldown(_dashCooldown),
	dashVector(0.0f, 0.0f), dashTimeRemaining(0.0f), dashCooldownRemaining(0.0f),
	renderComponent(_renderComponent), healthComponent(_healthComponent), animatorComponent(_animatorComponent)
{
}

void
FinalPlayerInputComponent::update(Level& level) {
	const InputManager& inputManager = InputManager::getInstance();
	bool left = inputManager.isKeyDown(SDLK_LEFT) || inputManager.isKeyDown(SDLK_a);
	bool right = inputManager.isKeyDown(SDLK_RIGHT) || inputManager.isKeyDown(SDLK_d);
	bool up = inputManager.isKeyDown(SDLK_UP) || inputManager.isKeyDown(SDLK_w);
	bool down = inputManager.isKeyDown(SDLK_DOWN) || inputManager.isKeyDown(SDLK_s);
	bool dash = inputManager.isKeyPressed(SDLK_SPACE);

	GameObject& gameObject = getGameObject();
	std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Update sprite flip
	renderComponent->setFlipX(mouseX < gameObject.x() + (gameObject.w() / 2));

	// Update animation states
	if (left != right || up != down) {
		animatorComponent->setState("run");
	}
	else {
		animatorComponent->setState("idle");
	}

	// If currently dashing, ignore movement inputs
	if (dashTimeRemaining > 0.0f) {
		// Track dash time remaining
		dashTimeRemaining = std::max(0.0f, dashTimeRemaining - Timer::deltaTime());

		// Rotate sprite while dashing
		float dashDuration = dashDistance / dashSpeed;
		double t = 1.0 - (dashTimeRemaining / dashDuration);
		double rot = TinyMath::lerp(0.0, (dashVector.x >= 0.0f ? 1.0 : -1.0) * 360.0, t);
		renderComponent->setRotation(rot);

		// Maintain dash velocity
		pc->setVx(dashVector.x);
		pc->setVy(dashVector.y);

		// If dash is over...
		if (dashTimeRemaining == 0.0f) {
			// Start dash cooldown
			dashCooldownRemaining = dashCooldown;
			// Make player vulnerable
			healthComponent->setInvulnerable(false);
			// Reset sprite rotation
			renderComponent->setRotation(0.0);
			// Reset dash velocity
			dashVector.x = 0.0f;
			dashVector.y = 0.0f;
		}
	}
	// Accept movement inputs
	else {
		TinyMath::Vector2D<float> moveVector(0.0f, 0.0f);
		if (left && !right) {
			moveVector.x = -1.0f;
		} else if (!left && right) {
			moveVector.x = 1.0f;
		}

		if(up && !down) {
			moveVector.y = -1.0f;
		}
		else if(!up && down) {
			moveVector.y = 1.0f;
		}

		// Ensure that player does not move faster when moving diagonally
		moveVector = TinyMath::Normalize(moveVector) * speed * Timer::deltaTime();
		pc->setVx(moveVector.x);
		pc->setVy(moveVector.y);

		// If player hits dash input and dash is not on cooldown, start dash
		if (dash && dashCooldownRemaining == 0.0f) {
			// Set dash duration
			dashTimeRemaining = dashDistance / dashSpeed;

			// Make player invulnerable
			healthComponent->setInvulnerable(true);

			// If player is not moving, dash in direction of crosshair
			if (pc->vx() == 0.0f && pc->vy() == 0.0f) {
				dashVector.x = mouseX - (gameObject.x() + gameObject.w() / 2);
				dashVector.y = mouseY - (gameObject.y() + gameObject.h() / 2);
			}
			// If player is moving, dash in movement direction
			else {
				dashVector.x = pc->vx();
				dashVector.y = pc->vy();
			}
			dashVector = TinyMath::Normalize(dashVector) * dashSpeed * Timer::deltaTime();
			pc->setVx(dashVector.x);
			pc->setVy(dashVector.y);
		}
	}

	// If dash is on cooldown, update remaining cooldown
	if (dashCooldownRemaining != 0.0f) {
		dashCooldownRemaining = std::max(0.0f, dashCooldownRemaining - Timer::deltaTime());
	}
}
