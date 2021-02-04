#include "breakout/BreakoutPlayer.hpp"
#include "breakout/BreakoutPlayerInputComponent.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "breakout/BreakoutPlayerLives.hpp"

BreakoutPlayer::BreakoutPlayer(float x, float y, float width, float height, int tag, SDLTextureResource* sprite, float speed, int lives):
	GameObject(x, y, width, height, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, true));
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
	addGenericComponent(std::make_shared<BreakoutPlayerInputComponent>(*this, speed));
	addGenericComponent(std::make_shared<BreakoutPlayerLives>(*this, lives));
}
