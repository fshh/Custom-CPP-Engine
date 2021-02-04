#include "final/FinalGunHUD.hpp"
#include "final/FinalGunHUDRenderComponent.hpp"

FinalGunHUD::FinalGunHUD(float x, float y, float w, float h, int tag, SDLTextureResource* sprite, std::shared_ptr<GunManagerComponent> gunManager): GameObject(x, y, w, h, tag) {
	setRenderComponent(std::make_shared<FinalGunHUDRenderComponent>(*this, sprite, gunManager));
}

