#ifndef INCLUDE_FINAL_FINALHEALTHBAR_HPP_
#define INCLUDE_FINAL_FINALHEALTHBAR_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "final/FinalHealthComponent.hpp"

class FinalHealthBar: public GameObject {
public:
	FinalHealthBar(float x, float y, float w, float h, int tag, SDLTextureResource* sprite, std::shared_ptr<FinalHealthComponent> healthTracker);
};



#endif /* INCLUDE_FINAL_FINALHEALTHBAR_HPP_ */
