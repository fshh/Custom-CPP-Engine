#include "breakout/BreakoutPlayerLives.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"

BreakoutPlayerLives::BreakoutPlayerLives(GameObject& gameObject, int initialLives):
	GenericComponent(gameObject), mLives(initialLives), mInitialX(gameObject.x()), mInitialY(gameObject.y())
{
}

void
BreakoutPlayerLives::update(Level& level)
{
	if (mLives <= 0)
	{
		level.lose();
	}
}

void
BreakoutPlayerLives::loseLife()
{
	mLives--;

	GameObject& gameObject = getGameObject();
	gameObject.setX(mInitialX);
	gameObject.setY(mInitialY);
}
