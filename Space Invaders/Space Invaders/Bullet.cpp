#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::Bullet(sf::Texture& texture, float dirX, float dirY, float mvSpeed_)
{
	this->shape.setTexture(texture);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->mvSpeed = mvSpeed_;
}
Bullet::~Bullet()
{
}

void Bullet::update()
{
	//Update movements
	this->shape.move(this->mvSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
