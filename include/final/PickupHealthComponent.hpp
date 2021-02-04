#ifndef INCLUDE_FINAL_PICKUPHEALTHCOMPONENT_HPP_
#define INCLUDE_FINAL_PICKUPHEALTHCOMPONENT_HPP_

#include "base/RemoveOnCollideComponent.hpp"
#include "base/Resource.hpp"

class PickupHealthComponent: public RemoveOnCollideComponent {
public:
	PickupHealthComponent(GameObject& gameObject, int tag, SDLMixChunkResource* pickupSound);

	void collision(Level& level, std::shared_ptr<GameObject> obj);

private:
	SDLMixChunkResource* mPickupSound;
};



#endif /* INCLUDE_FINAL_PICKUPHEALTHCOMPONENT_HPP_ */
