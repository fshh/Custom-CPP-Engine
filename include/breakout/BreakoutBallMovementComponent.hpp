#ifndef INCLUDE_BREAKOUT_BREAKOUTBALLMOVEMENTCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTBALLMOVEMENTCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "breakout/BreakoutPlayerLives.hpp"
#include "base/Resource.hpp"

class BreakoutBallMovementComponent: public GenericComponent {
public:
	BreakoutBallMovementComponent(GameObject& gameObject, float speed, std::shared_ptr<BreakoutPlayerLives> livesTracker,
			int blockTag, int playerTag, SDLMixChunkResource* blockBounceSound, SDLMixChunkResource* paddleBounceSound, SDLMixChunkResource* loseLifeSound);

	void update(Level& level) override;
	void collision(Level& level, std::shared_ptr<GameObject> obj) override;

private:
	float mSpeed;
	std::shared_ptr<BreakoutPlayerLives> mLivesTracker;

	bool mStarted;
	const float mInitialX;
	const float mInitialY;
	int mBlockTag;
	int mPlayerTag;
	SDLMixChunkResource* mBlockBounceSound;
	SDLMixChunkResource* mPaddleBounceSound;
	SDLMixChunkResource* mLoseLifeSound;
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTBALLMOVEMENTCOMPONENT_HPP_ */
