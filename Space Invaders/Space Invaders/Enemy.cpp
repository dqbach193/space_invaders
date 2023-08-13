#include "Enemy.h"


void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = static_cast<float>(10 - this->pointCount);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	//this->shape.setRadius(this->pointCount * 3);
	//this->shape.setPointCount(this->pointCount);
	//this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(sf::Texture* texture, float posX_, float posY_)
{
	this->shape.setTexture(*texture);
	this->initVariables();
	this->initShape();
	float scale = this->getPoints() / 100.f;
	this->shape.setScale(scale, scale);
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

const int& Enemy::getPoints() const
{
	// TODO: insert return statement here
	return this->points;
}

const int& Enemy::getDamage() const
{
	// TODO: insert return statement here
	return this->damage;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed * 1.5);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
