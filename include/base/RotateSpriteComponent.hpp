#ifndef INCLUDE_BASE_ROTATESPRITECOMPONENT_HPP_
#define INCLUDE_BASE_ROTATESPRITECOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "base/SpriteRenderComponent.hpp"

class RotateSpriteComponent: public GenericComponent {
public:
	RotateSpriteComponent(GameObject& gameObject, std::shared_ptr<SpriteRenderComponent> spriteRenderer, float rotationTime);

	void update(Level& level) override;

private:
	std::shared_ptr<SpriteRenderComponent> mSpriteRenderer;
	const float mRotationTime;
	float mTimeSinceLastRotation;
};



#endif /* INCLUDE_BASE_ROTATESPRITECOMPONENT_HPP_ */
