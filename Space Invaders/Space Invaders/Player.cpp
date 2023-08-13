#include "Player.h"

void Player::initVariables()
{
	this->mvSpeed = 10.f;
	this->bulletCDmax = 5.f;
	this->bulletCD = this->bulletCDmax;
	this->sprite.setPosition(100.f, 100.f);
}

void Player::initTexture()
{
	//Load texture from file
	if (!this->texture.loadFromFile("./Textures/amongusShip.png")) {
		std::cout << "ERROR::Player::initTexture: Failed loading texture.\n";
	}
}

void Player::initSprite()
{
	//Set texture to sprite 
	this->sprite.setTexture(this->texture);

	//Resize sprite
	this->sprite.scale(0.3f, 0.3f);

}

Player::Player(sf::Vector2f pos_)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	pos_.x -= this->sprite.getGlobalBounds().width * this->sprite.getScale().x * 2;
	pos_.y -= this->sprite.getGlobalBounds().height;
	this->sprite.setPosition(pos_);
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->mvSpeed * dirX, this->mvSpeed * dirY);
}

const bool Player::canShoot()
{
	if (this->bulletCD >= this->bulletCDmax) {
		this->bulletCD = 0.f;
		return true;
	}
	return false;
}

void Player::updateBullet()
{
	if(this->bulletCD < this->bulletCDmax)
		this->bulletCD += 0.5f;
}

void Player::update()
{
	this->updateBullet();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
