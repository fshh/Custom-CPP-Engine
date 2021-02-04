#ifndef INCLUDE_BASE_DIEONCOLLIDECOMPONENT_HPP_
#define INCLUDE_BASE_DIEONCOLLIDECOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include <vector>

//! \brief A component that destroys its gameObject when there is a collision with anything other than the ignored tag;
class DieOnCollideComponent : public GenericComponent {
public:
	DieOnCollideComponent(GameObject& gameObject, std::vector<int> _ignoreTags): GenericComponent(gameObject), ignoreTags(_ignoreTags) { }

	virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:
	std::vector<int> ignoreTags;
};

#endif /* INCLUDE_BASE_DIEONCOLLIDECOMPONENT_HPP_ */
