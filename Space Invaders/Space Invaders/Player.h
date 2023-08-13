#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	
	//Private functions
	void initTexture();
	void initSprite();
public:
	Player();
	~Player();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

