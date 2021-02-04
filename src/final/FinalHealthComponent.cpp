#include "final/FinalHealthComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "final/FinalBullet.hpp"
#include "base/AudioManager.hpp"

FinalHealthComponent::FinalHealthComponent(GameObject & gameObject, std::vector<int> _tags, int health, float hurtCooldown,
		SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
		std::shared_ptr<AnimatorComponent> animator, bool loseOnDeath, bool invulnerable):
	GenericComponent(gameObject),
	tags(_tags),
	mHealth(health),
	mMaxHealth(health),
	mHurtCooldown(hurtCooldown),
	mLastTimeHurt(0),
	mHurtSound(hurtSound),
	mDeathSound(deathSound),
	mAnimator(animator),
	mLoseOnDeath(loseOnDeath),
	mInvulnerable(invulnerable)
{
}

void
FinalHealthComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	bool hit = false;
	for (int tag : tags) {
		if (obj->tag() == tag) {
			hit = true;
		}
	}
	if (!mInvulnerable && hit && (SDL_GetTicks() - mLastTimeHurt) / 1000.0f >= mHurtCooldown) {
		mLastTimeHurt = SDL_GetTicks();
		AudioManager::playSound(mHurtSound);
		if (mAnimator) { mAnimator->setState("hurt"); }
		std::shared_ptr<Bullet> bulletObj = std::dynamic_pointer_cast<Bullet>(obj);
		if (bulletObj) {
			mHealth -= bulletObj->getDamage();
		}
		else {
			mHealth -= 10;
		}
	}
	if(mHealth <= 0) {
		AudioManager::playSound(mDeathSound);
		if (mAnimator) { mAnimator->setState("dead"); }
		level.removeObject(level.getShared(getGameObject()));
		if (mLoseOnDeath)
		{
			level.lose();
		}
	}

}
