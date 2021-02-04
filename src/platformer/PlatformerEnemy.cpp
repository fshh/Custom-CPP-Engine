#include "platformer/PlatformerEnemy.hpp"
#include "base/RectRenderComponent.hpp"
#include "base/LoseOnCollideComponent.hpp"
#include "base/PatrolComponent.hpp"

PlatformerEnemy::PlatformerEnemy(float x1, float y1, float x2, float y2, float size, int enemyTag, int playerTag):
	GameObject(x1, y1, size, size, enemyTag)
{
	addGenericComponent(std::make_shared<LoseOnCollideComponent>(*this, playerTag));
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<RectRenderComponent>(*this, 0x99, 0x00, 0x00));
	addGenericComponent(std::make_shared<PatrolComponent>(*this, x2, y2, 5.0f));
}
