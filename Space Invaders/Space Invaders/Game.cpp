#include "Game.h"
//private funcs
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invaders!", sf::Style::Close | sf::Style::Titlebar);
}

//Constructors/Deconstructors
Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

//Functions
void Game::run()//Game loop
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::update()
{
	sf::Event ev;
	while (this->window->pollEvent(ev)) 
	{
		if (ev.Event::type == sf::Event::Closed || 
			ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape) 
			this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	//Draw stuff

	this->window->display();
}
