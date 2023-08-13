#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
	this->type = 0;
	this->speed = 5.f;
	this->hpMax = 10;
	this->hp = 0;
	this->damage = 1;
	this->points = 5;
}

Enemy::Enemy(float posX_, float posY_)
{
	this->initShape();
	this->initVariables();
	this->shape.setPosition(posX_, posY_);
}

Enemy::~Enemy()
{
}


//Setter/getter
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
