#ifndef INCLUDE_FINAL_FINALHEALTHBARRENDERCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALHEALTHBARRENDERCOMPONENT_HPP_

#include "base/SpriteRenderComponent.hpp"
#include "final/FinalHealthComponent.hpp"

class FinalHealthBarRenderComponent: public SpriteRenderComponent {
public:
	FinalHealthBarRenderComponent(GameObject& gameObject, SDLTextureResource* sprite, std::shared_ptr<FinalHealthComponent> healthTracker);

	void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<FinalHealthComponent> mHealthTracker;
};



#endif /* INCLUDE_FINAL_FINALHEALTHBARRENDERCOMPONENT_HPP_ */
