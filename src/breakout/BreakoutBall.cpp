#include "breakout/BreakoutBall.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "breakout/BreakoutBallMovementComponent.hpp"
#include "breakout/BreakoutBallPhysicsComponent.hpp"
#include "breakout/BreakoutScoreComponent.hpp"

BreakoutBall::BreakoutBall(float x, float y, float diameter, int tag, SDLTextureResource* sprite, float speed, std::shared_ptr<BreakoutPlayerLives> livesTracker,
		int blockTag, int playerTag, SDLMixChunkResource* blockBounceSound, SDLMixChunkResource* paddleBounceSound, SDLMixChunkResource* loseLifeSound):
	GameObject(x, y, diameter, diameter, tag)
{
	setPhysicsComponent(std::make_shared<BreakoutBallPhysicsComponent>(*this));
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
	addGenericComponent(std::make_shared<BreakoutBallMovementComponent>(*this, speed, livesTracker, blockTag, playerTag, blockBounceSound, paddleBounceSound, loseLifeSound));
	addGenericComponent(std::make_shared<BreakoutScoreComponent>(*this));
}

