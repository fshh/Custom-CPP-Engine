#ifndef INCLUDE_FINAL_FINALGUNMANAGERCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALGUNMANAGERCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "final/FinalAbstractGunComponent.hpp"
#include "final/FinalPistolComponent.hpp"
#include "final/FinalShotgunComponent.hpp"
#include <vector>
#include <memory>

enum GunType {
	PISTOL,
	SHOTGUN
};

//! \brief Handles the guns the player has and switching between them.
class GunManagerComponent : public GenericComponent {
public:
	GunManagerComponent(GameObject& gameObject, std::vector<std::shared_ptr<FinalAbstractGunComponent>> _guns): GenericComponent(gameObject), guns(_guns), gunIndex(0) { }

	void update(Level& level) override;

	std::shared_ptr<FinalAbstractGunComponent> getCurrentGun() { return guns[gunIndex]; }

	void addGun(GunType type, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite);

private:
	std::vector<std::shared_ptr<FinalAbstractGunComponent>> guns;
	unsigned int gunIndex;
};

#endif /* INCLUDE_FINAL_FINALGUNMANAGERCOMPONENT_HPP_ */
