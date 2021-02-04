#include "final/FinalHealthHUD.hpp"
#include "base/SpriteRenderComponent.hpp"

FinalHealthHUD::FinalHealthHUD(float x, float y, float w, float h, int tag, SDLTextureResource* sprite):
	GameObject(x, y, w, h, tag)
{
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
}


