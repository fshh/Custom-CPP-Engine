#include "breakout/BreakoutFPSRendererComponent.hpp"

BreakoutFPSRendererComponent::BreakoutFPSRendererComponent(GameObject& gameObject, SDLTextResource* text):
		TextRenderComponent(gameObject, text)
{
}

void
BreakoutFPSRendererComponent::render(SDL_Renderer* renderer)
{
	const std::string additionalText = std::to_string(Timer::getAverageDeltaTime());
	renderText(renderer, additionalText);
}
