#ifndef INCLUDE_FINAL_FINALBULLET_HPP_
#define INCLUDE_FINAL_FINALBULLET_HPP_

#include "base/GameObject.hpp"
#include "base/TinyMath.hpp"
#include "base/Resource.hpp"

//! \brief A representation of a bullet flying through the level.
class Bullet : public GameObject {
public:
	Bullet(int shooterTag, TinyMath::Vector2D<float> dir, float speed, int damage, float x, float y, float scale, int tag, SDLTextureResource* sprite);

	int getDamage() { return damage; }

private:
	int damage;
};

#endif /* INCLUDE_FINAL_FINALBULLET_HPP_ */
