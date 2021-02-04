#ifndef INCLUDE_BREAKOUT_BREAKOUTFPSCOUNT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTFPSCOUNT_HPP_

#include "base/TextObject.hpp"
#include "base/Resource.hpp"
#include "platformer/PickupCollectibleComponent.hpp"

class BreakoutFPSCount: public TextObject {
public:
	BreakoutFPSCount(float x, float y, int tag, SDLTextResource* text);
};



#endif /* INCLUDE_PLATFORMER_PLATFORMERSCORE_HPP_ */
