#ifndef INCLUDE_BASE_TEXTRENDERCOMPONENT_HPP_
#define INCLUDE_BASE_TEXTRENDERCOMPONENT_HPP_

#include "base/RenderComponent.hpp"
#include "base/Resource.hpp"

class TextRenderComponent: public RenderComponent {
public:
	TextRenderComponent(GameObject& gameObject, SDLTextResource* text);

	virtual void render(SDL_Renderer* renderer) override;

protected:
	void renderText(SDL_Renderer* renderer, const std::string& additionalText);

private:
	SDLTextResource* mText;
};



#endif /* INCLUDE_BASE_TEXTRENDERCOMPONENT_HPP_ */
