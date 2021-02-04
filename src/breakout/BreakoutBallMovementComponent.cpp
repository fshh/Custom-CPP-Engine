#include "breakout/BreakoutBallMovementComponent.hpp"
#include "base/InputManager.hpp"
#include "base/TinyMath.hpp"
#include "base/GameObject.hpp"
#include "base/Timer.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"

BreakoutBallMovementComponent::BreakoutBallMovementComponent(GameObject& gameObject, float speed, std::shared_ptr<BreakoutPlayerLives> livesTracker,
		int blockTag, int playerTag, SDLMixChunkResource* blockBounceSound, SDLMixChunkResource* paddleBounceSound, SDLMixChunkResource* loseLifeSound):
	GenericComponent(gameObject), mSpeed(speed), mLivesTracker(livesTracker), mStarted(false), mInitialX(gameObject.x()), mInitialY(gameObject.y()),
		mBlockTag(blockTag), mPlayerTag(playerTag), mBlockBounceSound(blockBounceSound), mPaddleBounceSound(paddleBounceSound), mLoseLifeSound(loseLifeSound)
{
}


void
BreakoutBallMovementComponent::update(Level& level)
{
	GameObject& gameObject = getGameObject();
	std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

	if (!mStarted)
	{
		bool left = InputManager::getInstance().isKeyPressed(SDLK_LEFT);
		bool right = InputManager::getInstance().isKeyPressed(SDLK_RIGHT);
		if (left || right)
		{
			mStarted = true;

			TinyMath::Vector2D<float> vel(1, -1);
			vel = TinyMath::Normalize(vel) * mSpeed * Timer::deltaTime();

			pc->setVx(vel.x);
			pc->setVy(vel.y);
		}
	}

	float mx = gameObject.x() + pc->vx();
	float my = gameObject.y() + pc->vy();
	if (mx < 0 || mx + gameObject.w() > level.w() || my < 0)
	{
		AudioManager::playSound(mBlockBounceSound);
	}

	if (gameObject.y() > level.h())
	{
		mLivesTracker->loseLife();
		AudioManager::playSound(mLoseLifeSound);

		gameObject.setX(mInitialX);
		gameObject.setY(mInitialY);

		std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
		pc->setVx(0);
		pc->setVy(0);

		mStarted = false;
	}
}


void
BreakoutBallMovementComponent::collision(Level& level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mBlockTag)
	{
		AudioManager::playSound(mBlockBounceSound);
	}
	else if (obj->tag() == mPlayerTag)
	{
		AudioManager::playSound(mPaddleBounceSound);
	}
}

