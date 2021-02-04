#ifndef SRC_BREAKOUT_BREAKOUTBALL_HPP_
#define SRC_BREAKOUT_BREAKOUTBALL_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "breakout/BreakoutPlayerLives.hpp"

class BreakoutBall: public GameObject {
public:
	BreakoutBall(float x, float y, float diameter, int tag, SDLTextureResource* sprite, float speed, std::shared_ptr<BreakoutPlayerLives> livesTracker,
			int blockTag, int playerTag, SDLMixChunkResource* blockBounceSound, SDLMixChunkResource* paddleBounceSound, SDLMixChunkResource* loseLifeSound);
};



#endif /* SRC_BREAKOUT_BREAKOUTBALL_HPP_ */
