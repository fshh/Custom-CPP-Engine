#ifndef INCLUDE_PLATFORMER_PLATFORMERPLAYERINPUTCOMPONENT_HPP_
#define INCLUDE_PLATFORMER_PLATFORMERPLAYERINPUTCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "base/Resource.hpp"

class PlatformerPlayerInputComponent: public GenericComponent {
public:
	PlatformerPlayerInputComponent(GameObject& _gameObject, float _speed, float _jumpSpeed, float _gravity, SDLMixChunkResource* jumpSound);

	virtual void update(Level& level) override;

private:
	float speed;
	float jumpSpeed;
	float gravity;
	SDLMixChunkResource* mJumpSound;
};



#endif /* INCLUDE_PLATFORMER_PLATFORMERPLAYERINPUTCOMPONENT_HPP_ */
