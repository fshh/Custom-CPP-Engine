#ifndef INCLUDE_AUDIOMANAGER_HPP_
#define INCLUDE_AUDIOMANAGER_HPP_

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "GetResourcePath.hpp"
#include "ResourceManager.hpp"
#include "Resource.hpp"

//! \brief Class that manages audio playback for a play session.
class AudioManager {
public:

	static bool init(); //!< Initialize this AudioManager, setting up the underlying SDL libraries and loading audio resources.
	static void shutdown(); //!< Shut down this AudioManager, freeing audio resources and shutting down SDL libraries.
	static void playSound(SDLMixChunkResource* sound); //!< Play the sound with the given name.
	static void playMusic(SDLMixMusicResource* music); //!< Play the background music.
	static void pauseMusic(); //!< Pause the background music.
	static void haltMusic(); //!< Halt the background music fully.

private:
	static bool initialized;

};

#endif /* INCLUDE_AUDIOMANAGER_HPP_ */
