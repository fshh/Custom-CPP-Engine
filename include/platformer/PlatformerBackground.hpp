#ifndef INCLUDE_PLATFORMER_PLATFORMERBACKGROUND_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERBACKGROUND_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class PlatformerBackground: public GameObject {
public:
	PlatformerBackground(float width, float height, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID);
};



#endif /* INCLUDE_PLATFORMER_PLATFORMERBACKGROUND_HPP_ */
