#include "base/SDLGraphicsProgram.hpp"
#include "base/LevelManager.hpp"
#include "base/GetResourcePath.hpp"
#include "final/FinalLevel.hpp"
#include <vector>
#include <memory>

const unsigned int TARGET_FPS = 60;

int main(int argc, char** argv) {
	std::vector<std::string> levelFiles = { "theFirstBone.json", "theSecondBone.json", "theThirdBone.json" };
	std::vector<std::shared_ptr<Level>> levels;
	std::string levelsPath = getResourcePath("levels");
	for (auto file : levelFiles) {
		levels.push_back(std::make_shared<FinalLevel>(levelsPath + file));
	}
	std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>(levels);

	SDLGraphicsProgram finalProgram(levelManager, TARGET_FPS, "Final");
	finalProgram.loop("\nUse the arrow keys or WASD to move.\nUse left click and the mouse to shoot enemies.\nPress E to swap weapons.\nPress spacebar to roll, dodging attacks.\nBeat the level by defeating all the enemies within the level!\n");

	return 0;
}
