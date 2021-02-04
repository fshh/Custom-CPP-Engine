#ifndef INCLUDE_BREAKOUT_BREAKOUTPLAYERINPUTCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTPLAYERINPUTCOMPONENT_HPP_

#include "base/GenericComponent.hpp"

class BreakoutPlayerInputComponent: public GenericComponent {
public:
	BreakoutPlayerInputComponent(GameObject& _gameObject, float _speed);

	virtual void update(Level& level) override;

private:
	float speed;
};



#endif
