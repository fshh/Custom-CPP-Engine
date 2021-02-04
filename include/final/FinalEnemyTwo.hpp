#ifndef INCLUDE_FINAL_FINALENEMYTWO_HPP_
#define INCLUDE_FINAL_FINALENEMYTWO_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "base/AnimationState.hpp"

class FinalEnemyTwo: public GameObject {
public:
	FinalEnemyTwo(float x1, float y1, float size, std::weak_ptr<GameObject> player, int enemyTwoTag, int health, float hurtCooldown,
			SDLTextureResource* bulletSprite, SDLMixChunkResource* pistolSound, SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
			SDLSpriteSheetResource* spriteSheet, std::vector<AnimationState> animations);
};


#endif
