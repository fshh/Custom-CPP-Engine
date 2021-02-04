#include "base/SDLGraphicsProgram.hpp"
#include "base/LevelManager.hpp"
#include "base/GetResourcePath.hpp"
#include "platformer/PlatformerLevel.hpp"
#include <vector>
#include <memory>

const unsigned int TARGET_FPS = 60;

int main(int argc, char** argv) {
	std::vector<std::string> levelFiles = { "testBlocks.json", "testBlocks2.json", "testBlocks3.json" };
	std::vector<std::shared_ptr<Level>> levels;
	std::string levelsPath = getResourcePath("levels");
	for (auto file : levelFiles) {
		levels.push_back(std::make_shared<PlatformerLevel>(levelsPath + file));
	}
	std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>(levels);

	SDLGraphicsProgram platformerProgram(levelManager, TARGET_FPS, "Platformer");
	platformerProgram.loop("\nUse the arrow keys to control the player.\nGet to the goal and avoid enemies.\nGathering coins gives you points!\n");

	return 0;
}
