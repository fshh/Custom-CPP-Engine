// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#include "base/SDLGraphicsProgram.hpp"
#include "base/InputManager.hpp"
#include "base/AudioManager.hpp"
#include "base/Localization.hpp"
#include "base/Timer.hpp"
#include "base/Profiler.hpp"
#include <iostream>
#include <sstream>
#include <time.h>
#include <cmath>
#include <SDL_ttf.h>

SDL_Renderer* SDLGraphicsProgram::mRenderer = nullptr;

// Initialization function
SDLGraphicsProgram::SDLGraphicsProgram(std::shared_ptr<LevelManager> _levelManager, unsigned int _targetFPS, const char* _windowName):
  levelManager(_levelManager),
	idealFrameMS(1000.0f / (float)_targetFPS)
{
  // Initialize random number generation.
  srand(time(nullptr));


  // Initialization flag
  bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  mWindow = nullptr;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
    errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
    success = false;
  } else if (TTF_Init() != 0){
		errorStream << "TTF could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
  } else{
    //Create window
    //mWindow = SDL_CreateWindow( _windowName, 100, 100, levelManager->level->w(), levelManager->level->h(), SDL_WINDOW_SHOWN );
    mWindow = SDL_CreateWindow( _windowName, 100, 100, 1280, 704, SDL_WINDOW_SHOWN );

    // Check if Window did not create.
    if( mWindow == nullptr ){
      errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }

    //Create a Renderer to draw on
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if( mRenderer == nullptr ){
      errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    }
  }

  // start up managers
  Timer::getInstance();
  InputManager::getInstance().startUp();
  ResourceManager::getInstance().startUp();
  AudioManager::init();
  Localization::getInstance();
  Profiler::getInstance().startUp();
  Tags::getInstance();

  // If initialization did not work, then print out a list of errors in the constructor.
  if(!success){
    errorStream << "Failed to initialize!\n";
    std::string errors=errorStream.str();
    std::cout << errors << "\n";
  }else{
    std::cout << "No SDL errors Detected in during init\n\n";
  }
}



// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram() {
  Profiler::getInstance().shutDown();
  Localization::deleteInstance();
  AudioManager::shutdown();
  ResourceManager::getInstance().shutDown();
  InputManager::getInstance().shutDown();
  Timer::deleteInstance();
  Tags::deleteInstance();
  std::cout << "All managers shut down successfully" << std::endl;

  // Destroy Renderer
  SDL_DestroyRenderer(mRenderer);
  mRenderer = nullptr;

  //Destroy window
  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;

  //Quit SDL subsystems
  TTF_Quit();
  SDL_Quit();
}



// Update OpenGL
void SDLGraphicsProgram::update()
{
	if (levelManager->hasWon()) { return; }
  levelManager->level->update();
}


// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render() {
  SDL_SetRenderDrawColor(mRenderer, 0x22, 0x22, 0x22, 0xFF);
  SDL_RenderClear(mRenderer);

  levelManager->level->render(mRenderer);

  SDL_RenderPresent(mRenderer);
}

//Loops forever!
void SDLGraphicsProgram::loop(std::string instructions) {
	if (!levelManager->load(0)) {
		std::cout << "Program contains no levels! Aborting loop" << std::endl;
		return;
	}
    
	SDL_SetWindowSize(mWindow, levelManager->level->w(), levelManager->level->h());

    std::cout << instructions << std::endl;

  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;

  // While application is running
  while(!quit){
  	Timer::startTimer();

    InputManager::getInstance().resetForFrame();

    //Handle events on queue
    while(SDL_PollEvent( &e ) != 0){
      if(e.type == SDL_QUIT){
      	quit = true;
      }
      InputManager::getInstance().handleEvent(e);

      if (InputManager::getInstance().isKeyDown(SDLK_q)) {
      	quit = true;
      }

      if (InputManager::getInstance().isKeyPressed(SDLK_r)) {
    	  levelManager->restart();
      }

      if (InputManager::getInstance().isKeyPressed(SDLK_n)) {
    	  levelManager->advance();
    		SDL_SetWindowSize(mWindow, levelManager->level->w(), levelManager->level->h());
    	  break;
      }
    }

    if (levelManager->level->isWon() && !levelManager->hasWon())
    {
    	levelManager->advance();
    	SDL_SetWindowSize(mWindow, levelManager->level->w(), levelManager->level->h());
    }

    // update
    update();

		// render
		render();

		// get delta time for this frame
		float dt_ticks = Timer::getTime();

		// Wait however many milliseconds we need to get to the next frame window
		float wait_ms = idealFrameMS - (std::fmod(dt_ticks, idealFrameMS));
		SDL_Delay((unsigned int)wait_ms);

    Timer::endTimer();
  }
}
