#include "base/GameObject.hpp"
#include "base/SDLGraphicsProgram.hpp"
#include "base/GetResourcePath.hpp"
#include "editor/BreakoutEditorLevel.hpp"
#include "editor/PlatformerEditorLevel.hpp"
#include "editor/FinalEditorLevel.hpp"
#include <memory>
#include <SDL.h>
#include <iostream>
#include <string>

const unsigned int TARGET_FPS = 60;

int chooseFromList(std::vector<std::string> list) {
	for (unsigned int i = 0; i < list.size(); i++) {
		std::cout << i <<" - " << list[i] << std::endl;
	}
	bool invalid = true;
	int index;
	while (invalid) {
		std::cin >> index;
		if (index < 0 || index > (int)list.size()) {
			std::cout << "Invalid number, please enter a valid number:" << std::endl;
		}
		else {
			invalid = false;
		}
	}
	return index;
}

// Run the level editor
int main(int argc, char** argv) {
	std::vector<std::string> games = { "Breakout", "Platformer", "BoneThrone" };

	std::cout << "To use level editor, simply click to place a block and use the number keys to change the block type." << std::endl;
	std::cout << "Save the level by hitting s. Closing the application will not save." << std::endl;
	std::cout << "Input the number of the game with levels you want to edit:" << std::endl;
	int game = chooseFromList(games);
	std::string levelsPath = getResourcePath("levels");
	std::shared_ptr<Level> level;
	if (game == 0) {
		std::vector<std::string> levelFiles = { "Level1.json", "Level2.json", "Level3.json" };
		level = std::make_shared<BreakoutEditorLevel>(levelsPath + levelFiles[chooseFromList(levelFiles)]);
	}
	else if (game == 1) {
		std::vector<std::string> levelFiles = { "testBlocks.json", "testBlocks2.json", "testBlocks3.json" };
		level = std::make_shared<PlatformerEditorLevel>(levelsPath + levelFiles[chooseFromList(levelFiles)]);
	} else {
		std::vector<std::string> levelFiles = { "theFirstBone.json", "theSecondBone.json", "theThirdBone.json" };
		level = std::make_shared<FinalEditorLevel>(levelsPath + levelFiles[chooseFromList(levelFiles)]);
	}

	std::vector<std::shared_ptr<Level>> levels;
	levels.push_back(level);
	std::shared_ptr<LevelManager> levelManager = std::make_shared<LevelManager>(levels);

	SDLGraphicsProgram editorProgram(levelManager, TARGET_FPS, "Level Editor");
	editorProgram.loop("");

	return 0;
}
