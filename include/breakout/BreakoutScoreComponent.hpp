#ifndef INCLUDE_BREAKOUT_BREAKOUTSCORECOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTSCORECOMPONENT_HPP_

#include "base/GenericComponent.hpp"

class BreakoutScoreComponent: public GenericComponent {
public:
	BreakoutScoreComponent(GameObject& gameObject): GenericComponent(gameObject), mScore(0) {}

	void incrementScore() { mScore++; }

	int getScore() { return mScore; }

private:

	int mScore;
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTSCORECOMPONENT_HPP_ */
