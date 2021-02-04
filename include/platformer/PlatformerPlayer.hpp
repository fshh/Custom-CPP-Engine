#ifndef INCLUDE_PLATFORMER_PLATFORMERPLAYER_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERPLAYER_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class PlatformerPlayer: public GameObject {
public:
	PlatformerPlayer(float x, float y, float width, float height, int playerTag, int goalTag, int collectibleTag,
			float speed, float jumpSpeed, float gravity, SDLSpriteSheetResource* spriteSheet,
			SDLMixChunkResource* jumpSound, SDLMixChunkResource* pickupCollectibleSound);
};

#endif /* INCLUDE_PLATFORMER_PLATFORMERPLAYER_HPP_ */
