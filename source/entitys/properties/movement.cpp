#include "movement.hpp"

MovementComponent::MovementComponent(sf::Sprite& sprite, const float acceleration, const float deceleration, const float maxVelocity) :
	sprite(sprite) {
	this->acceleration = acceleration;
	this->deceleration = deceleration;
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent() {  }

//Accessors
const float& MovementComponent::getMaxVelocity() const {
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const {
	return this->velocity;
}

//Functions
void MovementComponent::stopVelocity() {/* Resets the velocity to 0.*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX() {/* Resets the velocity x to 0.*/
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {/* Resets the velocity y to 0.*/
	this->velocity.y = 0.f;
}

void MovementComponent::move(const float& dir_x, const float& dir_y, const float& delta_time) {
	/* Accelerating a sprite until it reaches the max velocity. */
	this->velocity.x += this->acceleration * delta_time * dir_x;
	this->velocity.y += this->acceleration * delta_time * dir_y;
}

void MovementComponent::update(const float& delta_time) {
	//Decelerates the sprite and controls the maximum velocity.
	//Moves the sprite.
	if (this->velocity.x > 0.f) {//Check for positive x
		//Deceleration
		this->velocity.x -= this->deceleration * delta_time;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

	}
	else if (this->velocity.x < 0.f) {//Check for negative x
		//Deceleration
		this->velocity.x += deceleration * delta_time;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}
	if (this->velocity.y > 0.f) {//Check for positive y
		//Deceleration
		this->velocity.y -= this->deceleration * delta_time;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;
	}
	else if (this->velocity.y < 0.f) {//Check for negative y
		//Deceleration
		this->velocity.y += deceleration * delta_time;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
	}
	//Final move
	this->sprite.move(this->velocity.x, this->velocity.y); //Uses velocity
}