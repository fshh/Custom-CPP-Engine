#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>
#include <string>

#include "base/Level.hpp"

//! \brief A class for managing the progression of levels in a game of BlockBreaker.
class LevelManager {
public:
	//! \brief Construct a level manager with the given levels.
	//! Note that this DOES NOT load any level's data for use, so call load() after construction.
	LevelManager(std::vector<std::shared_ptr<Level>> _levels);

	bool load(unsigned int index); //!< Load the level at the given index, if one exists. Returns whether loading was successful

	void advance(); //!< Progress to the next level.
	void restart(); //!< Restarts the current level.

	bool hasWon(); //!< Returns true if the player has advanced past all the levels in the list.

	std::shared_ptr<Level> level; //!< A pointer to the level currently being played. Other managers modify this level to affect the game state.

private:
	LevelManager() = delete;
	LevelManager(const LevelManager&) = delete;
	void operator=(LevelManager const&) = delete;

	std::vector<std::shared_ptr<Level>> levels; //!< A sequential list of pointers to the game's levels.

	unsigned int levelIndex; //!< Index of the current level in the list of levels.
};

#endif /* LEVEL_MANAGER_HPP */
