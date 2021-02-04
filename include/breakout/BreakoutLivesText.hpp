#ifndef INCLUDE_BREAKOUT_BREAKOUTLIVESTEXT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTLIVESTEXT_HPP_

#include "base/GameObject.hpp"
#include "breakout/BreakoutPlayerLives.hpp"
#include "base/Resource.hpp"

class BreakoutLivesText: public GameObject {
public:
	BreakoutLivesText(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<BreakoutPlayerLives> tracker);
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTLIVESTEXT_HPP_ */
