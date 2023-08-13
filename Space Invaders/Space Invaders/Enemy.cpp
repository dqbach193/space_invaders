#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
}

void Enemy::initVariables()
{
	this->type = 0;
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

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
