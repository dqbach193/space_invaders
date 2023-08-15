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
	this->textures["ENEMY"] = new sf::Texture();
	this->textures["ENEMY"]->loadFromFile("./Textures/enemy.png");
	this->textures["ENEMY2"] = new sf::Texture();
	this->textures["ENEMY2"]->loadFromFile("./Textures/enemy2.png");
	this->textures["ENEMY3"] = new sf::Texture();
	this->textures["ENEMY3"]->loadFromFile("./Textures/enemy3.png");
	this->textures["PHAN"] = new sf::Texture();
	this->textures["PHAN"]->loadFromFile("./Textures/phan.png");
	this->textures["DEFAULT"] = new sf::Texture();
	this->textures["DEFAULT"]->loadFromFile("./Textures/amongusShip.png");

	this->enemyTexture = this->textures["ENEMY"];
}

void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("./Fonts/28 Days Later.ttf")) {
		std::cout << "Failed to load fonts.\n";
	}
	//Init point
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(35.f);
	this->pointsText.setFillColor(sf::Color::White);
	this->pointsText.setOutlineColor(sf::Color::Black);
	this->pointsText.setOutlineThickness(2.f);

	//Init Gameover
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(90.f);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setOutlineColor(sf::Color::Black);
	this->gameOverText.setOutlineThickness(8.f);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width/2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init game over guide text
	this->gameOverGuideText.setFont(this->font);
	this->gameOverGuideText.setCharacterSize(30.f);
	this->gameOverGuideText.setFillColor(sf::Color::Red);
	this->gameOverGuideText.setOutlineColor(sf::Color::Black);
	this->gameOverGuideText.setOutlineThickness(4.f);
	this->gameOverGuideText.setString("F1 to play again or ESC to quit");
	this->gameOverGuideText.setPosition(this->window->getSize().x / 2.f - this->gameOverGuideText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f + this->gameOverText.getGlobalBounds().height / 2.f);

	this->pausedText.setFont(this->font);
	this->pausedText.setCharacterSize(90.f);
	this->pausedText.setFillColor(sf::Color::White);
	this->pausedText.setOutlineColor(sf::Color::Black);
	this->pausedText.setOutlineThickness(6.f);
	this->pausedText.setString("Paused");
	this->pausedText.setPosition(this->window->getSize().x / 2.f - this->pausedText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->pausedText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHP.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHP.setFillColor(sf::Color::Red);
	this->playerHP.setPosition(sf::Vector2f(20.f, 50.f));

	this->playerHPBack = this->playerHP;
	this->playerHPBack.setFillColor(sf::Color(25, 25, 25, 255));
}

void Game::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("./Textures/background.jpg")) {
		std::cout << "Failed to load background.\n";
	}
	this->background.scale(0.5f, 0.5f);
	this->background.setTexture(this->backgroundTexture);
}

void Game::initSystem()
{
	this->points = 0;
}

void Game::initSound()
{
	if (!this->music.openFromFile("./Audios/28-days-later-ost.mp3")){
		std::cout << "Error opening OST";
	} // error
	if (!this->endGameScream.openFromFile("./Audios/eren-scream.mp3")) {
		std::cout << "Error opening Sound effect: eren-scream.mp3";
	} // error
	if (!this->buffer.loadFromFile("./Audios/laser-gun.mp3")) {
		std::cout << "Error opening Sound effect: laser-gun.mp3";
	} // error
	
	this->laserGunSFX.setBuffer(buffer);
	this->laserGunSFX.setPitch(2.f);
	this->laserGunSFX.setVolume(50.f);
	this->music.setVolume(50.f);
	this->music.play();
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

void Game::initRestart() {
	this->initGUI();
	this->initSystem();
	this->initPlayer();
	this->initEnemies();
	this->gameOver = false;
}

//Constructors/Deconstructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initBackground();
	this->initSystem();
	this->initPlayer();
	this->initEnemies();
	this->initSound();
	this->gameOver = false;
	this->pause = false;
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
		this->updatePollEvents();
		if (this->player->getHP() > 0) {
			if (!pause){
				this->update();
		}
			this->render();
		}
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
		//TODO: add a play again fucntion
		if (gameOver) {//Only F1 when game is over
			if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::F1) {
				//this->initRestart();
			}
		}

		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::F2) {
			this->pause = true;
		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::F3) {
			this->pause = false;
		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::F4) {
			this->music.pause();
		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::F5) {
			this->music.play();
		}
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
		this->laserGunSFX.play();
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 45.f
			, this->player->getPos().y
			, 0.f, -2.f, 5.f));
	}

	//TODO: add changing skins here
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		this->enemyTexture = this->textures["ENEMY"];
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		this->enemyTexture = this->textures["ENEMY2"];
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		this->enemyTexture = this->textures["ENEMY3"];
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		this->player->setTexture(this->textures["PHAN"]);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->player->setTexture(this->textures["DEFAULT"]);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss <<"Points " << this->points;

	
	this->pointsText.setString(ss.str());

	//Update HP Bar
	float hpPercent = static_cast<float> (this->player->getHP()) / this->player->getHPMax();
	this->playerHP.setSize(sf::Vector2f(300.f * hpPercent,this->playerHP.getSize().y));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	//Left screen collision
	if (this->player->getBounds().left < 0.f) {
		this->player->setPos(0.f, this->player->getBounds().top);
	}//Right screen collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPos(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top screen collision
	if (this->player->getBounds().top < 0.f) {
		this->player->setPos(this->player->getBounds().left, 0.f);
	}//Bottom screen collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPos(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
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

void Game::updateEnemies()
{
	//Spawnning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(this->enemyTexture, rand() % this->window->getSize().x - 20.f, -100.f));
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
		}//Enemy collides with player
		else if (enemy->getBounds().intersects(this->player->getBounds())){
			this->player->loseHP(this->enemies.at(counter)->getDamage());

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
				this->points += this->enemies[i]->getPoints();

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
	this->updateInput();
	this->updateCollision();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointsText);
	this->window->draw(this->playerHPBack);
	this->window->draw(this->playerHP);
}

void Game::renderBackground()
{
	this->window->draw(this->background);
}

void Game::render()
{
	this->window->clear();
	//Draw stuff
	this->renderBackground();

	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();

	if (this->pause) {
		this->window->draw(this->pausedText);
	}

	//Game over screen
	if (this->player->getHP() <= 0) {
		this->window->draw(this->gameOverText);
		this->window->draw(this->gameOverGuideText);
		this->endGameScream.play();
		this->gameOver = true;
	}

	//Show to screen
	this->window->display();
}


