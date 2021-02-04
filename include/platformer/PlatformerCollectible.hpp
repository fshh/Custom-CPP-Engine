#ifndef INCLUDE_PLATFORMER_PLATFORMERCOLLECTIBLE_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERCOLLECTIBLE_HPP_

#include "base/GameObject.hpp"
#include "base/SpriteSheetRenderComponent.hpp"

class PlatformerCollectible: public GameObject {
public:
	PlatformerCollectible(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID);
};

#endif /* INCLUDE_PLATFORMER_PLATFORMERCOLLECTIBLE_HPP_ */
