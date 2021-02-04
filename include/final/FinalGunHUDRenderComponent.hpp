#ifndef INCLUDE_FINAL_FINALGUNHUDRENDERCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALGUNHUDRENDERCOMPONENT_HPP_

#include "base/SpriteRenderComponent.hpp"
#include "final/FinalGunManagerComponent.hpp"

class FinalGunHUDRenderComponent : public SpriteRenderComponent {
public:
	FinalGunHUDRenderComponent(GameObject & gameObject, SDLTextureResource* defSprite, std::shared_ptr<GunManagerComponent> _gunManager):
		SpriteRenderComponent(gameObject, defSprite, 0), gunManager(_gunManager) { }

	void render(SDL_Renderer * renderer) override;
private:
	std::shared_ptr<GunManagerComponent> gunManager;
};

#endif /* INCLUDE_FINAL_FINALGUNHUDRENDERCOMPONENT_HPP_ */
