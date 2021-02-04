#ifndef INCLUDE_BASE_CURSORCOMPONENT_HPP_
#define INCLUDE_BASE_CURSORCOMPONENT_HPP_

#include "base/GenericComponent.hpp"

class CursorComponent: public GenericComponent {
public:
	CursorComponent(GameObject& gameObject);

	void update(Level& level) override;
};



#endif /* INCLUDE_BASE_CURSORCOMPONENT_HPP_ */
