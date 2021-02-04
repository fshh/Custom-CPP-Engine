#ifndef SRC_BREAKOUT_BREAKOUTBLOCK_CPP_
#define SRC_BREAKOUT_BREAKOUTBLOCK_CPP_

#include "breakout/BreakoutBlock.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "breakout/BlockHealthComponent.hpp"

BreakoutBlock::BreakoutBlock(float x, float y, float size, int tag, SDLTextureResource* sprite, int initialHealth, int ballTag):
	GameObject(x, y, size, size, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, true));
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
	addGenericComponent(std::make_shared<BlockHealthComponent>(*this, initialHealth, ballTag));
}


#endif /* SRC_BREAKOUT_BREAKOUTBLOCK_CPP_ */
