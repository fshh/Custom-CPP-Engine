#ifndef INCLUDE_FINAL_FINALPLAYERINPUTCOMPONENT_HPP_
#define INCLUDE_FINAL_FINALPLAYERINPUTCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "base/TinyMath.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include "final/FinalHealthComponent.hpp"
#include "base/AnimatorComponent.hpp"

class FinalPlayerInputComponent: public GenericComponent {
public:
	FinalPlayerInputComponent(GameObject& _gameObject, float _speed,
		float _dashSpeed, float _dashDistance, float _dashCooldown,
		std::shared_ptr<SpriteSheetRenderComponent> _renderComponent,
		std::shared_ptr<FinalHealthComponent> _healthComponent,
		std::shared_ptr<AnimatorComponent> _animatorComponent);

	virtual void update(Level& level) override;

private:
	const float speed;
	const float dashSpeed;
	const float dashDistance;
	const float dashCooldown;
	TinyMath::Vector2D<float> dashVector;
	float dashTimeRemaining;
	float dashCooldownRemaining;
	std::shared_ptr<SpriteSheetRenderComponent> renderComponent;
	std::shared_ptr<FinalHealthComponent> healthComponent;
	std::shared_ptr<AnimatorComponent> animatorComponent;
};

#endif
