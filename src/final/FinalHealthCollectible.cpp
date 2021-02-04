#include "final/FinalHealthCollectible.hpp"
#include "final/FinalHealthComponent.hpp"

FinalHealthCollectible::FinalHealthCollectible(float x, float y, float size, int tag, int health, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID):
	GameObject(x, y, size, size, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, size, size, spriteSheet, spriteID));
	addGenericComponent(std::make_shared<FinalHealthComponent>(*this, std::vector<int>(), health, 0.0f, nullptr, nullptr, nullptr));
}

