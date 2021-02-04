#ifndef INCLUDE_PLATFORMER_PLATFORMERPLAYERRENDERCOMPONENT_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERPLAYERRENDERCOMPONENT_HPP_

#include "base/SpriteSheetRenderComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Resource.hpp"

class PlatformerPlayerRenderComponent: public SpriteSheetRenderComponent {
public:
	PlatformerPlayerRenderComponent(GameObject& gameObject, float size, SDLSpriteSheetResource* _spriteSheet);

	virtual void render(SDL_Renderer* renderer) override;

private:
	float oldX;
	float oldY;
};

#endif /* INCLUDE_PLATFORMER_PLATFORMERPLAYERRENDERCOMPONENT_HPP_ */
