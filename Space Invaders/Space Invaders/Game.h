#pragma once

#include<map>
#include<string>
#include<sstream>
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
	sf::Text pointsText;

	sf::Text gameOverText;

	//World
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Player variables
	Player* player;
	unsigned points;

	//Player GUI
	sf::RectangleShape playerHP;
	sf::RectangleShape playerHPBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	sf::Texture* enemyTexture;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystem();

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
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderBackground();
	void render();
	void renderGUI();
};

