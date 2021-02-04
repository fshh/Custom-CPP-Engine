#include "platformer/Block.hpp"
#include "base/SpriteSheetRenderComponent.hpp"

Block::Block(float x, float y, float size, int tag, bool solid, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID):
	GameObject(x, y, size, size, tag)
{
		setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, solid));
		setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, size, size, spriteSheet, spriteID));
}

PlatformerBlockGrass::PlatformerBlockGrass(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	Block(x, y, size, tag, true, spriteSheet, rand() % 2 + 97)
{
}

PlatformerBlockStone::PlatformerBlockStone(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	Block(x, y, size, tag, true, spriteSheet, rand() % 10 + 1)
{
}
