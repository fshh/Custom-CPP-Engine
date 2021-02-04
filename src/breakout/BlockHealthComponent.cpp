#include "breakout/BlockHealthComponent.hpp"
#include "breakout/BreakoutScoreComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

BlockHealthComponent::BlockHealthComponent(GameObject& gameObject, int initialHealth, int ballTag):
	GenericComponent(gameObject), mHealth(initialHealth), mBallTag(ballTag)
{
}

void
BlockHealthComponent::collision(Level& level, std::shared_ptr<GameObject> obj)
{
	if (obj->tag() == mBallTag)
	{
		mHealth--;

		if (mHealth < 1)
		{
			std::shared_ptr<BreakoutScoreComponent> scoreTracker;
			for (auto component : obj->genericComponents())
			{
				scoreTracker = std::dynamic_pointer_cast<BreakoutScoreComponent>(component);
				if (scoreTracker) { break; }
			}
			scoreTracker->incrementScore();

			GameObject& gameObject = getGameObject();

			level.removeObject(level.getShared(gameObject));
		}
	}
}

