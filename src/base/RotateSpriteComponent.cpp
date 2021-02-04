#include "base/RotateSpriteComponent.hpp"
#include "base/Timer.hpp"
#include "base/TinyMath.hpp"

RotateSpriteComponent::RotateSpriteComponent(GameObject& gameObject, std::shared_ptr<SpriteRenderComponent> spriteRenderer, float rotationTime):
	GenericComponent(gameObject), mSpriteRenderer(spriteRenderer), mRotationTime(rotationTime), mTimeSinceLastRotation(0.0f)
{
}

void
RotateSpriteComponent::update(Level& level)
{
	mTimeSinceLastRotation += Timer::deltaTime();
	if (mTimeSinceLastRotation >= mRotationTime) { mTimeSinceLastRotation = 0.0f; }
	mSpriteRenderer->setRotation(TinyMath::lerp(0.0, 360.0, (double)mTimeSinceLastRotation / (double)mRotationTime));
}

