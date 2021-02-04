#ifndef INCLUDE_FINAL_FINALHEALTHHUD_HPP_
#define INCLUDE_FINAL_FINALHEALTHHUD_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class FinalHealthHUD: public GameObject {
public:
	FinalHealthHUD(float x, float y, float w, float h, int tag, SDLTextureResource* sprite);
};



#endif /* INCLUDE_FINAL_FINALHEALTHHUD_HPP_ */
