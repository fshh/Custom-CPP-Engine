#include "final/FinalEnemyTwoGun.hpp"
#include "final/FinalBullet.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"
#include <SDL.h>

const float FinalEnemyTwoGun::COOLDOWN = 3.0f;
const float FinalEnemyTwoGun::BULLET_SCALE = 1.5f;
const float FinalEnemyTwoGun::BULLET_SPEED = 05.0f;
const int FinalEnemyTwoGun::DAMAGE = 15;

FinalEnemyTwoGun::FinalEnemyTwoGun(GameObject& gameObject, int bulletTag, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound):
	FinalAbstractGunComponent(gameObject, bulletTag, bulletSprite, shootingSound, "NON_PLAYER_GUN"), lastTimeShot(0)
{
}

void FinalEnemyTwoGun::update(Level& level) {
	if ((SDL_GetTicks() - lastTimeShot) / 1000.0f >= COOLDOWN) {
		AudioManager::playSound(mShootingSound);
		shoot(level, TinyMath::Vector2D<float>(0.0f, 1.0f));
		shoot(level, TinyMath::Vector2D<float>(1.0f, 0.0f));
		shoot(level, TinyMath::Vector2D<float>(0.0f, -1.0f));
		shoot(level, TinyMath::Vector2D<float>(-1.0f, 0.0f));
		lastTimeShot = SDL_GetTicks();
	}
}

void FinalEnemyTwoGun::shoot(Level& level, const TinyMath::Vector2D<float>& dir) {
	const GameObject& gameObject = getGameObject();
	level.addObject(std::make_shared<Bullet>(gameObject.tag(), dir, BULLET_SPEED, DAMAGE,
			gameObject.x() + gameObject.w() / 2, gameObject.y() + gameObject.h() / 2, BULLET_SCALE, bulletTag, mBulletSprite));
}
