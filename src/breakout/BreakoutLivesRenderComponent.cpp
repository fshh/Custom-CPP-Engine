#include "breakout/BreakoutLivesRenderComponent.hpp"


BreakoutLivesRenderComponent::BreakoutLivesRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<BreakoutPlayerLives> tracker):
	TextRenderComponent(gameObject, text), mTracker(tracker)
{
}

void
BreakoutLivesRenderComponent::render(SDL_Renderer* renderer)
{
	const std::string additionalText = std::to_string(mTracker->getLives());
	renderText(renderer, additionalText);
}


