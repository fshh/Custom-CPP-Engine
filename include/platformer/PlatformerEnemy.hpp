#ifndef INCLUDE_PLATFORMER_PLATFORMERENEMY_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERENEMY_HPP_

#include "base/GameObject.hpp"

class PlatformerEnemy: public GameObject {
public:
	PlatformerEnemy(float x1, float y1, float x2, float y2, float size, int enemyTag, int playerTag);
};


#endif /* INCLUDE_PLATFORMER_PLATFORMERENEMY_HPP_ */
