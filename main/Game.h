#pragma once

// Including Input/Output stream
#include <iostream>

// Including Vectors
#include <vector>

// Including CTIME
#include <ctime>

// Including sstream
#include <sstream>

// Including Player class
#include "Player.h"

// Including Ball class
#include "Ball.h"



class Game
{
private:
	// MEMBER VARIABLES
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	bool endGame;

	sf::Event SFMLEvent;

	Player player;

	std::vector<Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;

	// Fonts & Text
	sf::Font font;
	sf::Text uiText;
	sf::Text endGameText;

	// PRIVATE FUNCTIONS
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
	void initEndGameText();

public:
	// Constuctor
	Game();
	// Destructor
	~Game();

	// GETTERS
	

	// SETTERS


	// Functions
	const bool isRunning() const;
	void pollEvents();

	void spawnBalls();
	const int randBallType();

	void update();
	void updateCollision();
	void updatePlayer();
	void updateUI();

	void render();
	void renderUIText(sf::RenderTarget* target);
	void renderEndGame(sf::RenderTarget* target);
};

