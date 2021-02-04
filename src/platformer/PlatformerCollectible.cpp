#include "platformer/PlatformerCollectible.hpp"

PlatformerCollectible::PlatformerCollectible(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID):
	GameObject(x, y, size, size, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, size, size, spriteSheet, spriteID));
}

