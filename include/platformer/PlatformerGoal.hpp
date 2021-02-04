#ifndef INCLUDE_PLATFORMER_PLATFORMERGOAL_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERGOAL_HPP_

#include "base/GameObject.hpp"

class PlatformerGoal: public GameObject {
public:
	PlatformerGoal(float x, float y, float size, int tag);
};

#endif /* INCLUDE_PLATFORMER_PLATFORMERGOAL_HPP_ */
