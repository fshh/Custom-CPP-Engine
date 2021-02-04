#include "final/FinalHealthBarRenderComponent.hpp"

FinalHealthBarRenderComponent::FinalHealthBarRenderComponent(GameObject& gameObject, SDLTextureResource* sprite, std::shared_ptr<FinalHealthComponent> healthTracker):
	SpriteRenderComponent(gameObject, sprite),
	mHealthTracker(healthTracker)
{
}

void
FinalHealthBarRenderComponent::render(SDL_Renderer* renderer)
{
  const GameObject & gameObject = getGameObject();
  SDL_Rect spriteRect = { 0, 0, int(sprite->w() * mHealthTracker->getHealthPercentage()), int(sprite->h()) };
  SDL_Rect worldRect = { int(gameObject.x()), int(gameObject.y()), int(gameObject.w() * mHealthTracker->getHealthPercentage()), int(gameObject.h()) };

	SDL_RenderCopy(renderer, sprite->getTexture(), &spriteRect, &worldRect);
}

