#ifndef INCLUDE_BASE_LOSEONCOLLIDECOMPONENT_HPP_
#define INCLUDE_BASE_LOSEONCOLLIDECOMPONENT_HPP_

#include "base/RemoveOnCollideComponent.hpp"

class LoseOnCollideComponent: public RemoveOnCollideComponent {
public:
	LoseOnCollideComponent(GameObject & gameObject, int tag);

	virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;
};



#endif /* INCLUDE_BASE_LOSEONCOLLIDECOMPONENT_HPP_ */
