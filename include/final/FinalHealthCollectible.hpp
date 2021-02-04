#ifndef INCLUDE_FINAL_FINALHEALTHCOLLECTIBLE_HPP_
#define INCLUDE_FINAL_FINALHEALTHCOLLECTIBLE_HPP_

#include "base/GameObject.hpp"
#include "base/SpriteSheetRenderComponent.hpp"

class FinalHealthCollectible: public GameObject {
public:
	FinalHealthCollectible(float x, float y, float size, int tag, int health, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID);
};

#endif /* INCLUDE_FINAL_FINALHEALTHCOLLECTIBLE_HPP_ */
