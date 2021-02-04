#include "final/FinalShotgunComponent.hpp"
#include "final/FinalBullet.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"
#include <SDL.h>

const float FinalShotgunComponent::COOLDOWN = 1.0f;
const float FinalShotgunComponent::SPREAD = 30.0f;
const int FinalShotgunComponent::PELLET_NUM = 5;
// These are per bullet/pellet
const float FinalShotgunComponent::BULLET_SCALE = 2.0f;
const float FinalShotgunComponent::BULLET_SPEED = 20.0f;
const int FinalShotgunComponent::DAMAGE = 1;

FinalShotgunComponent::FinalShotgunComponent(GameObject& gameObject, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite):
	FinalAbstractGunComponent(gameObject, bulletTag, bulletSprite, shootingSound, hudSprite), lastTimeShot(0)
{
	spreadInRad = (SPREAD / 2) * (3.14159265f / 180.0f);
}

void FinalShotgunComponent::shoot(Level& level, const TinyMath::Vector2D<float>& dir) {
	if ((SDL_GetTicks() - lastTimeShot) / 1000.0f >= COOLDOWN) {
		AudioManager::playSound(mShootingSound);
		const GameObject& gameObject = getGameObject();
		// Get the angle of dir in radians.
		float angle = std::asin(dir.y);
		if (dir.x < 0) { // Flip negative angle to positive to make calculation easier.
			angle = 3.14159265f - angle;
		}
		float low = angle - spreadInRad;
		float high = angle + spreadInRad;
		for (int i = 0; i < PELLET_NUM; i++) {
			float angle = low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
			level.addObject(std::make_shared<Bullet>(
					gameObject.tag(),
					TinyMath::Vector2D<float>(cos(angle), sin(angle)),
					BULLET_SPEED,
					DAMAGE,
					gameObject.x() + gameObject.w() / 2,
					gameObject.y() + gameObject.h() / 2,
					BULLET_SCALE,
					bulletTag,
					mBulletSprite
				)
			);
		}
		lastTimeShot = SDL_GetTicks();
	}
}
