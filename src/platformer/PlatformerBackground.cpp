#include "platformer/PlatformerBackground.hpp"
#include "base/SpriteSheetRenderComponent.hpp"

PlatformerBackground::PlatformerBackground(float width, float height, int tag, SDLSpriteSheetResource* spriteSheet, unsigned int spriteID):
	GameObject(0, 0, width, height, tag)
{
	setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, width, height, spriteSheet, spriteID));
}


