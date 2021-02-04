/*
 * Based on code from https://codereview.stackexchange.com/questions/165408/resource-manager-in-c-for-games
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

#include "json/json.h"


 //! \brief A class representing a resource to be managed by the ResourceManager.
class Resource
{
public:
	Resource() = delete;
	Resource(const std::string& _name, const std::string& _path);
	virtual ~Resource() {}

	virtual void load() = 0; //!< Loads resource value into memory.
	virtual void unload() = 0; //!< Unloads the resource value from memory.
	virtual bool isLoaded() const = 0; //!< Whether or not the resource value has been loaded into memory.

	void setName(const std::string& name); //!< Sets the name of the resource in the table.
	std::string getName() const; //!< Gets the name of this resource.

	void setPath(const std::string& path); //!< Sets the path this resource is loaded from.
	std::string getPath() const; //!< Gets the path this resource is loaded from.

protected:
	std::string name;
	std::string path;
};

//! \brief A class representing an SDL_Texture to be managed by the ResourceManager.
class SDLTextureResource: public Resource
{
public:
	SDLTextureResource() = delete;
	SDLTextureResource(const std::string& _name, const std::string& _path);
	~SDLTextureResource();

	virtual void load() override;
	virtual void unload() override;
	virtual bool isLoaded() const override;

	SDL_Texture* getTexture() const { return texture; } //!< Gets the SDL_Texture of this instance.

	int w() const { return width; }
	int h() const { return height; }

protected:
	SDL_Texture* texture;
	int width, height;
};

//! \brief This class represents a sprite sheet resource that uses a single image file with a square grid of sprites.
class SDLSpriteSheetResource: public SDLTextureResource
{
public:
	SDLSpriteSheetResource() = delete;
	SDLSpriteSheetResource(const std::string& _name, const std::string& _path, unsigned int _spriteSize);

	unsigned int getSpriteSize() const { return spriteSize; } //!< Return the size of a single square sprite on the sprite sheet.
private:
	unsigned int spriteSize;
};

//! \brief This class represents a resource used to render a message with a given font, size, and color
class SDLTextResource: public SDLTextureResource
{
public:
	SDLTextResource() = delete;
	SDLTextResource(const std::string& _name, const std::string& _fontFile, const std::string& _localizationKey, SDL_Color _color, int _fontSize);

	virtual void load() override;
	virtual void unload() override;
	void loadAdditionalText(const std::string& additionalText); //!< Updates this resource's texture to include the additional text after the text retrieved from the localization table.

	std::string getLocalizationKey() const { return localizationKey; } //!< Gets the localization key of this text resource.
	void setLocalizationKey(const std::string& _localizationKey); //!< Sets the localization key of this text resource (this reloads the associated texture).

	SDL_Color getColor() const { return color; } //!< Gets the color of this text resource.
	void setColor(const SDL_Color _color); //!< Sets the color of this text resource (this reloads the associated texture).

	int getFontSize() const { return fontSize; } //!< Gets the font size of this text resource.
	void setFontSize(const int fontSize); //!< Sets the font size of this text resource (this reloads the associated texture).

private:
	std::string localizationKey;
	SDL_Color color;
	int fontSize;
};

//! \brief A class representing a Mix_Chunk to be managed by the ResourceManager.
class SDLMixChunkResource: public Resource
{
public:
	SDLMixChunkResource() = delete;
	SDLMixChunkResource(const std::string& _name, const std::string& _path);
	~SDLMixChunkResource();

	void load() override;
	void unload() override;
	bool isLoaded() const override;

	Mix_Chunk* getMixChunk(); //!< Gets the chunk value.

private:
	Mix_Chunk* chunk;
};

//! \brief A class representing a Mix_Music to be managed by the ResourceManager.
class SDLMixMusicResource: public Resource
{
public:
	SDLMixMusicResource() = delete;
	SDLMixMusicResource(const std::string& _name, const std::string& _path);
	~SDLMixMusicResource();

	void load() override;
	void unload() override;
	bool isLoaded() const override;

	Mix_Music* getMixMusic(); //!< Gets the music value.

private:
	Mix_Music* music;
};

//! \brief A class representing a table of strings localized into various languages.
class LocalizationFileResource: public Resource
{
public:
	LocalizationFileResource() = delete;
	LocalizationFileResource(const std::string& _name, const std::string& _path);
	~LocalizationFileResource();

	void load() override;
	void unload() override;
	bool isLoaded() const override;

	Json::Value* getLocalizationTable(); //!< Gets the localization table JSON object.

private:
	Json::Value* localizationTable;
};

#endif /* RESOURCE_HPP */
