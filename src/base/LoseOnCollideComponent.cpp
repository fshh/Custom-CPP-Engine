#include "base/LoseOnCollideComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

LoseOnCollideComponent::LoseOnCollideComponent(GameObject & gameObject, int tag):
	RemoveOnCollideComponent(gameObject, tag)
{
}

void
LoseOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mTag) {
		level.removeObject(obj);
		level.lose();
  }
}

