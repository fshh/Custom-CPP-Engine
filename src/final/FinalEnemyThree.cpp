#include "final/FinalEnemyThree.hpp"
#include "final/FinalHealthComponent.hpp"
#include "final/FinalEnemyThreeGun.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include "base/LoseOnCollideComponent.hpp"
#include "base/StatesAndTransitions.hpp"
#include "base/StateComponent.hpp"
#include "base/AnimatorComponent.hpp"
#include "base/Tags.hpp"

FinalEnemyThree::FinalEnemyThree(float x1, float y1, float size, std::weak_ptr<GameObject> player, int enemyThreeTag, int health, float hurtCooldown,
		SDLTextureResource* bulletSprite, SDLMixChunkResource* pistolSound, SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound,
		SDLSpriteSheetResource* spriteSheet, std::vector<AnimationState> animations):
	GameObject(x1, y1, size, size, enemyThreeTag)
{
	std::shared_ptr<SpriteSheetRenderComponent> renderer = std::make_shared<SpriteSheetRenderComponent>(*this, spriteSheet->getSpriteSize() * 2, spriteSheet->getSpriteSize() * 2, spriteSheet, 0);
	setRenderComponent(renderer);
	std::shared_ptr<AnimatorComponent> animator = std::make_shared<AnimatorComponent>(*this, renderer, animations);
	addGenericComponent(animator);

	std::shared_ptr<StateComponent::State> chaseState = std::make_shared<ChaseState>(1.0f, player, animator);

	std::shared_ptr<StateComponent> sc = std::make_shared<StateComponent>(*this);
	sc->setStartState(chaseState);
	addGenericComponent(sc);


	addGenericComponent(std::make_shared<FinalHealthComponent>(*this, std::vector<int> { Tags::tagOf("Player_Bullet") }, health, hurtCooldown, hurtSound, deathSound, animator));
	addGenericComponent(std::make_shared<FinalEnemyThreeGun>(*this, Tags::tagOf("Enemy_Bullet"), player, bulletSprite, pistolSound));
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));

}
