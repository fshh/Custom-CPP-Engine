// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#ifndef BASE_SDL_GRAPHICS_PROGRAM_HPP
#define BASE_SDL_GRAPHICS_PROGRAM_HPP

#include "base/LevelManager.hpp"
#include <string>
#include <memory.h>
#include <SDL.h>

//! \brief This class sets up a full graphics program.
class SDLGraphicsProgram {
public:

  // Constructor
  SDLGraphicsProgram(std::shared_ptr<LevelManager> _levelManager, unsigned int _targetFPS, const char* _windowName);

  // Destructor
  ~SDLGraphicsProgram();

  // Per frame update
  void update();

  // Renders shapes to the screen
  void render();

  // loop that runs forever
  void loop(std::string instructions);

  // get renderer
  static SDL_Renderer* getRenderer() { return mRenderer; }

private:

  // the current level
  std::shared_ptr<LevelManager> levelManager;
  
  // the ideal milliseconds to spend on each frame to achieve target FPS
  const float idealFrameMS;

  // The window we'll be rendering to
  SDL_Window * mWindow = nullptr;

  // SDL Renderer
  static SDL_Renderer * mRenderer;

};

#endif
