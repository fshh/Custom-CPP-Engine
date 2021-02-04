#ifndef INCLUDE_BREAKOUT_BREAKOUTBALLPHYSICSCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTBALLPHYSICSCOMPONENT_HPP_

#include "base/PhysicsComponent.hpp"

class BreakoutBallPhysicsComponent: public PhysicsComponent {
public:
	BreakoutBallPhysicsComponent(GameObject& gameObject);

	void step(Level& level) override;
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTBALLPHYSICSCOMPONENT_HPP_ */
