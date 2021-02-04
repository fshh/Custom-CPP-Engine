#ifndef INCLUDE_BLOCK_HPP_
#define INCLUDE_BLOCK_HPP_

#include "base/Resource.hpp"
#include "base/GameObject.hpp"
#include <SDL.h>

//! \brief A static block that makes up part of the level terrain
class Block: public GameObject {
public:
	Block(float x, float y, float size, int tag, bool solid, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID);
};

//! \brief A block representing grass
class PlatformerBlockGrass: public Block {
public:
	PlatformerBlockGrass(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief A block representing stone
class PlatformerBlockStone: public Block {
public:
	PlatformerBlockStone(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

#endif /* INCLUDE_BLOCK_HPP_ */
