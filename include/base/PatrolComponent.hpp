#ifndef BASE_PATROL_COMPONENT
#define BASE_PATROL_COMPONENT

#include "base/GenericComponent.hpp"
#include <algorithm>

//! \brief A component that causes its game object to patrol back and forth.
class PatrolComponent: public GenericComponent {
public:

  PatrolComponent(GameObject & gameObject, float toX, float toY, float speed);
  
  virtual void update(Level & level);

private:

  float initX;
  float initY;
  float targetX;
  float targetY;
  float moveSpeed;
  bool towardsTarget = true;

  float clamp(float curVal, float minVal, float maxVal);
};

#endif
