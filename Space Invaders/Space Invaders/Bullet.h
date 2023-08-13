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
	Bullet(sf::Texture* texture, float pos_X, float pos_Y, float dirX, float dirY, float mvSpeed_);
	~Bullet();

	//Setter/Getters
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

