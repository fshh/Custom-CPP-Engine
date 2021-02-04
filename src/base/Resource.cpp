#include "base/Resource.hpp"
#include "base/ResourceManager.hpp"
#include "base/SDLGraphicsProgram.hpp"
#include "base/Localization.hpp"
#include <iostream>
#include <fstream>

// ========== Resource ==========
Resource::Resource(const std::string& _name, const std::string& _path):
	name(_name), path(_path)
{
}

void
Resource::setName(const std::string& name)
{
	this->name = name;
}

std::string
Resource::getName() const
{
	return name;
}

void
Resource::setPath(const std::string& path)
{
	this->path = path;
}

std::string
Resource::getPath() const
{
	return path;
}


// ========== SDLTextureResource ==========
SDLTextureResource::SDLTextureResource(const std::string& _name, const std::string& _path):
	Resource(_name, _path),
	texture(nullptr),
	width(0),
	height(0)
{
}

SDLTextureResource::~SDLTextureResource()
{
	unload();
}

void
SDLTextureResource::load()
{
	unload();

	std::cout << "load(): Loading " << name << std::endl;

	// create surface
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));

	// create texture
	texture = SDL_CreateTextureFromSurface(SDLGraphicsProgram::getRenderer(), surface);

	// free surface
	SDL_FreeSurface(surface);

	// initialize width/height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	std::cout << SDL_GetError();
}

void
SDLTextureResource::unload()
{
	if (isLoaded())
	{
		std::cout << "unload(): Freeing texture for " << name << std::endl;
		SDL_DestroyTexture(texture);
	}
}

bool
SDLTextureResource::isLoaded() const
{
	return texture != nullptr;
}


// ========== SDLSpriteSheetResource ==========
SDLSpriteSheetResource::SDLSpriteSheetResource(const std::string& _name, const std::string& _path, unsigned int _spriteSize):
	SDLTextureResource(_name, _path),
	spriteSize(_spriteSize)
{
}


// ========== SDLTextResource ==========
SDLTextResource::SDLTextResource(const std::string& _name, const std::string& _fontFile, const std::string& _localizationKey, SDL_Color _color, int _fontSize):
	SDLTextureResource(_name, _fontFile),
	localizationKey(_localizationKey),
	color(_color),
	fontSize(_fontSize)
{
}

void
SDLTextResource::load()
{
	loadAdditionalText("");
}

void
SDLTextResource::unload()
{
	if (isLoaded()) { SDL_DestroyTexture(texture); }
}

void
SDLTextResource::loadAdditionalText(const std::string& additionalText)
{
	unload();

	// create font -> surface -> texture
	TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
	SDL_Surface *surface = TTF_RenderUTF8_Solid(font, (Localization::getInstance()->getLocalizedText(localizationKey) + additionalText).c_str(), color);
	texture = SDL_CreateTextureFromSurface(SDLGraphicsProgram::getRenderer(), surface);

	// free surface and font
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	// initialize width/height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	std::cout << SDL_GetError();
}

void
SDLTextResource::setLocalizationKey(const std::string& _localizationKey)
{
	localizationKey = _localizationKey;
	load();
}

void
SDLTextResource::setColor(const SDL_Color _color)
{
	color = _color;
	load();
}

void
SDLTextResource::setFontSize(const int _fontSize)
{
	fontSize = _fontSize;
	load();
}


// ========== SDLMixChunkResource ==========
SDLMixChunkResource::SDLMixChunkResource(const std::string& _name, const std::string& _path):
	Resource(_name, _path),
	chunk(nullptr)
{
}

SDLMixChunkResource::~SDLMixChunkResource()
{
	unload();
}

void
SDLMixChunkResource::load()
{
	unload();

	std::cout << "load(): Loading " << name << std::endl;
	chunk = Mix_LoadWAV(path.c_str());
	std::cout << SDL_GetError();
}

void
SDLMixChunkResource::unload()
{
	if (isLoaded())
	{
		std::cout << "unload(): Freeing Mix Chunk for " << name << std::endl;
		Mix_FreeChunk(chunk);
	}
}

bool
SDLMixChunkResource::isLoaded() const
{
	return chunk != nullptr;
}

Mix_Chunk*
SDLMixChunkResource::getMixChunk()
{
	return chunk;
}


// ========== SDLMixMusicResource ==========
SDLMixMusicResource::SDLMixMusicResource(const std::string& _name, const std::string& _path):
	Resource(_name, _path),
	music(nullptr)
{
}

SDLMixMusicResource::~SDLMixMusicResource()
{
	unload();
}

void
SDLMixMusicResource::load()
{
	unload();

	std::cout << "load(): Loading " << name << std::endl;
	music = Mix_LoadMUS(path.c_str());
	std::cout << SDL_GetError();
}

void
SDLMixMusicResource::unload()
{
	if (isLoaded())
	{
		std::cout << "unload(): Freeing music for " << name << std::endl;
		Mix_FreeMusic(music);
	}
}

bool
SDLMixMusicResource::isLoaded() const
{
	return music != nullptr;
}

Mix_Music*
SDLMixMusicResource::getMixMusic()
{
	return music;
}


// ========== LocalizationFileResource ==========
LocalizationFileResource::LocalizationFileResource(const std::string& _name, const std::string& _path):
	Resource(_name, _path),
	localizationTable(nullptr)
{
}

LocalizationFileResource::~LocalizationFileResource()
{
	unload();
}

void
LocalizationFileResource::load()
{
	unload();

	std::cout << "load(): Loading " << name << std::endl;
	std::ifstream file(path, std::ifstream::binary);
	localizationTable = new Json::Value();
	file >> *localizationTable;
}

void
LocalizationFileResource::unload()
{
	if (isLoaded())
	{
		std::cout << "unload(): Freeing localization for " << name << std::endl;
		delete localizationTable;
	}
}

bool
LocalizationFileResource::isLoaded() const
{
	return localizationTable != nullptr;
}

Json::Value*
LocalizationFileResource::getLocalizationTable()
{
	return localizationTable;
}





