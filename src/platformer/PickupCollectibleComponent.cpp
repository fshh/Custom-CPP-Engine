#include "platformer/PickupCollectibleComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"

PickupCollectibleComponent::PickupCollectibleComponent(GameObject& gameObject, int tag, SDLMixChunkResource* pickupSound):
	RemoveOnCollideComponent(gameObject, tag), mCount(0), mPickupSound(pickupSound)
{
}

void
PickupCollectibleComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mTag) {
		AudioManager::playSound(mPickupSound);
		level.removeObject(obj);
		mCount++;
  }
}

