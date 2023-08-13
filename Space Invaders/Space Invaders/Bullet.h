#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float mvSpeed;
	
public:
	Bullet();
	Bullet(sf::Texture& texture, float dirX, float dirY, float mvSpeed_);
	~Bullet();

	void update();
	void render(sf::RenderTarget* target);
};

