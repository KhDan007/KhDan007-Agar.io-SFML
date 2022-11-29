#include "Ball.h"

void Ball::initShape(const sf::RenderWindow* window)
{
	/*
		@return void
		Initialize a shape:
		- Set its radius
		- Set a random color
		- Set a random position
	*/
	
	// Setting up a radius
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	

	// Setting up a color which depends on type
	sf::Color color;
	
	switch (this->type)
	{
	case BallTypes::DEFAULT:
		//color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		color = sf::Color::White;
		break;
	case BallTypes::DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case BallTypes::HEALING:
		color = sf::Color(55, 235, 84);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}

	this->shape.setFillColor(color);


	// Setting up a random position
	float randomX = static_cast<float>(rand() % window->getSize().x);
	float randomY = static_cast<float>(rand() % window->getSize().y);

	if (randomX + this->shape.getGlobalBounds().width > window->getSize().x)
	{
		randomX = randomX - this->shape.getGlobalBounds().width;
	}
	if (randomY + this->shape.getGlobalBounds().height > window->getSize().y)
	{
		randomY = randomY - this->shape.getGlobalBounds().height;
	}

	this->shape.setPosition(
		sf::Vector2f(randomX, randomY)
	);
}

Ball::Ball(const sf::RenderWindow* window, int type)
	: type(type)
{
	this->initShape(window);
}

Ball::~Ball()
{
}

// GETTERS
const sf::CircleShape& Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}


// FUNCTIONS
void Ball::update()
{
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
