#include "platformer/ScoreRenderComponent.hpp"

ScoreRenderComponent::ScoreRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<PickupCollectibleComponent> tracker):
		TextRenderComponent(gameObject, text),
		mTracker(tracker)
{
}

void
ScoreRenderComponent::render(SDL_Renderer* renderer)
{
	const std::string additionalText = std::to_string(mTracker->count());
	renderText(renderer, additionalText);
}



