#ifndef INCLUDE_FINAL_FINALSHOTGUNCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALSHOTGUNCOMPONENT_HPP_

#include "final/FinalAbstractGunComponent.hpp"
#include "base/Resource.hpp"

//! \brief A representation of a pistol.
class FinalShotgunComponent: public FinalAbstractGunComponent {
public:
	FinalShotgunComponent(GameObject& gameObject, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite);

	static const float COOLDOWN; // In seconds
	static const float SPREAD; // In degrees
	static const int PELLET_NUM;
	static const float BULLET_SPEED;
	static const float BULLET_SCALE;
	static const int DAMAGE;

protected:
	//! \behavior Creates a bullet and sends it off in the given direction if the gun is off cooldown.
	void shoot(Level& level, const TinyMath::Vector2D<float>& dir) override;

private:
	int lastTimeShot;

	// Representation of half spread in radians that only computes once.
	float spreadInRad;
};

#endif /* INCLUDE_FINAL_FINALSHOTGUNCOMPONENT_HPP_ */
