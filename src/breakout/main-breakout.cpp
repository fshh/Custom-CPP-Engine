// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "base/SDLGraphicsProgram.hpp"
#include "base/LevelManager.hpp"
#include "base/GetResourcePath.hpp"
#include "breakout/BreakoutLevel.hpp"
#include <vector>
#include <memory>

const unsigned int TARGET_FPS = 60;

int main(int argc, char** argv) {
	std::cout << getResourcePath("sprites") << std::endl;

	std::vector<std::string> levelFiles = { "Level1.json", "Level2.json", "Level3.json" };
	std::vector<std::shared_ptr<Level>> levels;
	std::string levelsPath = getResourcePath("levels");
	for (auto file : levelFiles) {
		levels.push_back(std::make_shared<BreakoutLevel>(levelsPath + file));
	}
	std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>(levels);

	SDLGraphicsProgram breakoutProgram(levelManager, TARGET_FPS, "Breakout");
	breakoutProgram.loop("\nUse the left and right arrow keys to control the paddle.\nPrevent the ball from passing the paddle.\nBeat the level by destroying all the bricks with the ball!\n");

	return 0;
}
