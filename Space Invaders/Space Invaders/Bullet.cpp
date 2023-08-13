#include "Bullet.h"

Bullet::Bullet() {
	this->shape.scale(0.2f, 0.2f);
}

Bullet::Bullet(sf::Texture* texture,float pos_X, float pos_Y, float dirX, float dirY, float mvSpeed_)
{
	this->shape.scale(0.2f, 0.2f);
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_X, pos_Y);

	this->direction.x = dirX;
	this->direction.y = dirY;
	this->mvSpeed = mvSpeed_;
}
Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
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
