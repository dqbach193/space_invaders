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

void Game::initPlayer()
{
	//Init player to middle bottom
	this->player = new Player(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y));
	this->enemy = new Enemy(20.f, 20.f);
}

//Constructors/Deconstructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y
			, 0.f, -1.f, 5.f));
	}
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

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
}

void Game::render()
{
	this->window->clear();
	//Draw stuff
	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	this->enemy->render(this->window);
	//Show to screen
	this->window->display();
}
