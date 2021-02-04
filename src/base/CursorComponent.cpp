#include "base/CursorComponent.hpp"
#include "base/GameObject.hpp"

CursorComponent::CursorComponent(GameObject& gameObject):
	GenericComponent(gameObject)
{
	SDL_ShowCursor(SDL_DISABLE);
}

void
CursorComponent::update(Level& level)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	GameObject& gameObject = getGameObject();
	gameObject.setX(x - (gameObject.w() / 2));
	gameObject.setY(y - (gameObject.h() / 2));
}


