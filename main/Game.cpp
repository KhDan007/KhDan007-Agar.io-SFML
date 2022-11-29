#include "Game.h"

// CONSTRUCTOR
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
	this->initEndGameText();
}

// DESTRUCTOR
Game::~Game()
{
	delete this->window;
}


// INIT
// VARIABLES
void Game::initVariables()
{
	/*
		@return void
		Initialize all default variables
	*/
	this->endGame = false;

	// Setting up balls spawn settings
	this->spawnTimerMax = 30.f;
	this->spawnTimer = spawnTimer;
	this->maxBalls = 10;
}

// WINDOW
void Game::initWindow()
{
	/*
		@return void
		Initialize the main window:
		- Setup width and height of the window
		- Setup the name of the window
		- Setup styles of the window (titlebar and close)

		- Sets the framerate limit
	*/
	this->videomode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videomode, "Game2", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::COULD NOT LOAD: PixellettersFull.ttf" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setCharacterSize(36);
	this->uiText.setString("NONE");
	this->uiText.move(10.f, 0.f);
}

void Game::initEndGameText()
{
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Green);
	this->endGameText.setCharacterSize(100);
	this->endGameText.setString("GAME OVER");

	/*this->endGameText.setPosition(
		sf::Vector2f(
			this->window->getSize().x/2 - this->endGameText.getGlobalBounds().width,
			this->window->getSize().y/2 - this->endGameText.getGlobalBounds().height
		)
	);*/

	this->endGameText.setPosition(
		sf::Vector2f(200, 200)
	);
}

// GETTERS



// SETTERS

// FUNCTIONS
const bool Game::isRunning() const
{
	/*
		@return bool
		Checks is the game running
	*/
	return this->window->isOpen()/* && this->endGame == false */;
}

void Game::pollEvents()
{
	/*
		@return void
		Listens event each frame. If event is:
		- Tap 'X' button at top right: close the window
		- Type 'Escape' key on keyboard: close the window
	*/
	while (this->window->pollEvent(this->SFMLEvent))
	{
		switch (SFMLEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (SFMLEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::spawnBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->balls.size() < this->maxBalls)
		{
			// When we should spawn our balls
			this->balls.push_back(Ball(this->window, this->randBallType()));


			this->spawnTimer = 0.f;
		}
	}

}

const int Game::randBallType()
{
	/*
		@return const int (type of a ball)
		Sets a random type to a ball with:
		- 50% to DEFAULT type
		- 40% to DAMAGING type
		- 10% to HEALING type
	*/

	int type = BallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 50 && randValue <= 90)
	{
		type = BallTypes::DAMAGING;
	}
	else if (randValue > 90 && randValue <= 100)
	{
		type = BallTypes::HEALING;
	}

	return type;
}

// UPDATE
void Game::update()
{
	this->pollEvents(); // Activates EventListener

	if (this->endGame == false)
	{
		this->spawnBalls(); // Spawns a ball

		this->updatePlayer(); // Updates the player

		this->updateCollision();

		this->updateUI();
	}
}

void Game::updatePlayer()
{
	this->player.update(this->window); // Updates everything about the player

	if (this->player.getHP() <= 0)
	{
		this->endGame = true;
	}
}

void Game::updateCollision()
{
	/*
		@return void
		Checks the collision between player and balls
	*/
	for (size_t i{}; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallTypes::DEFAULT:
				// Add points
				player.addPoints(1);
				break;
			case BallTypes::DAMAGING:
				// Remove 1 hp
				player.takeDamage(1);
				break;
			case BallTypes::HEALING:
				// Gain 1 hp
				player.gainHealth(1);
				break;
			}

			// Remove the ball
			this->balls.erase(this->balls.begin() + i);
		}
	}
}


void Game::updateUI()
{
	std::stringstream ss;
	ss << "Points: " << player.getPoints() << "\n"
		<< "Health: " << player.getHP() << " / " << player.getHPMax();

	this->uiText.setString(ss.str());
}

// RENDER
void Game::render()
{
	this->window->clear(); // Clear old frame

	// Render some stuff:
	this->player.render(this->window); // Render the player

	// Render balls
	for (auto i : this->balls)
	{
		i.render(this->window);
	}

	// Render text
	this->renderUIText(this->window);

	// Render endgame
	if (this->endGame == true)
	{
		this->renderEndGame(this->window);
	}

	this->window->display(); // Say to SFML that we need to display everything we draw
}

void Game::renderUIText(sf::RenderTarget* target)
{
	target->draw(this->uiText);
}

void Game::renderEndGame(sf::RenderTarget* target) {
	target->draw(this->endGameText);
}
