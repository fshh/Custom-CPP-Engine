#include "final/FinalBullet.hpp"
#include "base/DieOnCollideComponent.hpp"
#include "base/SpriteRenderComponent.hpp"
#include "base/TinyMath.hpp"
#include "base/Tags.hpp"
#include <vector>

Bullet::Bullet(int shooterTag, TinyMath::Vector2D<float> dir, float speed, int _damage, float x, float y, float scale, int tag, SDLTextureResource* sprite):
	GameObject(x - (sprite->w() * scale) / 2.0f, y - (sprite->h() * scale) / 2.0f, sprite->w() * scale, sprite->h() * scale, tag),
	damage(_damage)
{
	setPhysicsComponent(std::make_shared<PhysicsComponent>(*this, false));
	setRenderComponent(std::make_shared<SpriteRenderComponent>(*this, sprite, TinyMath::AngleBetweenDegrees(TinyMath::Vector2D<float>{1,0}, dir)));
	// Bullets do not collide with each other, collectibles, or goals.
	addGenericComponent(std::make_shared<DieOnCollideComponent>(*this,
			std::vector<int> {shooterTag, Tags::tagOf("Enemy_Bullet"), Tags::tagOf("Player_Bullet"), Tags::tagOf("Collectible"), Tags::tagOf("Goal")}));

	physicsComponent()->setVx(dir.x * speed);
	physicsComponent()->setVy(dir.y * speed);
}
