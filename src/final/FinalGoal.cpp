#include "final/FinalGoal.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "base/RotateSpriteComponent.hpp"

FinalGoal::FinalGoal(float x, float y, float size, int tag, SDLTextureResource* sprite):
	GameObject(x, y, size, size, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	std::shared_ptr<SpriteRenderComponent> renderComp = std::make_shared<SpriteRenderComponent>(*this, sprite);
	setRenderComponent(renderComp);
	addGenericComponent(std::make_shared<RotateSpriteComponent>(*this, renderComp, 2.0f));
}



