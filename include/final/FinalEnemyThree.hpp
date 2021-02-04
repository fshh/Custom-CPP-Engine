#ifndef INCLUDE_FINAL_FINALENEMYTHREE_HPP_
#define INCLUDE_FINAL_FINALENEMYTHREE_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "base/AnimationState.hpp"

class FinalEnemyThree: public GameObject {
public:
	FinalEnemyThree(float x1, float y1, float size, std::weak_ptr<GameObject> player, int enemyThreeTag, int health, float hurtCooldown,
			SDLTextureResource* bulletSprite, SDLMixChunkResource* pistolSound, SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
			SDLSpriteSheetResource* spriteSheet, std::vector<AnimationState> animations);
};



#endif /* INCLUDE_FINAL_FINALENEMYTHREE_HPP_ */
