#ifndef INCLUDE_FINAL_FINALPISTOLCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALPISTOLCOMPONENT_HPP_

#include "final/FinalAbstractGunComponent.hpp"

//! \brief A representation of a pistol.
class FinalPistolComponent: public FinalAbstractGunComponent {
public:
	FinalPistolComponent(GameObject& gameObject, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite);

	static const float COOLDOWN; // In seconds
	static const float BULLET_SPEED;
	static const float BULLET_SCALE;
	static const int DAMAGE;

protected:
	//! \behavior Creates a bullet and sends it off in the given direction if the gun is off cooldown.
	void shoot(Level& level, const TinyMath::Vector2D<float>& dir) override;

private:
	int lastTimeShot;
};

#endif /* INCLUDE_FINAL_FINALPISTOLCOMPONENT_HPP_ */
