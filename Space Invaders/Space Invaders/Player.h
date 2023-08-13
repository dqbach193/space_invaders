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
	
	//Private functions
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	//Setter/getter
	const sf::Vector2f& getPos() const;

	//Functions
	void move(const float dirX, const float dirY);
	void update();
	void render(sf::RenderTarget& target);
};

