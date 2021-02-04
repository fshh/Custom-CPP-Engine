#include "final/FinalEnemyThreeGun.hpp"
#include "final/FinalBullet.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"
#include <SDL.h>

const float FinalEnemyThreeGun::COOLDOWN = 3.0f;
const float FinalEnemyThreeGun::BULLET_SCALE = 1.5f;
const float FinalEnemyThreeGun::BULLET_SPEED = 07.0f;
const int FinalEnemyThreeGun::DAMAGE = 15;

FinalEnemyThreeGun::FinalEnemyThreeGun(GameObject& gameObject, int bulletTag, std::weak_ptr<GameObject> player, SDLTextureResource* bulletSprite, SDLMixChunkResource* shootingSound):
	FinalAbstractGunComponent(gameObject, bulletTag, bulletSprite, shootingSound, "NON_PLAYER_GUN"), lastTimeShot(0), player(player)
{
}

void FinalEnemyThreeGun::update(Level& level) {
	if ((SDL_GetTicks() - lastTimeShot) / 1000.0f >= COOLDOWN) {
		AudioManager::playSound(mShootingSound);

		std::shared_ptr<GameObject> player_ptr = player.lock();
		TinyMath::Vector2D<float> playerPos = TinyMath::Vector2D<float>(player_ptr->x() + (player_ptr->w() / 2), player_ptr->y() + (player_ptr->h() / 2));
		TinyMath::Vector2D<float> wielderPos = TinyMath::Vector2D<float>(getGameObject().x() + (getGameObject().w() / 2), getGameObject().y() + (getGameObject().h() / 2));
		TinyMath::Vector2D<float> shotDir = playerPos - wielderPos;
		shotDir = TinyMath::Normalize(shotDir);
		shoot(level, shotDir);

		lastTimeShot = SDL_GetTicks();
	}
}

void FinalEnemyThreeGun::shoot(Level& level, const TinyMath::Vector2D<float>& dir) {
	const GameObject& gameObject = getGameObject();
	level.addObject(std::make_shared<Bullet>(gameObject.tag(), dir, BULLET_SPEED, DAMAGE,
			gameObject.x() + gameObject.w() / 2, gameObject.y() + gameObject.h() / 2, BULLET_SCALE, bulletTag, mBulletSprite));
}
