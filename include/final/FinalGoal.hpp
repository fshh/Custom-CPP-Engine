#ifndef INCLUDE_FINAL_FINALGOAL_HPP_
#define INCLUDE_FINAL_FINALGOAL_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class FinalGoal: public GameObject {
public:
	FinalGoal(float x, float y, float size, int tag, SDLTextureResource* sprite);
};

#endif /* INCLUDE_FINAL_FINALGOAL_HPP_ */
