#ifndef INCLUDE_BREAKOUT_BREAKOUTBLOCK_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTBLOCK_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class BreakoutBlock: public GameObject {
public:
	BreakoutBlock(float x, float y, float size, int tag, SDLTextureResource* sprite, int initialHealth, int ballTag);
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTBLOCK_HPP_ */
