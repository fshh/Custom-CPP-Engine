#include "base/SpriteRenderComponent.hpp"

SpriteRenderComponent::SpriteRenderComponent(GameObject & gameObject, SDLTextureResource* _sprite, double angle):
	RenderComponent(gameObject), sprite(_sprite), mAngle(angle)
{
}

void
SpriteRenderComponent::render(SDL_Renderer * renderer)
{
  const GameObject & gameObject = getGameObject();
  SDL_Rect worldRect = { int(gameObject.x()), int(gameObject.y()), int(gameObject.w()), int(gameObject.h()) };

  SDL_RenderCopyEx(renderer, sprite->getTexture(), NULL, &worldRect, mAngle, NULL, SDL_FLIP_NONE);
}


