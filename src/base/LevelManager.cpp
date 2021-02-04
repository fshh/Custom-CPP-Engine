#include "base/LevelManager.hpp"
#include "base/ResourceManager.hpp"


LevelManager::LevelManager(std::vector<std::shared_ptr<Level>> _levels):
	levels(_levels), levelIndex(0)
{
}

bool
LevelManager::load(unsigned int index) {
	if (index >= levels.size()) { return false; }

	levelIndex = index;
	level = levels[levelIndex];
	level->initTags();
	level->load();
	return true;
}

void
LevelManager::advance() {
	levelIndex++;
	if (hasWon()) {
		return;
	}
	level->unload();
	level = levels[levelIndex];
	level->load();
}

void
LevelManager::restart() {
	level->unload();
	if (hasWon()) {
		load(0);
	} else {
		level->load();
	}
}

bool
LevelManager::hasWon() {
	return levelIndex >= levels.size();
}
