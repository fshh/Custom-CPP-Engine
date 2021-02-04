#ifndef INCLUDE_FINAL_FINALCROSSHAIR_HPP_
#define INCLUDE_FINAL_FINALCROSSHAIR_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class FinalCrosshair: public GameObject {
public:
	FinalCrosshair(float size, int tag, SDLTextureResource* sprite);
};



#endif /* INCLUDE_FINAL_FINALCROSSHAIR_HPP_ */
