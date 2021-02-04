#ifndef BASE_LEVEL
#define BASE_LEVEL

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "base/Tags.hpp"

//! \brief A class for storing data about a single level.
//! Stores info about the screen size, player, and blocks.
class Level {
public:
	Level(const std::string& _dataPath); //!< Creates a new level object..
	virtual ~Level(); //!< Destroys this level object.

	virtual void initTags(); //!< Initializes the tags for this level.
	virtual void load(); //!< Loads the data for this level
	virtual void unload(); //!< Unloads the level data

	inline std::string getDataPath() const { return dataPath; }
	inline int w() const { return width; }
	inline int h() const { return height; }

	std::shared_ptr<GameObject> getShared(GameObject& object); //!< Get the shared pointer to the given GameObject.
	virtual void addObject(std::shared_ptr<GameObject> object); //!< Set an object to be added.
	virtual void removeObject(std::shared_ptr<GameObject> object); //!< Set an object to be removed.
	bool hasObject(std::shared_ptr<GameObject> object) const; //!< Get if an object is in the level.

	bool hasObjectWithTag(int tag); //!< Return true if objects has an object with the given tag.

	bool getCollisions(const GameObject & obj, std::vector<std::shared_ptr<GameObject>> & _objects) const; //!< Get objects colliding with a given object.
	bool getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>> & _objects) const; //!< Get objects colliding with a given point.

	virtual void update(); //!< Update the objects in the level.
	virtual void render(SDL_Renderer * renderer); //!< Render the level.

	inline int getLevelState() const { return levelState; } //!< Returns the value stored in levelState
	inline bool isLost() const { return levelState == -1; } //!< Returns true if the level is in a loss state
	inline bool isWon() const { return levelState == 1; } //!< Returns true if the level is in a won state
	void win(); //!< Call this function when the player completes the level.
	void lose(); //!< Call this function when the player loses the level.

protected:
	unsigned int width; //!< Width of the level, in pixels.
	unsigned int height; //!< Height of the level, in pixels.

	std::vector<std::shared_ptr<GameObject>> objects; //!< All the objects in the level.

	SDLMixChunkResource* winSound; //!< Sound that plays when the level is won.
	SDLMixChunkResource* loseSound; //!< Sound that plays when the level is lost.

private:
	Level(const Level &) = delete;
	void operator=(Level const&) = delete;

	int levelState; //!< -1 when the Level is lost, 0 when the Level is being played, and 1 when the level has been beaten.
	const std::string dataPath; //!< Path to the file which contains this level's data.

	std::vector<std::shared_ptr<GameObject>> objectsToAdd; //!< Objects to add to the level on the next frame.
	std::vector<std::shared_ptr<GameObject>> objectsToRemove; //!< Objects to remove from the level on the next frame.
};

#endif /* LEVEL_HPP */
