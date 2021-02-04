#include "final/FinalCrosshair.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "base/CursorComponent.hpp"

FinalCrosshair::FinalCrosshair(float size, int tag, SDLTextureResource* sprite):
	GameObject(0, 0, size, size, tag)
{
	addGenericComponent(std::make_shared<CursorComponent>(*this));
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
}


