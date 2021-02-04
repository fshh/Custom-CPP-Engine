#ifndef INCLUDE_BREAKOUT_BREAKOUTSCORE_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTSCORE_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "breakout/BreakoutScoreComponent.hpp"

class BreakoutScore: public GameObject {
public:
	BreakoutScore(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<BreakoutScoreComponent> tracker);
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTSCORE_HPP_ */
