#ifndef INCLUDE_BREAKOUT_BLOCKHEALTHCOMPONENT_HPP_
#define INCLUDE_BREAKOUT_BLOCKHEALTHCOMPONENT_HPP_

#include "base/GenericComponent.hpp"

class BlockHealthComponent: public GenericComponent {
public:
	BlockHealthComponent(GameObject& gameObject, int initialHealth, int ballTag);

	void collision(Level& level, std::shared_ptr<GameObject> obj) override;

private:
	int mHealth;
	int mBallTag;

};



#endif /* INCLUDE_BREAKOUT_BLOCKHEALTHCOMPONENT_HPP_ */
