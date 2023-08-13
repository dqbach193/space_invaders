#pragma once
#include<SFML/Graphics.hpp>
class Enemy
{
private:
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Private funcs
	void initShape();
	void initVariables();

public:
	Enemy(float posX_, float posY_);
	~Enemy();

	//Setter/getter
	const sf::FloatRect getBounds() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

