#ifndef INCLUDE_BASE_TEXTOBJECT_HPP_
#define INCLUDE_BASE_TEXTOBJECT_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class TextObject: public GameObject {
public:
	TextObject(float x, float y, int tag, SDLTextResource* text);
};

#endif /* INCLUDE_PLATFORMER_TEXTOBJECT_HPP_ */
