#ifndef INCLUDE_BREAKOUT_BREAKOUTFPSRENDERERCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTFPSRENDERERCOMPONENT_HPP_

#include "base/TextRenderComponent.hpp"
#include "base/Timer.hpp"

class BreakoutFPSRendererComponent: public TextRenderComponent {
public:
	BreakoutFPSRendererComponent(GameObject& gameObject, SDLTextResource* text);

	virtual void render(SDL_Renderer* renderer) override;

private:
};



#endif /* INCLUDE_PLATFORMER_SCORERENDERCOMPONENT_HPP_ */
