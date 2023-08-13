#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Enemy
{
private:
	unsigned pointCount;
	sf::Sprite shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Private funcs
	void initVariables();
	void initShape();

public:
	Enemy(sf::Texture* texture, float posX_, float posY_);
	~Enemy();

	//Setter/getter
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

