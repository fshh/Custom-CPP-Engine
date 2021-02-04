#ifndef BASE_SPRITE_SHEET_RENDER_COMPONENT
#define BASE_SPRITE_SHEET_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include "ResourceManager.hpp"
#include <SDL.h>
#include <string>

//! \brief Handles rendering a game object using a sprite from a spritesheet.
class SpriteSheetRenderComponent: public RenderComponent {
public:

	SpriteSheetRenderComponent(GameObject & gameObject, float _width, float _height, SDLSpriteSheetResource* _spriteSheet, unsigned int _spriteID);
  
  virtual void render(SDL_Renderer * renderer) override;

  inline void setSpriteID(unsigned int id) { spriteID = id; }
  inline unsigned int getSpriteID() const { return spriteID; }

  inline void setFlipX(bool flip) { flipX = flip; }
  inline void setRotation(double degrees) { angle = degrees; }

private:
  float width;
  float height;
  SDLSpriteSheetResource* spriteSheet;
  unsigned int spriteID;
  bool flipX;
  double angle;
  
};

#endif
