#include <json/json.h>
#include <fstream>
#include <algorithm>

#include "base/Level.hpp"
#include "base/AutoProfile.hpp"
#include "base/AudioManager.hpp"

Level::Level(const std::string& _dataPath): width(0), height(0), levelState(0), dataPath(_dataPath) {
}

Level::~Level() {
	unload();
}

void Level::load()
{
}

void Level::unload()
{
	width = 0;
	height = 0;
	levelState = 0;
	objects.clear();
	objectsToAdd.clear();
	objectsToRemove.clear();
}

void Level::initTags() {
	Tags::addTag("Player", 1);
}

std::shared_ptr<GameObject>
Level::getShared(GameObject& object)
{
	for (auto gameObject : objects)
	{
		if (gameObject.get() == &object)
		{
			return gameObject;
		}
	}
	return nullptr;
}

void
Level::addObject(std::shared_ptr<GameObject> object)
{
  objectsToAdd.push_back(object);
}

void
Level::removeObject(std::shared_ptr<GameObject> object)
{
  objectsToRemove.push_back(object);
}
bool
Level::hasObject(std::shared_ptr<GameObject> object) const
{
  return std::find(objects.begin(), objects.end(), object) != objects.end();
}
bool
Level::hasObjectWithTag(int tag)
{
  for(auto gameObject: objects) {
	  if (gameObject->tag() == tag) {
		  return true;
	  }
  }
  return false;
}

bool
Level::getCollisions(const GameObject & obj, std::vector<std::shared_ptr<GameObject>> & _objects) const
{
	PROFILE("GetCollisions");
  _objects.clear();
  for (auto gameObject: objects) {
    if (gameObject.get() != &obj && gameObject->isColliding(obj)) {
      _objects.push_back(gameObject);
    }
  }
  return !_objects.empty();
}

bool
Level::getCollisions(float px, float py, std::vector<std::shared_ptr<GameObject>> & _objects) const
{
	PROFILE("GetCollisions");
  _objects.clear();
  for (auto gameObject: objects) {
    if (gameObject->isColliding(px, py)) {
      _objects.push_back(gameObject);
    }
  }
  return !_objects.empty();
}

void
Level::update()
{
	if (getLevelState() != 0) { return; }

  for (auto obj: objectsToAdd) {
    objects.push_back(obj);
  }
  objectsToAdd.clear();

  {
  	PROFILE("Update");
    for (auto gameObject: objects) {
      gameObject->update(*this);
    }
  }
  {
  	PROFILE("Step");
    for (auto gameObject: objects) {
      gameObject->step(*this);
    }
  }

  for (auto obj: objectsToRemove) {
    auto elem = std::find(objects.begin(), objects.end(), obj);
    if (elem != objects.end()) {
      objects.erase(elem);
    }
  }
  objectsToRemove.clear();
}

void
Level::render(SDL_Renderer * renderer)
{
	PROFILE("Render");
	for (auto gameObject: objects) {
		gameObject->render(renderer);
	}
}

void
Level::win()
{
	levelState = 1;
	AudioManager::playSound(winSound);
}

void
Level::lose()
{
	levelState = -1;
	AudioManager::playSound(loseSound);
}
