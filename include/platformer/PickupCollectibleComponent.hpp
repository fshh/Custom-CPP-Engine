#ifndef INCLUDE_PLATFORMER_PICKUPCOLLECTIBLECOMPONENT_HPP_
#define INCLUDE_PLATFORMER_PICKUPCOLLECTIBLECOMPONENT_HPP_

#include "base/RemoveOnCollideComponent.hpp"
#include "base/Resource.hpp"

class PickupCollectibleComponent: public RemoveOnCollideComponent {
public:
	PickupCollectibleComponent(GameObject& gameObject, int tag, SDLMixChunkResource* pickupSound);

	void collision(Level& level, std::shared_ptr<GameObject> obj);

	int count() const { return mCount; }

private:
	int mCount;
	SDLMixChunkResource* mPickupSound;
};


#endif /* INCLUDE_PLATFORMER_PICKUPCOLLECTIBLECOMPONENT_HPP_ */
