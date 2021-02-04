#ifndef INCLUDE_FINAL_FINALLEVEL_HPP_
#define INCLUDE_FINAL_FINALLEVEL_HPP_

#include "base/Level.hpp"
#include "base/TextObject.hpp"
#include "final/FinalGoal.hpp"

class FinalLevel: public Level {
public:
	FinalLevel(const std::string& jsonPath);

	void load() override;

	void initTags() override;

	void removeObject(std::shared_ptr<GameObject> object) override;

	void render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<TextObject> winText;
	std::shared_ptr<TextObject> loseText;

	int enemyTag;
	float clearPercent;
	int initialEnemies;
	int enemiesCleared;
	std::shared_ptr<FinalGoal> portal;
};



#endif /* INCLUDE_FINAL_FINALLEVEL_HPP_ */
