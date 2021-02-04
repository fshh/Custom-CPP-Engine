#ifndef INCLUDE_BREAKOUT_BREAKOUTSCORERENDERCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTSCORERENDERCOMPONENT_HPP_

#include "base/TextRenderComponent.hpp"
#include "breakout/BreakoutScoreComponent.hpp"

class BreakoutScoreRenderComponent: public TextRenderComponent {
public:
	BreakoutScoreRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<BreakoutScoreComponent> tracker);

	virtual void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<BreakoutScoreComponent> mTracker;
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTSCORERENDERCOMPONENT_HPP_ */
