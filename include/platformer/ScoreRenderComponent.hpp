#ifndef INCLUDE_PLATFORMER_SCORERENDERCOMPONENT_HPP_
#define INCLUDE_PLATFORMER_SCORERENDERCOMPONENT_HPP_

#include "base/TextRenderComponent.hpp"
#include "platformer/PickupCollectibleComponent.hpp"

class ScoreRenderComponent: public TextRenderComponent {
public:
	ScoreRenderComponent(GameObject& gameObject, SDLTextResource* text, std::shared_ptr<PickupCollectibleComponent> tracker);

	virtual void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<PickupCollectibleComponent> mTracker;
};



#endif /* INCLUDE_PLATFORMER_SCORERENDERCOMPONENT_HPP_ */
