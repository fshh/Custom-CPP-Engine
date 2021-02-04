#include "final/FinalGunManagerComponent.hpp"
#include "base/InputManager.hpp"

void GunManagerComponent::update(Level& level) {
	if (InputManager::getInstance().isKeyPressed(SDLK_e)) {
		gunIndex = (gunIndex + 1) % guns.size();
	}
	else if (InputManager::getInstance().getScrollDelta().y > 0.0f) { // An exact 0 check is alright here because it is directly zeroed out when reset.
		gunIndex = (gunIndex + 1) % guns.size();
	}
	else if (InputManager::getInstance().getScrollDelta().y < 0.0f) {
		gunIndex = (gunIndex - 1) % guns.size();
	}

	guns[gunIndex]->update(level);
}

void GunManagerComponent::addGun(GunType type, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite) {
	switch (type) {
		case GunType::PISTOL:
			guns.push_back(std::make_shared<FinalPistolComponent>(getGameObject(), bulletTag, bulletSprite, shootingSound, hudSprite));
			break;
		case GunType::SHOTGUN:
			guns.push_back(std::make_shared<FinalShotgunComponent>(getGameObject(), bulletTag, bulletSprite, shootingSound, hudSprite));
			break;
	}
}
