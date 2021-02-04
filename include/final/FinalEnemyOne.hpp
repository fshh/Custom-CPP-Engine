#ifndef INCLUDE_FINAL_FINALENEMYONE_HPP_
#define INCLUDE_FINAL_FINALENEMYONE_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "base/AnimationState.hpp"

class FinalEnemyOne: public GameObject {
public:
	FinalEnemyOne(float x1, float y1, float x2, float y2, float size, std::weak_ptr<GameObject> player, int enemyOneTag, int health, float hurtCooldown,
			SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound, SDLSpriteSheetResource* spriteSheet,
			std::vector<AnimationState> animations);
};


#endif
