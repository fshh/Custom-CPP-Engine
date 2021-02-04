#ifndef INCLUDE_BREAKOUT_BREAKOUTPLAYERLIVES_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTPLAYERLIVES_HPP_

#include "base/GenericComponent.hpp"

class BreakoutPlayerLives: public GenericComponent {
public:
	BreakoutPlayerLives(GameObject& gameObject, int initialLives);

	void update(Level& level) override;

	void loseLife();
	inline void addLife() { mLives++; }
	inline int getLives() const { return mLives; }

private:
	int mLives;

	const float mInitialX;
	const float mInitialY;
};



#endif /* INCLUDE_BREAKOUT_BREAKOUTPLAYERLIVES_HPP_ */
