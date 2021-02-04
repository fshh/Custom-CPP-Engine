#include "final/FinalHealthBar.hpp"
#include "final/FinalHealthBarRenderComponent.hpp"

FinalHealthBar::FinalHealthBar(float x, float y, float w, float h, int tag, SDLTextureResource* sprite, std::shared_ptr<FinalHealthComponent> healthTracker):
	GameObject(x, y, w, h, tag)
{
	setRenderComponent(std::make_shared<FinalHealthBarRenderComponent>(*this, sprite, healthTracker));
}

