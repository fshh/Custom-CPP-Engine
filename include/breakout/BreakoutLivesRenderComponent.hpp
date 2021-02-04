#ifndef INCLUDE_BREAKOUT_BREAKOUTLIVESRENDERCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTLIVESRENDERCOMPONENT_HPP_

#include "base/TextRenderComponent.hpp"
#include "breakout/BreakoutPlayerLives.hpp"

class BreakoutLivesRenderComponent: public TextRenderComponent {
public:
	BreakoutLivesRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<BreakoutPlayerLives> tracker);

	virtual void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<BreakoutPlayerLives> mTracker;
};


#endif /* INCLUDE_BREAKOUT_BREAKOUTLIVESRENDERCOMPONENT_HPP_ */
