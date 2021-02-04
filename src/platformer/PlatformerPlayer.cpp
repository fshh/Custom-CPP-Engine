#include "platformer/PlatformerPlayer.hpp"
#include "platformer/PlatformerPlayerInputComponent.hpp"
#include "platformer/PlatformerPlayerRenderComponent.hpp"
#include "platformer/PickupCollectibleComponent.hpp"
#include "base/WinOnCollideComponent.hpp"

PlatformerPlayer::PlatformerPlayer(float x, float y, float width, float height, int playerTag, int goalTag, int collectibleTag,
		float speed, float jumpSpeed, float gravity, SDLSpriteSheetResource* spriteSheet,
		SDLMixChunkResource* jumpSound, SDLMixChunkResource* pickupCollectibleSound):
	GameObject(x, y, width, height, playerTag)
{
	addGenericComponent(std::make_shared<PlatformerPlayerInputComponent>(*this, speed, jumpSpeed, gravity, jumpSound));
	addGenericComponent(std::make_shared<WinOnCollideComponent>(*this, goalTag));
	addGenericComponent(std::make_shared<PickupCollectibleComponent>(*this, collectibleTag, pickupCollectibleSound));
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<PlatformerPlayerRenderComponent>(*this, spriteSheet->getSpriteSize(), spriteSheet));
}
