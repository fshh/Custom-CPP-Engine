#ifndef INCLUDE_FINAL_FINALPLAYER_HPP_
#define INCLUDE_FINAL_FINALPLAYER_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "final/FinalAbstractGunComponent.hpp"
#include "base/AnimationState.hpp"
#include <vector>

//! \brief The player of Bone Throne.
class FinalPlayer : public GameObject {
public:

	FinalPlayer(float x, float y, float width, float height, int tag, float speed,
			float dashSpeed, float dashDistance, float dashCooldown,
			int health, float hurtCooldown,
			SDLSpriteSheetResource* spriteSheet, SDLMixChunkResource* pickupHealthSound,
			std::vector<std::shared_ptr<FinalAbstractGunComponent>> guns,
			SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
			std::vector<AnimationState> animations);
};

#endif /* INCLUDE_FINAL_FINALPLAYER_HPP_ */
