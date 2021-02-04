#include "base/SpriteSheetRenderComponent.hpp"

SpriteSheetRenderComponent::SpriteSheetRenderComponent(GameObject & gameObject, float _width, float _height, SDLSpriteSheetResource* _spriteSheet, unsigned int _spriteID):
  RenderComponent(gameObject),
	width(_width),
	height(_height),
	spriteSheet(_spriteSheet),
	spriteID(_spriteID),
	flipX(false),
	angle(0.0)
{
}

void
SpriteSheetRenderComponent::render(SDL_Renderer * renderer)
{
  int spriteSize = spriteSheet->getSpriteSize();
  int widthInSprites = spriteSheet->w() / spriteSize;

  SDL_Rect spriteRect = {
  		((int)spriteID % widthInSprites) * spriteSize,
			((int)spriteID / widthInSprites) * spriteSize,
			spriteSize,
			spriteSize
  };

  const GameObject & gameObject = getGameObject();
  int xOffset = (width - int(gameObject.w())) / 2;
  int yOffset = (height - int(gameObject.h())) / 2;
  SDL_Rect worldRect = { int(gameObject.x()) - xOffset, int(gameObject.y()) - yOffset, int(width), int(height) };
  SDL_RendererFlip flip = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_RenderCopyEx(renderer, spriteSheet->getTexture(), &spriteRect, &worldRect, angle, NULL, flip);
}

