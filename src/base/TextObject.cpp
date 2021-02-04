#include "base/TextObject.hpp"
#include "base/TextRenderComponent.hpp"

TextObject::TextObject(float x, float y, int tag, SDLTextResource* text):
	GameObject(x, y, 0, 0, tag)
{
	setRenderComponent(std::make_shared<TextRenderComponent>(*this, text));
}


