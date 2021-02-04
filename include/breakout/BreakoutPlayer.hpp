#ifndef INCLUDE_BREAKOUT_BREAKOUTPLAYER_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTPLAYER_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class BreakoutPlayer: public GameObject {
public:
	BreakoutPlayer(float x, float y, float width, float height, int tag, SDLTextureResource* sprite, float speed = 200, int lives = 3);
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTPLAYER_HPP_ */
