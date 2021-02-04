#ifndef INCLUDE_PLATFORMER_PLATFORMERLEVEL_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERLEVEL_HPP_

#include "base/Level.hpp"
#include "base/TextObject.hpp"

class PlatformerLevel: public Level {
public:
	PlatformerLevel(const std::string& jsonPath);

	void load() override;

	void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<TextObject> winText;
	std::shared_ptr<TextObject> loseText;
};



#endif /* INCLUDE_PLATFORMER_PLATFORMERLEVEL_HPP_ */
