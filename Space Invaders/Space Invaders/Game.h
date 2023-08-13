#pragma once

#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	
	//GUI
	sf::Font font;
	sf::Text points;

	//Player variables
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();

	void initPlayer();
	void initEnemies();

public:
	Game();
	~Game();

	//Functions
	void run();
	
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateEnemiesAndCombat();
	void update();
	void render();
	void renderGUI();
};

