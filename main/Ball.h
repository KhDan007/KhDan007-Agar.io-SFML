#pragma once

// Including SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NTYPES};

class Ball
{
private:
	// Member variables
	sf::CircleShape shape;

	int type;


	// Init functions
	void initShape(const sf::RenderWindow* window);

public:
	Ball(const sf::RenderWindow* window, int type);
	virtual ~Ball();


	// GETTERS
	const sf::CircleShape& getShape() const;

	const int& getType() const;

	// Functions

	void update();
	void render(sf::RenderTarget* target);
};

