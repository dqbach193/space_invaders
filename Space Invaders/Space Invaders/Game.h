#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include<SFML/Audio.hpp>

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
	sf::Text gameOverGuideText;

	//World
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::SoundBuffer buffer;
	sf::Sound laserGunSFX;
	sf::Music music;
	sf::Music endGameScream;
	bool gameOver;

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
	void initSound();

	void initPlayer();
	void initEnemies();

	void initRestart();

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

