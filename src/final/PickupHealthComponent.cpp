#include "final/PickupHealthComponent.hpp"
#include "final/FinalHealthComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/AudioManager.hpp"

PickupHealthComponent::PickupHealthComponent(GameObject& gameObject, int tag, SDLMixChunkResource* pickupSound):
	RemoveOnCollideComponent(gameObject, tag), mPickupSound(pickupSound)
{
}

void
PickupHealthComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mTag) {
		std::shared_ptr<FinalHealthComponent> healthPack = obj->getGenericComponent<FinalHealthComponent>();
		std::shared_ptr<FinalHealthComponent> playerHealth = getGameObject().getGenericComponent<FinalHealthComponent>();
		playerHealth->restoreHealth(healthPack->getHealth());
		AudioManager::playSound(mPickupSound);
		level.removeObject(obj);
  }
}
