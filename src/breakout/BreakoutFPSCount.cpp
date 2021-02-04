#include "breakout/BreakoutFPSCount.hpp"
#include "breakout/BreakoutFPSRendererComponent.hpp"

BreakoutFPSCount::BreakoutFPSCount(float x, float y, int tag, SDLTextResource* text):
		TextObject(x, y, tag, text)
{
	setRenderComponent(std::make_shared<BreakoutFPSRendererComponent>(*this, text));
}
