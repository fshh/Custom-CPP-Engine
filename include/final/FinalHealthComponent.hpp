#ifndef INCLUDE_FINAL_FINALHEALTHCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALHEALTHCOMPONENT_HPP_

#include "base/RemoveOnCollideComponent.hpp"
#include "base/Resource.hpp"
#include "base/AnimatorComponent.hpp"
#include <vector>

class FinalHealthComponent: public GenericComponent {
public:
	FinalHealthComponent(GameObject & gameObject, std::vector<int> _tags, int health, float hurtCooldown,
			SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
			std::shared_ptr<AnimatorComponent> animator, bool loseOnDeath = false, bool invulnerable = false);

	virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

	inline float getHealthPercentage() { return (float)mHealth / (float)mMaxHealth; }

	inline const int getHealth() { return mHealth; }

	inline void restoreHealth(int h) { mHealth = (mHealth + h > mMaxHealth ? mMaxHealth : mHealth + h); }

	inline void setInvulnerable(bool invulnerable) { mInvulnerable = invulnerable; }

private:
	std::vector<int> tags;

	int mHealth;
	int mMaxHealth;
	float mHurtCooldown;
	int mLastTimeHurt;
	SDLMixChunkResource* mHurtSound;
	SDLMixChunkResource* mDeathSound;
	std::shared_ptr<AnimatorComponent> mAnimator;
	bool mLoseOnDeath;
	bool mInvulnerable;
};



#endif
