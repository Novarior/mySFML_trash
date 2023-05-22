#include "player.hpp"
//Initializer functions

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet) {
    this->m_sprite.setTexture(texture_sheet);
    this->createHitboxComponent(this->m_sprite, 0.f, 0.f, 64.f, 64.f);
    this->createMovementComponent(7.f, 3.f, 15.f);
    this->createAttributesComponent();
    this->e_setPosition(x, y);
}

Player::~Player() {}

void Player::e_update(const float& delta_time) {
    this->e_movement->update(delta_time);
    this->e_hitbox->update();
    this->e_attributes->update(delta_time);
}

void Player::e_render(sf::RenderTarget& target, const bool show_hitbox) {
    target.draw(this->m_sprite);

    if (show_hitbox)
        this->e_hitbox->render(target);
}