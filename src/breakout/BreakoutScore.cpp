#include "breakout/BreakoutScore.hpp"
#include "breakout/BreakoutScoreRenderComponent.hpp"

BreakoutScore::BreakoutScore(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<BreakoutScoreComponent> tracker):
		GameObject(x, y, 0, 0, tag)
{
	setRenderComponent(std::make_shared<BreakoutScoreRenderComponent>(*this, text, tracker));
}
