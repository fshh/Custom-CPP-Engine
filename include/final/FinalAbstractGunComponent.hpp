#ifndef INCLUDE_FINAL_FINALABSTRACTGUNCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALABSTRACTGUNCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "base/TinyMath.hpp"
#include "base/Resource.hpp"
#include <string>

//! \brief An abstract class defining what a gun should do.
class FinalAbstractGunComponent: public GenericComponent {
public:
	FinalAbstractGunComponent(GameObject& gameObject, int _bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite):
		GenericComponent(gameObject), bulletTag(_bulletTag), mBulletSprite(bulletSprite), mShootingSound(shootingSound), hudSpriteName(hudSprite) { }

	void update(Level& level) override;

	std::string getHudSpriteName() { return hudSpriteName; }

protected:
	//! \behavior Executes the firing behavior of the gun.
	virtual void shoot(Level& level, const TinyMath::Vector2D<float>& dir) = 0;

	int bulletTag;
	SDLTextureResource* mBulletSprite;
	SDLMixChunkResource* mShootingSound;
	std::string hudSpriteName;
};

#endif /* INCLUDE_FINAL_FINALABSTRACTGUNCOMPONENT_HPP_ */
