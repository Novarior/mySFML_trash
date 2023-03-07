#include "player.hpp"

Player::Player()
{
    this->sprite.setFillColor(sf::Color::Red);
    this->sprite.setPosition(0, 0);
    this->sprite.setSize(sf::Vector2f(20.f, 20.f));


    this->e_movement = new Movement(this->sprite, 16.f, 7.f, 5.f, *this);
    this->e_hitbox = new HitboxCounter(this->sprite, sf::Vector2f(64, 64), sf::Vector2f(32, 32));
}

Player::~Player()
{
    delete this->e_movement;
    delete this->e_hitbox;
}

void Player::e_update(TileMap* map, const float& deltatime)
{
    if (this->isAlive) {
        this->e_movement->update(deltatime, map);
        this->e_hitbox->update();
    }
}

void Player::e_render(sf::RenderTarget* target)
{
    this->e_hitbox->render(target);
    target->draw(this->sprite);
}