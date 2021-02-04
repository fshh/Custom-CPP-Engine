#ifndef INCLUDE_EDITOR_EDITOROBJECT_HPP_
#define INCLUDE_EDITOR_EDITOROBJECT_HPP_

#include "base/GameObject.hpp"
#include "base/ResourceManager.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include "base/RectRenderComponent.hpp"

static const int TAG_EDITOR = 0;

enum class ObjectType {
	INVALID = -1,
	EMPTY = 0,
	PLAYER = 1,
	GOAL = 2,
	COLLECTIBLE = 3,
	ENEMY = 4,
	SKY = 5,
	STONE = 6,
	GRASS = 7,
	BLOCK = 6,
	HEALTH = 3
};

//! \brief Represents an object in the editor.
//! Stores the type of object as initializes the physics component.
//! DOES NOT initialize the renderer for this component, should be specified in child classes.
class EditorObject : public GameObject {
public:
	EditorObject(float x, float y, float size, ObjectType _type): GameObject(x,y,size,size,TAG_EDITOR) {
		type = _type;
		setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, true));
	}

	ObjectType getObjectType() { return type; }

private:
	ObjectType type;
};

//! \brief An EditorObject using a SpriteRenderer
class SpriteEditorObject: public EditorObject {
public:
	SpriteEditorObject(float x, float y, float size, ObjectType _type, SDLTextureResource* sprite):
		EditorObject(x,y,size,_type)
	{
		setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite));
	}
};

//! \brief An EditorObject using a SpriteSheetRenderer
class SpriteSheetEditorObject : public EditorObject {
public:
	SpriteSheetEditorObject(float x, float y, float size, ObjectType _type, SDLSpriteSheetResource* spriteSheet, int spriteID):
		EditorObject(x,y,size,_type)
	{
		setRenderComponent(std::make_shared<SpriteSheetRenderComponent>(*this, size, size, spriteSheet, spriteID));
	}
};

//! \brief An EditorObject using a SpriteSheetRenderer
class RectEditorObject : public EditorObject {
public:
	RectEditorObject(float x, float y, float size, ObjectType _type, Uint8 r, Uint8 g, Uint8 b):
		EditorObject(x,y,size,_type)
	{
		setRenderComponent(std::make_shared<RectRenderComponent>(*this, r, g, b));
	}
};


#endif /* INCLUDE_EDITOR_EDITOROBJECT_HPP_ */
