#ifndef INCLUDE_BASE_SPRITERENDERCOMPONENT_HPP_
#define INCLUDE_BASE_SPRITERENDERCOMPONENT_HPP_

#include "base/RenderComponent.hpp"
#include "ResourceManager.hpp"
#include <SDL.h>
#include <string>

//! \brief Handles rendering a game object using a single sprite.
class SpriteRenderComponent: public RenderComponent {
public:

	SpriteRenderComponent(GameObject & gameObject, SDLTextureResource* _sprite, double angle = 0);

  virtual void render(SDL_Renderer * renderer) override;

  inline void setRotation(double degrees) { mAngle = degrees; }

protected:
  SDLTextureResource* sprite;
  double mAngle;
};


#endif /* INCLUDE_BASE_SPRITERENDERCOMPONENT_HPP_ */
