#include "base/InputManager.hpp"
#include <algorithm>

InputManager &
InputManager::getInstance()
{
  static InputManager * instance = new InputManager();
  return *instance;
}

void
InputManager::startUp()
{
	scrollDelta = TinyMath::Vector2D<float>(0.0f, 0.0f);
}

void
InputManager::shutDown()
{
}

void
InputManager::resetForFrame()
{
  mKeysPressed.clear();
  scrollDelta = TinyMath::Vector2D<float>(0.0f, 0.0f);
}

void
InputManager::handleEvent(const SDL_Event & e)
{
  if (e.type == SDL_KEYDOWN) {
    auto elem = mKeysDown.find(e.key.keysym.sym);
    if (elem == mKeysDown.end()) {
      mKeysPressed.insert(e.key.keysym.sym);
    }
    mKeysDown.insert(e.key.keysym.sym);
  } else if (e.type == SDL_KEYUP) {
    mKeysDown.erase(e.key.keysym.sym);
  } else if (e.type == SDL_MOUSEWHEEL) {
	scrollDelta.x = e.wheel.x;
	scrollDelta.y = e.wheel.y;
  }
}

bool
InputManager::isKeyDown(SDL_Keycode k) const
{
  return mKeysDown.find(k) != mKeysDown.end();
}

bool
InputManager::isKeyPressed(SDL_Keycode k) const
{
  return mKeysPressed.find(k) != mKeysPressed.end();
}
