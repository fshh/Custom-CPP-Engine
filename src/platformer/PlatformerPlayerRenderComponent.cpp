#include "platformer/PlatformerPlayerRenderComponent.hpp"
#include <math.h>

PlatformerPlayerRenderComponent::PlatformerPlayerRenderComponent(GameObject& gameObject, float size, SDLSpriteSheetResource* _spriteSheet):
	SpriteSheetRenderComponent(gameObject, size, size, _spriteSheet, 8), oldX(gameObject.x()), oldY(gameObject.y())
{
}

void
PlatformerPlayerRenderComponent::render(SDL_Renderer* renderer) {
	GameObject& gameObject = getGameObject();

	float dx = gameObject.x() - oldX;
	float dy = gameObject.y() - oldY;

	oldX = gameObject.x();
	oldY = gameObject.y();

	enum PlayerSprite {
		IDLE_GROUND = 8,
		IDLE_JUMP = 9,
		IDLE_FALL = 10,
		RIGHT_GROUND = 0,
		RIGHT_JUMP = 11,
		RIGHT_FALL = 12,
		LEFT_GROUND = 4,
		LEFT_JUMP = 13,
		LEFT_FALL = 14
	};

	PlayerSprite id;
	// right
	if (dx > 0) {
		// if we moved less than 1 pixel up/down, we're probably grounded
		if (fabsf(dy) < 1) {
			id = RIGHT_GROUND;
		}
		else if (dy > 0) {
			id = RIGHT_FALL;
		}
		else {
			id = RIGHT_JUMP;
		}
	}
	// left
	else if (dx < 0) {
		// if we moved less than 1 pixel up/down, we're probably grounded
		if (fabsf(dy) < 1) {
			id = LEFT_GROUND;
		}
		else if (dy > 0) {
			id = LEFT_FALL;
		}
		else {
			id = LEFT_JUMP;
		}
	}
	// idle (forward)
	else {
		// if we moved less than 1 pixel up/down, we're probably grounded
		if (fabsf(dy) < 1) {
			id = IDLE_GROUND;
		}
		else if (dy > 0) {
			id = IDLE_FALL;
		}
		else {
			id = IDLE_JUMP;
		}
	}

	setSpriteID((unsigned int)id);
	SpriteSheetRenderComponent::render(renderer);
}
