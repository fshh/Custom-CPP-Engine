#include "breakout/BreakoutBallPhysicsComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/TinyMath.hpp"
#include <cmath>
#include <algorithm>

BreakoutBallPhysicsComponent::BreakoutBallPhysicsComponent(GameObject& gameObject):
	PhysicsComponent(gameObject, false)
{
}

void
BreakoutBallPhysicsComponent::step(Level& level)
{
  GameObject & gameObject = getGameObject();

  float oldX = gameObject.x();
  float oldY = gameObject.y();

  gameObject.setX(gameObject.x() + mVx);
  gameObject.setY(gameObject.y() + mVy);

  if (!mSolid) {
    std::vector<std::shared_ptr<GameObject>> objects;
    if (level.getCollisions(gameObject, objects)) {
    	if (mVy < 0.0f)
    	{
      	std::sort(objects.begin(), objects.end(),
  				[](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) -> bool
  				{
      			return a->y() > b->y();
  				}
  			);
    	}
      for (auto obj: objects) {
				if (obj->physicsComponent()) {
					if (obj->physicsComponent()->isSolid()) {
						if (!gameObject.isColliding(*obj)) {
							continue;
						}

						float resolveX = 0.0f;
						if (oldX < obj->x() && mVx > 0.0f) {
							resolveX = -(gameObject.x() - (obj->x() - gameObject.w()));
						} else if (oldX > obj->x() && mVx < 0.0f) {
							resolveX = (obj->x() - (gameObject.x() - obj->w()));
						}

						float resolveY = 0.0f;
						if (oldY < obj->y() && mVy > 0.0f) {
							resolveY = -(gameObject.y() - (obj->y() - gameObject.h()));
						} else if (oldY > obj->y() && mVy < 0.0f) {
							resolveY = (obj->y() - (gameObject.y() - obj->h()));
						}

						if (resolveX != 0.0f && resolveY != 0.0f) {
							if (fabsf(resolveX) < fabsf(resolveY)) {
								gameObject.setX(gameObject.x() + resolveX);
								mVx = -mVx;
							} else {
								gameObject.setY(gameObject.y() + resolveY);
								mVy = -mVy;
							}
						} else if (resolveX != 0.0f) {
							gameObject.setX(gameObject.x() + resolveX);
							mVx = -mVx;
						} else if (resolveY != 0.0f) {
							gameObject.setY(gameObject.y() + resolveY);
							mVy = -mVy;
						}
					}
					gameObject.collision(level, obj);
					obj->collision(level, level.getShared(gameObject));
				}
      }
    }
    if (gameObject.x() < 0 || gameObject.x() > level.w() - gameObject.w())
    {
  		float clampX = TinyMath::clamp(gameObject.x(), 0.0f, level.w() - gameObject.w());
    	gameObject.setX(clampX);
    	mVx = -mVx;
    }
    if (gameObject.y() < 0)
    {
    	gameObject.setY(0);
    	mVy = -mVy;
    }
  }
}

