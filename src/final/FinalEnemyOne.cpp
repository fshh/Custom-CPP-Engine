#include "final/FinalEnemyOne.hpp"
#include "final/FinalHealthComponent.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include "base/LoseOnCollideComponent.hpp"
#include "base/StatesAndTransitions.hpp"
#include "base/StateComponent.hpp"
#include "base/AnimatorComponent.hpp"
#include "base/Tags.hpp"

FinalEnemyOne::FinalEnemyOne(float x1, float y1, float x2, float y2, float size, std::weak_ptr<GameObject> player, int enemyOneTag, int health, float hurtCooldown,
		SDLMixChunkResource* hurtSound, SDLMixChunkResource* deathSound, SDLSpriteSheetResource* spriteSheet,
		std::vector<AnimationState> animations):
	GameObject(x1, y1, size, size, enemyOneTag)
{
	std::shared_ptr<SpriteSheetRenderComponent> renderer = std::make_shared<SpriteSheetRenderComponent>(*this, spriteSheet->getSpriteSize() * 2, spriteSheet->getSpriteSize() * 2, spriteSheet, 0);
	setRenderComponent(renderer);
	std::shared_ptr<AnimatorComponent> animator = std::make_shared<AnimatorComponent>(*this, renderer, animations);
	addGenericComponent(animator);

	std::shared_ptr<StateComponent::State> patrolState = std::make_shared<PatrolState>(2.0f, x1, y1, x2, y2, animator);
	std::shared_ptr<StateComponent::State> chaseState = std::make_shared<ChaseState>(4.0f, player, animator);
	std::shared_ptr<StateComponent::State> returnState = std::make_shared<MoveState>(3.0f, x1, y1, animator);

	std::shared_ptr<StateComponent> sc = std::make_shared<StateComponent>(*this);
	sc->setStartState(patrolState);
	sc->addTransition(patrolState, chaseState, std::make_shared<ObjectProximityTransition>(player, size * 5.0f));
	sc->addTransition(returnState, chaseState, std::make_shared<ObjectProximityTransition>(player, size * 3.0f));
	sc->addTransition(chaseState, returnState, std::make_shared<TimedTransition>(60));
	sc->addTransition(returnState, patrolState, std::make_shared<PointProximityTransition>(x1, y1, size / 4.0f));
	addGenericComponent(sc);

	addGenericComponent(std::make_shared<FinalHealthComponent>(*this, std::vector<int> { Tags::tagOf("Player_Bullet") }, health, hurtCooldown, hurtSound, deathSound, animator));
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));

}
