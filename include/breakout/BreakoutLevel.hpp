#ifndef INCLUDE_BREAKOUT_BREAKOUTLEVEL_HPP_
#define INCLUDE_BREAKOUT_BREAKOUTLEVEL_HPP_

#include "base/Level.hpp"
#include "base/TextObject.hpp"

class BreakoutLevel: public Level {
public:
	BreakoutLevel(const std::string& jsonPath);

	void load() override;

	void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<TextObject> winText;
	std::shared_ptr<TextObject> loseText;
};


#endif /* INCLUDE_BREAKOUT_BREAKOUTLEVEL_HPP_ */
