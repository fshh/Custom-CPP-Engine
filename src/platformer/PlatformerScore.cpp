#include "platformer/PlatformerScore.hpp"
#include "platformer/ScoreRenderComponent.hpp"

PlatformerScore::PlatformerScore(float x, float y, int tag, SDLTextResource* text, std::shared_ptr<PickupCollectibleComponent> tracker):
		GameObject(x, y, 0, 0, tag)
{
	setRenderComponent(std::make_shared<ScoreRenderComponent>(*this, text, tracker));
}


