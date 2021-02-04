#ifndef INCLUDE_FINAL_FINALBLOCK_HPP_
#define INCLUDE_FINAL_FINALBLOCK_HPP_

#include "base/Resource.hpp"
#include "base/GameObject.hpp"
#include <SDL.h>

//! \brief A static block that makes up part of the level terrain
class FinalBlock: public GameObject {
public:
	FinalBlock(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID);
};

//! \brief A block representing the desert ground
class FinalBlockFloor: public FinalBlock {
public:
	FinalBlockFloor(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief A block representing a cliff wall
class FinalBlockWall: public FinalBlock {
public:
	FinalBlockWall(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed below walls
class FinalBlockWallBorderBottom: public FinalBlock {
public:
	FinalBlockWallBorderBottom(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed above walls
class FinalBlockWallBorderTop: public FinalBlock {
public:
	FinalBlockWallBorderTop(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed to the left of walls
class FinalBlockWallBorderLeft: public FinalBlock {
public:
	FinalBlockWallBorderLeft(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed to the right of walls
class FinalBlockWallBorderRight: public FinalBlock {
public:
	FinalBlockWallBorderRight(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed on the bottom left corner of walls
class FinalBlockWallBorderBottomLeft: public FinalBlock {
public:
	FinalBlockWallBorderBottomLeft(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief Decoration block placed on the bottom right corner of walls
class FinalBlockWallBorderBottomRight: public FinalBlock {
public:
	FinalBlockWallBorderBottomRight(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};

//! \brief A piece of desert scenery such as a cactus, skull, or brush
class FinalBlockDecoration: public FinalBlock {
public:
	FinalBlockDecoration(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet);
};



#endif /* INCLUDE_FINAL_FINALBLOCK_HPP_ */
