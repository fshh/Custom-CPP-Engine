#include "base/WinOnCollideComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

WinOnCollideComponent::WinOnCollideComponent(GameObject & gameObject, int tag):
	RemoveOnCollideComponent(gameObject, tag)
{
}

void
WinOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mTag) {
		level.removeObject(obj);
		level.win();
  }
}

