#ifndef INCLUDE_PLATFORMER_PLATFORMERSCORE_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERSCORE_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "platformer/PickupCollectibleComponent.hpp"

class PlatformerScore: public GameObject {
public:
	PlatformerScore(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<PickupCollectibleComponent> tracker);
};



#endif /* INCLUDE_PLATFORMER_PLATFORMERSCORE_HPP_ */
