#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float mvSpeed;

	float bulletCD;
	float bulletCDmax;

	int hp;
	int hpMax;
	
	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player(sf::Vector2f pos_);
	~Player();

	//Setter/getter
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getHP() const;
	const int getHPMax() const;

	void setPos(const sf::Vector2f pos);
	void setPos(const float posX_, const float posY_);
	void setHP(const int hp);
	void loseHP(const int value);
	//Functions
	void move(const float dirX, const float dirY); 

	const bool canShoot();
	void updateBullet();
	void update();
	void render(sf::RenderTarget& target);
};

