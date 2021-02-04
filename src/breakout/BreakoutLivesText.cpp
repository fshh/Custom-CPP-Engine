#include "breakout/BreakoutLivesText.hpp"
#include "breakout/BreakoutLivesRenderComponent.hpp"

BreakoutLivesText::BreakoutLivesText(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<BreakoutPlayerLives> tracker):
	GameObject(x, y, 0, 0, tag)
{
	setRenderComponent(std::make_shared<BreakoutLivesRenderComponent>(*this, text, tracker));
}

