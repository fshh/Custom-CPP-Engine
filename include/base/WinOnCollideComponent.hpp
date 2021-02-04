#ifndef INCLUDE_BASE_WINONCOLLIDECOMPONENT_HPP_
#define INCLUDE_BASE_WINONCOLLIDECOMPONENT_HPP_

#include "base/RemoveOnCollideComponent.hpp"

class WinOnCollideComponent: public RemoveOnCollideComponent {
public:
	WinOnCollideComponent(GameObject & gameObject, int tag);

	virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;
};



#endif /* INCLUDE_BASE_WINONCOLLIDECOMPONENT_HPP_ */
