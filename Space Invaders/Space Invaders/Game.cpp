#include "Game.h"
//private funcs
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invaders!", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("./Textures/bullet.png");
}

void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("./Fonts/28 Days Later.ttf")) {
		std::cout << "Failed to load fonts.\n";
	}
	//Init point
	this->points.setFont(this->font);
	this->points.setCharacterSize(30);
	this->points.setFillColor(sf::Color::White);
	this->points.setString("Test");
}

void Game::initPlayer()
{
	//Init player to middle bottom
	this->player = new Player(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y));
	
}

void Game::initEnemies()
{
	this->spawnTimerMax = 20.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Constructors/Deconstructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}

	//Delete bullets
	for (auto& i : this->bullets) {
		delete i;
	}

	//Delete enemies
	for (auto& i : this->enemies) {
		delete i;
	}
}

//Functions
void Game::run()//Game loop
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed ||
			ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	//TODO: add shooting
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canShoot())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 45.f
			, this->player->getPos().y
			, 0.f, -2.f, 5.f));
	}
}

void Game::updateGUI()
{
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets) {
		bullet->update();

		//When bullet goes out of the screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawnning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->update();

		//When enemy goes out of the screen
		if (enemy->getBounds().top > this->window->getSize().y) {

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i) {
		bool enemyRemoved = false;
		for (size_t j = 0; j < this->bullets.size() && !enemyRemoved; j++) {
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds())) {
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				enemyRemoved = true;
			}
		}
	}

}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->points);
}

void Game::render()
{
	this->window->clear();
	//Draw stuff
	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();

	//Show to screen
	this->window->display();
}


