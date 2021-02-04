#include "final/FinalAbstractGunComponent.hpp"
#include "base/InputManager.hpp"
#include "base/GameObject.hpp"

void FinalAbstractGunComponent::update(Level& level) {
	int x, y;
	if (SDL_GetMouseState(&x,&y) & SDL_BUTTON_LMASK) {
		const GameObject& gameObject = getGameObject();
		TinyMath::Vector2D<float> dir((float)x - (gameObject.x() + (gameObject.w() / 2)), (float)y - (gameObject.y() + (gameObject.h() / 2)));
		dir = TinyMath::Normalize(dir);
		shoot(level, dir);
	}
}
