#ifndef INCLUDE_FINAL_FINALENEMYTHREEGUN_HPP_
#define INCLUDE_FINAL_FINALENEMYTHREEGUN_HPP_

#include "final/FinalAbstractGunComponent.hpp"
#include "base/Resource.hpp"

//! \brief A representation of a pistol.
class FinalEnemyThreeGun: public FinalAbstractGunComponent {
public:
	FinalEnemyThreeGun(GameObject& gameObject, int bulletTag, std::weak_ptr<GameObject> player, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound);

	void update(Level& level) override;

	static const float COOLDOWN; // In seconds
	static const float BULLET_SPEED;
	static const float BULLET_SCALE;
	static const int DAMAGE;

protected:
	//! \behavior Creates a bullet and sends it off in the given direction if the gun is off cooldown.
	void shoot(Level& level, const TinyMath::Vector2D<float>& dir) override;

private:
	int lastTimeShot;
	std::weak_ptr<GameObject> player;
};

#endif /* INCLUDE_FINAL_FINALENEMYTHREEGUN_HPP_ */
