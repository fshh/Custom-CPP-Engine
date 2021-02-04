#include "final/FinalPistolComponent.hpp"
#include "final/FinalBullet.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"
#include <SDL.h>

const float FinalPistolComponent::COOLDOWN = 0.2f;
const float FinalPistolComponent::BULLET_SCALE = 1.5f;
const float FinalPistolComponent::BULLET_SPEED = 20.0f;
const int FinalPistolComponent::DAMAGE = 3;

FinalPistolComponent::FinalPistolComponent(GameObject& gameObject, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound, std::string hudSprite):
	FinalAbstractGunComponent(gameObject, bulletTag, bulletSprite, shootingSound, hudSprite), lastTimeShot(0)
{
}

void FinalPistolComponent::shoot(Level& level, const TinyMath::Vector2D<float>& dir) {
	if ((SDL_GetTicks() - lastTimeShot) / 1000.0f >= COOLDOWN) {
		AudioManager::playSound(mShootingSound);
		const GameObject& gameObject = getGameObject();
		level.addObject(std::make_shared<Bullet>(gameObject.tag(), dir, BULLET_SPEED, DAMAGE,
				gameObject.x() + gameObject.w() / 2, gameObject.y() + gameObject.h() / 2, BULLET_SCALE, bulletTag, mBulletSprite));
		lastTimeShot = SDL_GetTicks();
	}
}
