#include "final/FinalBlock.hpp"
#include "base/SpriteSheetRenderComponent.hpp"

FinalBlock::FinalBlock(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID):
	GameObject(x, y, size, size, tag)
{
		setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, size, size, spriteSheet, spriteID));
}

FinalBlockFloor::FinalBlockFloor(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, rand() % 5)
{
}

FinalBlockWall::FinalBlockWall(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, (rand() % 4) + 5)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, true));
}

FinalBlockWallBorderBottom::FinalBlockWallBorderBottom(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 9)
{
}

FinalBlockWallBorderTop::FinalBlockWallBorderTop(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 10)
{
}

FinalBlockWallBorderLeft::FinalBlockWallBorderLeft(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 11)
{
}

FinalBlockWallBorderRight::FinalBlockWallBorderRight(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 12)
{
}

FinalBlockWallBorderBottomLeft::FinalBlockWallBorderBottomLeft(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 13)
{
}

FinalBlockWallBorderBottomRight::FinalBlockWallBorderBottomRight(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, 14)
{
}

FinalBlockDecoration::FinalBlockDecoration(float x, float y, float size, int tag, SDLSpriteSheetResource* spriteSheet):
	FinalBlock(x, y, size, tag, spriteSheet, rand() % 5 + 15)
{
}
