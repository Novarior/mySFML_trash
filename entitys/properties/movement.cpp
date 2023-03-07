#include "movement.hpp"

Movement::Movement(sf::RectangleShape& sprite, float accel, float decel, float maxVel):
	sprite(sprite), acceleration(accel), deceleration(decel), maxVelocity(maxVel)
{

}

Movement::~Movement()
{

}

sf::Vector2f Movement::getVelocity()
{
	return this->velocity;
}

void Movement::stopVelocity()
{
	this->velocity = sf::Vector2f();
}
void Movement::stopVelocityX()
{
	this->velocity.x = 0.f;
}
void Movement::stopVelocityY()
{
	this->velocity.y = 0.f;
}
void Movement::move(sf::Vector2f direction, const float& deltatime)
{
	this->velocity.x += this->acceleration * direction.x * deltatime;
	this->velocity.y += this->acceleration * direction.y * deltatime;
}

void Movement::update(const float& deltatime, TileMap* map)
{
	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Deceleration
		this->velocity.x -= this->deceleration * deltatime;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f) //Check for negative x
	{
		//Deceleration
		this->velocity.x += deceleration * deltatime;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}

	if (this->velocity.y > 0.f) //Check for positive y
	{
		//Deceleration
		this->velocity.y -= this->deceleration * deltatime;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;
	}
	else if (this->velocity.y < 0.f) //Check for negative y
	{
		//Deceleration
		this->velocity.y += deceleration * deltatime;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
	}

	this->sprite.move(velocity.x, velocity.y);
	
	this->updateCollison(deltatime, map);
}

void Movement::updateCollison(const float& deltatime, TileMap* map)
{
	sf::Vector2f bufferPos = this->sprite.getPosition();
	//chek left bound map
	if (this->sprite.getPosition().x < 0)
	{
		this->stopVelocityX();
		this->sprite.setPosition(0.f, bufferPos.y);
	}
	else if (bufferPos.x + this->sprite.getGlobalBounds().width > map->getMapSizeOnFloat().x)
	{
		this->stopVelocityX();
		this->sprite.setPosition(map->getMapSizeOnFloat().x - this->sprite.getGlobalBounds().width, bufferPos.y);
	}

	if (this->sprite.getPosition().y < 0)
	{
		this->stopVelocityY();
		this->sprite.setPosition(bufferPos.x, 0.f);
	}
	else if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height > map->getMapSizeOnFloat().y)
	{
		this->stopVelocityY();
		this->sprite.setPosition(bufferPos.x, map->getMapSizeOnFloat().y - this->sprite.getGlobalBounds().height);
	}

	/*
		if (this->sprite.getPosition().y < 1000.0f) {
			this->velocity.y += this->deceleration * deltatime;
			this->m_state = Fall;
		}
		else if (this->sprite.getPosition().y > 1000.0f) {
			this->stopVelocityY();
			this->sprite.setPosition(sf::Vector2f(bufferPos.x, 1000));
			this->m_state = Idle;
		}
	*/
}

void Movement::jump(const float& dealtatime)
{
	if (this->m_state == Idle)
	{
		this->velocity.y = (-1) * this->acceleration * 100 * dealtatime;

		this->m_state = Jump;
	}
	else {}
}
