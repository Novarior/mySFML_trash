#include "player.hpp"

Player::Player(const float grid)
{
    this->sprite.setFillColor(sf::Color::Red);
    this->sprite.setPosition(0, 0);
    this->sprite.setSize(sf::Vector2f(grid * 1.5f, grid * 1.5f));


    this->e_movement = new Movement(this->sprite, 16.f, 7.f, 5.f, grid);
    this->e_hitbox = new HitboxCounter(this->sprite, sf::Vector2f(grid * 1.5f, grid * 1.5f), sf::Vector2f());
}


Player::Player(const sf::Vector2f basePos, const float grid)
{
    this->sprite.setFillColor(sf::Color::Red);
    this->sprite.setPosition(basePos);
    this->sprite.setSize(sf::Vector2f(grid * 1.5f, grid * 1.5f));


    this->e_movement = new Movement(this->sprite, 16.f, 7.f, 5.f, grid);
    this->e_hitbox = new HitboxCounter(this->sprite, sf::Vector2f(grid * 1.5f, grid * 1.5f), sf::Vector2f());
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