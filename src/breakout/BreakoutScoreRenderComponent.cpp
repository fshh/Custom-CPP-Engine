#include "breakout/BreakoutScoreRenderComponent.hpp"

BreakoutScoreRenderComponent::BreakoutScoreRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<BreakoutScoreComponent> tracker):
		TextRenderComponent(gameObject, text),
		mTracker(tracker)
{
}

void
BreakoutScoreRenderComponent::render(SDL_Renderer* renderer)
{
	const std::string additionalText = std::to_string(mTracker->getScore());
	renderText(renderer, additionalText);
}
