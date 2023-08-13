#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Game
{
private:
	sf::RenderWindow* window;

	//Private functions
	void initWindow();
public:
	Game();
	~Game();

	//Functions
	void run();
	
	void update();
	void render();
};

