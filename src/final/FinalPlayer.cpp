#include "final/FinalPlayer.hpp"
#include "final/FinalHealthComponent.hpp"
#include "final/FinalPlayerInputComponent.hpp"
#include "final/FinalAbstractGunComponent.hpp"
#include "final/FinalPistolComponent.hpp"
#include "final/FinalShotgunComponent.hpp"
#include "final/FinalGunManagerComponent.hpp"
#include "final/PickupHealthComponent.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include "base/Tags.hpp"
#include "base/WinOnCollideComponent.hpp"
#include "base/AnimatorComponent.hpp"

FinalPlayer::FinalPlayer(float x, float y, float width, float height, int tag, float speed,
		float dashSpeed, float dashDistance, float dashCooldown,
		int health, float hurtCooldown,
		SDLSpriteSheetResource* spriteSheet, SDLMixChunkResource* pickupHealthSound,
		std::vector<std::shared_ptr<FinalAbstractGunComponent>> guns,
		SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
		std::vector<AnimationState> animations):
	GameObject(x, y, width, height, tag)
{
		setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
		std::shared_ptr<SpriteSheetRenderComponent> renderComp = std::make_shared<SpriteSheetRenderComponent>(*this, spriteSheet->getSpriteSize() * 2, spriteSheet->getSpriteSize() * 2, spriteSheet, 0);
		setRenderComponent(renderComp);
		std::shared_ptr<AnimatorComponent> animatorComp = std::make_shared<AnimatorComponent>(*this, renderComp, animations);
		addGenericComponent(animatorComp);
		std::shared_ptr<FinalHealthComponent> healthComp = std::make_shared<FinalHealthComponent>(*this, 
			std::vector<int> { Tags::tagOf("Enemy"), Tags::tagOf("Enemy_Bullet") }, health, hurtCooldown, hurtSound, deathSound, animatorComp, true);
		addGenericComponent(healthComp);
		addGenericComponent(std::make_shared<FinalPlayerInputComponent>(*this, speed, dashSpeed, dashDistance, dashCooldown, renderComp, healthComp, animatorComp));
		addGenericComponent(std::make_shared<GunManagerComponent>(*this, guns));
		addGenericComponent(std::make_shared<PickupHealthComponent>(*this, Tags::tagOf("Collectible"), pickupHealthSound));
		addGenericComponent(std::make_shared<WinOnCollideComponent>(*this, Tags::tagOf("Goal")));
}
