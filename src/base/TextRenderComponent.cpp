#include "base/TextRenderComponent.hpp"
#include "base/Localization.hpp"
#include "base/GameObject.hpp"

TextRenderComponent::TextRenderComponent(GameObject& gameObject, SDLTextResource* text):
	RenderComponent(gameObject),
	mText(text)
{
}

void
TextRenderComponent::render(SDL_Renderer* renderer)
{
	renderText(renderer, "");
}

void
TextRenderComponent::renderText(SDL_Renderer* renderer, const std::string& additionalText)
{
	mText->loadAdditionalText(additionalText);

	const GameObject & gameObject = getGameObject();

	SDL_Rect dst { int(gameObject.x()), int(gameObject.y()), mText->w(), mText->h() };
	SDL_RenderCopy(renderer, mText->getTexture(), NULL, &dst);
}


