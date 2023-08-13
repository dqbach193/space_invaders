#pragma once
#include"Player.h"

class Game
{
private:
	sf::RenderWindow* window;

	//Player variables
	Player* player;

	//Private functions
	void initWindow();
	void initPlayer();

public:
	Game();
	~Game();

	//Functions
	void run();
	
	void update();
	void render();
};

