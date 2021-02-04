#include "final/FinalGunHUDRenderComponent.hpp"
#include "base/ResourceManager.hpp"
#include <iostream>

void FinalGunHUDRenderComponent::render(SDL_Renderer * renderer) {
	SDLTextureResource* newSprite = ResourceManager::get<SDLTextureResource>(gunManager->getCurrentGun()->getHudSpriteName());
	if (newSprite == nullptr) {
		std::cout << "Couldn't find a gun HUD sprite with the name " << gunManager->getCurrentGun()->getHudSpriteName() << std::endl;
	}
	else {
		sprite = newSprite;
	}
	SpriteRenderComponent::render(renderer);
}
