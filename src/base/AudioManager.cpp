#include "base/AudioManager.hpp"

// Initialization flag
bool AudioManager::initialized = false;

bool
AudioManager::init() {
	if (initialized) { return true; }
	bool success = true;
	if (SDL_Init(SDL_INIT_AUDIO)) {
		printf( "SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	Mix_AllocateChannels(16);
	Mix_Volume(-1, MIX_MAX_VOLUME * 3 / 4.0f);

	initialized = success;
	return success;
}

void
AudioManager::shutdown() {
	if (!initialized) { return; }
	AudioManager::haltMusic();
	Mix_Quit();
	initialized = false;
}

void
AudioManager::playSound(SDLMixChunkResource* sound) {
	if (!sound) { return; }
	if (!initialized) {
		std::cout << "AudioManager not initialized! Can't play " << sound->getName() << std::endl;
		return;
	}

	Mix_PlayChannel(-1, sound->getMixChunk(), 0);
}

void
AudioManager::playMusic(SDLMixMusicResource* music) {
	if (!music) { return; }
	if (!initialized) {
		std::cout << "AudioManager not initialized! Can't play music." << std::endl;
		return;
	}

	Mix_PlayMusic(music->getMixMusic(), -1);
}

void
AudioManager::pauseMusic() {
	if (!initialized) {
		std::cout << "AudioManager not initialized! Can't pause music." << std::endl;
		return;
	}

	Mix_PauseMusic();
}

void
AudioManager::haltMusic() {
	if (!initialized) {
		std::cout << "AudioManager not initialized! Can't halt music." << std::endl;
		return;
	}

	Mix_HaltMusic();
}
