#include "breakout/BreakoutLevel.hpp"
#include "base/ResourceManager.hpp"
#include "base/AudioManager.hpp"
#include "base/Localization.hpp"
#include "base/GetResourcePath.hpp"
#include "breakout/BreakoutBlock.hpp"
#include "breakout/BreakoutPlayer.hpp"
#include "breakout/BreakoutBall.hpp"
#include "breakout/BreakoutPlayerLives.hpp"
#include "breakout/BreakoutScoreComponent.hpp"
#include "breakout/BreakoutScore.hpp"
#include "breakout/BreakoutLivesText.hpp"
#include <fstream>

BreakoutLevel::BreakoutLevel(const std::string& jsonPath):
	Level(jsonPath)
{
}

void
BreakoutLevel::render(SDL_Renderer* renderer)
{
	Level::render(renderer);
	if (isWon()) { winText->render(renderer); }
	else if (isLost()) { loseText->render(renderer); }
}

void
BreakoutLevel::load()
{
	Json::Value data;
	std::ifstream file(getDataPath(), std::ifstream::binary);
	file >> data;
	file.close();

	const float SIZE = data["size"].asFloat();
	const int TAG_PLAYER = 1;
	const int TAG_BALL = 2;
	const int TAG_BLOCKS = 3;
	const int TAG_TEXT = 4;

	{
		// TEXT
		const Json::Value texts = data["text"];
		for (unsigned int ii = 0; ii < texts.size(); ++ii) {
			Json::Value textData = texts[ii];
			if (ResourceManager::get<SDLTextResource>(textData["name"].asString())) { continue; }

			Json::Value colorData = textData["color"];
			SDLTextResource* text = new SDLTextResource(
					textData["name"].asString(),
					getResourcePath() + Localization::fontFile,
					textData["tag"].asString(),
					SDL_Color{
						(unsigned char)colorData["r"].asUInt(), (unsigned char)colorData["g"].asUInt(),
						(unsigned char)colorData["b"].asUInt(), (unsigned char)colorData["a"].asUInt()
					},
					textData["size"].asInt());
			ResourceManager::add<SDLTextResource>(text);
		}
	}

	{
		// SPRITES
		const Json::Value sprites = data["sprites"];
		for (unsigned int ii = 0; ii < sprites.size(); ++ii) {
			Json::Value spriteData = sprites[ii];
			if (ResourceManager::get<SDLTextureResource>(spriteData["name"].asString())) { continue; }

			SDLTextureResource* sprite = new SDLTextureResource(
					spriteData["name"].asString(),
					getResourcePath("sprites") + spriteData["file"].asString());
			ResourceManager::add<SDLTextureResource>(sprite);
		}
	}

	{
		// SOUNDS
		const Json::Value sounds = data["sounds"];
		for (unsigned int ii = 0; ii < sounds.size(); ++ii) {
			Json::Value soundData = sounds[ii];
			if (ResourceManager::get<SDLMixChunkResource>(soundData["name"].asString())) { continue; }

			SDLMixChunkResource* sound = new SDLMixChunkResource(
					soundData["name"].asString(),
					getResourcePath("sounds") + soundData["file"].asString());
			ResourceManager::add<SDLMixChunkResource>(sound);
		}

		winSound = nullptr;
		loseSound = ResourceManager::get<SDLMixChunkResource>(data["loseSound"].asString());
	}

	{
		// MUSIC
		const Json::Value musicData = data["music"];
		SDLMixMusicResource* music = new SDLMixMusicResource(
				musicData["name"].asString(),
				getResourcePath("sounds") + musicData["file"].asString());
		ResourceManager::add<SDLMixMusicResource>(music);
		AudioManager::playMusic(music);
	}

	{
		// BLOCKS
		SDLTextureResource* blockSprite = ResourceManager::get<SDLTextureResource>(data["blocks"]["sprite"].asString());
		const Json::Value rows = data["blocks"]["grid"];
		// track height of the level
		height = rows.size() * SIZE;
		for (unsigned int ii = 0; ii < rows.size(); ++ii) {
			const char* cols = rows[ii].asCString();
			// track width of the level
			width = std::max(width, (unsigned int)strlen(cols) * (unsigned int)SIZE);
			for (unsigned int jj = 0; jj < strlen(cols); ++jj) {
				// construct block object from blockType
				const char blockType = cols[jj];
				if (blockType == 'x') {
					addObject(std::make_shared<BreakoutBlock>(jj * SIZE, ii * SIZE, SIZE, TAG_BLOCKS, blockSprite, 1, TAG_BALL));
				}
			}
		}
	}

	std::shared_ptr<BreakoutPlayerLives> playerLivesTracker;
	float playerY;
	{
		// PLAYER
		const Json::Value playerData = data["player"];
		// load player values
		float playerWidth = SIZE * 2;
		float playerHeight = SIZE / 2;
		float playerX = (width / 2) - (playerWidth / 2);
		playerY = height - (2 * playerHeight);
		SDLTextureResource* playerSprite = ResourceManager::get<SDLTextureResource>(playerData["sprite"].asString());
		float playerSpeed = playerData["speed"].asFloat();
		int playerLives = playerData["lives"].asInt();
		std::shared_ptr<BreakoutPlayer> player = std::make_shared<BreakoutPlayer>(
			playerX,
			playerY,
			playerWidth,
			playerHeight,
			TAG_PLAYER,
			playerSprite,
			playerSpeed,
			playerLives);
		addObject(player);

		// Get the lives component on the player
		playerLivesTracker = player->getGenericComponent<BreakoutPlayerLives>();
	}

	std::shared_ptr<BreakoutScoreComponent> scoreTracker;
	{
		// BALL
		const Json::Value ballData = data["ball"];
		// load ball values
		float ballDiameter = SIZE / 2;
		float ballX = (width / 2) - (ballDiameter / 2);
		float ballY = playerY - ballDiameter;
		SDLTextureResource* ballSprite = ResourceManager::get<SDLTextureResource>(ballData["sprite"].asString());
		SDLMixChunkResource* blockBounceSound = ResourceManager::get<SDLMixChunkResource>(ballData["blockBounceSound"].asString());
		SDLMixChunkResource* paddleBounceSound = ResourceManager::get<SDLMixChunkResource>(ballData["paddleBounceSound"].asString());
		SDLMixChunkResource* loseLifeSound = ResourceManager::get<SDLMixChunkResource>(ballData["loseLifeSound"].asString());
		float ballSpeed = ballData["speed"].asFloat();
		std::shared_ptr<BreakoutBall> ball = std::make_shared<BreakoutBall>(
			ballX,
			ballY,
			ballDiameter,
			TAG_BALL,
			ballSprite,
			ballSpeed,
			playerLivesTracker,
			TAG_BLOCKS,
			TAG_PLAYER,
			blockBounceSound,
			paddleBounceSound,
			loseLifeSound);
		addObject(ball);

		scoreTracker = ball->getGenericComponent<BreakoutScoreComponent>();
	}

	{
		// SCORE
		Json::Value scoreData = data["score"];
		SDLTextResource* scoreText = ResourceManager::get<SDLTextResource>(scoreData["text"].asString());
		std::shared_ptr<BreakoutScore> score = std::make_shared<BreakoutScore>(
				scoreData["x"].asInt(),
				scoreData["y"].asInt(),
				TAG_TEXT,
				scoreText,
				scoreTracker);
		addObject(score);
	}

	{
		// LIVES
		const Json::Value livesData = data["livesText"];
		SDLTextResource* livesText = ResourceManager::get<SDLTextResource>(livesData["text"].asString());
		std::shared_ptr<BreakoutLivesText> livesTextObject = std::make_shared<BreakoutLivesText>(
				livesData["x"].asInt(),
				livesData["y"].asInt(),
				TAG_TEXT,
				livesText,
				playerLivesTracker);
		addObject(livesTextObject);
	}

}
