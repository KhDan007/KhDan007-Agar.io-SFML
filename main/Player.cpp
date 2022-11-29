#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = hpMax;
	this->points = 0;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

// CONSTRUCTOR
Player::Player(float x, float y)
{
	/*
		Constructs the object.
	*/

	this->initVariables();
	this->initShape();
	this->shape.setPosition(x, y);
}

// DESTRUCTOR
Player::~Player()
{
}

// GETTERS
const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

int Player::getPoints()
{
	return this->points;
}

int Player::getHP()
{
	return this->hp;
}

int Player::getHPMax()
{
	return this->hpMax;
}


// FUNCTIONS
void Player::addPoints(int number)
{
	this->points += number;
}

void Player::takeDamage(int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(int health)
{
	if (this->hp < this->hpMax)
	{
		this->hp += health;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = hpMax;
	}
}


// UPDATE
void Player::update(const sf::RenderTarget* target)
{
	/*
		@return void
		Updates everything about the player:
		- Movement through keyboard pressing
		- Window bounds collision
	*/
	
	this->updateInput();
	
	// Window bounds collision
	this->updateWindowBoundsCollision(target);


}

// KEYBOARD INPUT
void Player::updateInput()
{
	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	// Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	// Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

// WINDOW BOUNDS COLLISION
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Left
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	// Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}
	// Top
	if (this->shape.getGlobalBounds().top <= 0.f)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	// Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}
}

//RENDER
void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


