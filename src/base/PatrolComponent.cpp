#include "base/PatrolComponent.hpp"
#include "base/GameObject.hpp"

PatrolComponent::PatrolComponent(GameObject & gameObject, float toX, float toY, float speed):
  GenericComponent(gameObject)
{
  initX = gameObject.x();
  initY = gameObject.y();
  targetX = toX;
  targetY = toY;
  moveSpeed = speed;
}

void
PatrolComponent::update(Level & level)
{
	GameObject & gameObject = getGameObject();
	float curX = gameObject.x();
	float curY = gameObject.y();
	float curTarX, curTarY;
	if (towardsTarget) {
		curTarX = targetX;
		curTarY = targetY;
	} else {
		curTarX = initX;
		curTarY = initY;
	}

	if (curX < curTarX) {
		gameObject.setX(clamp(curX + moveSpeed, curX, curTarX));
	} else if (curX > curTarX) {
		gameObject.setX(clamp(curX - moveSpeed, curTarX, curX));
	}

	if (curY < curTarY) {
		gameObject.setY(clamp(curY + moveSpeed, curY, curTarY));
	} else if (curY > curTarY) {
		gameObject.setY(clamp(curY - moveSpeed, curTarY, curY));
	}

	if (gameObject.x() == curTarX && gameObject.y() == curTarY) {
		towardsTarget = !towardsTarget;
	}
}

float PatrolComponent::clamp(float curVal, float minVal, float maxVal) {
	return std::min(maxVal, std::max(minVal, curVal));
}
