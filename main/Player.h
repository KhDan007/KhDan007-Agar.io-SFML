#pragma once

#include "Ball.h"


class Player
{
private:
	// Member variables
	sf::RectangleShape shape;

	float movementSpeed;
	int hp;
	int hpMax;
	int points;


	// Private functions
	void initVariables();
	void initShape();

public:
	Player(float x = 375.f, float y = 275.f);
	~Player();

	// GETTERS
	const sf::RectangleShape& getShape() const;

	int getPoints();
	int getHP();
	int getHPMax();

	// Functions
	void addPoints(int number);
	void takeDamage(int damage);
	void gainHealth(int health);

	void update(const sf::RenderTarget* target);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);

	void render(sf::RenderTarget* target);
};

