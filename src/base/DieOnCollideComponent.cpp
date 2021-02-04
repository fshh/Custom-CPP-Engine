#include "base/DieOnCollideComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

void DieOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	for (int tag : ignoreTags) {
		if (tag == obj->tag()) {
			return;
		}
	}
	level.removeObject(level.getShared(getGameObject()));
}
