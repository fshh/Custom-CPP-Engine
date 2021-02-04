#include "platformer/PlatformerGoal.hpp"
#include "base/RectRenderComponent.hpp"

PlatformerGoal::PlatformerGoal(float x, float y, float size, int tag):
	GameObject(x, y, size, size, tag)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<RectRenderComponent>(*this, 0x99, 0x99, 0x00));
}
