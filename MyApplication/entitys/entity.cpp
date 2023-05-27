#include "entity.hpp"

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) {
    this->e_hitbox = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}
void Entity::createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity) {
    this->e_movement = new MovementComponent(this->m_sprite, acceleration, deceleration, maxVelocity);
}
void Entity::createAttributesComponent() {
    this->e_attributes = new Attributes();
}

Entity::Entity() {
    this->e_movement = NULL;
    this->e_hitbox = NULL;
    this->e_attributes = NULL;
}

Entity::~Entity() {
    delete this->e_hitbox;
    delete this->e_movement;
    delete this->e_attributes;
}

HitboxComponent* Entity::getHitbox() {
    return this->e_hitbox;
}

MovementComponent* Entity::getMovement() {
    return this->e_movement;
}

Attributes* Entity::getAttributes() {
    return this->e_attributes;
}

void Entity::setTexture(sf::Texture& texture) {
    this->m_sprite.setTexture(texture);
}

void Entity::e_move(const float& dir_x, const float& dir_y, const float& delta_time) {
    this->e_movement->move(dir_x, dir_y, delta_time);
}

const float& Entity::getGridSizeFloat() const {
    return this->gridSizeF;
}

const sf::FloatRect Entity::getGlobalBounds() {
    if (this->e_hitbox)
        return this->e_hitbox->getGlobalBounds();

    return this->m_sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& delta_time) {
    if (this->e_hitbox && this->e_movement)
        return this->e_hitbox->getNextPosition(this->e_movement->getVelocity() * delta_time);

    return sf::FloatRect(1, 1, 1, 1);
}

void Entity::e_setPosition(const sf::Vector2f pos) {
    this->m_sprite.setPosition(pos);
}
void Entity::e_setPosition(const float pos_x, const float pos_y) {
    this->m_sprite.setPosition(sf::Vector2f(pos_x, pos_y));
}

void Entity::e_updateAnimation(std::string keyNameAnimation, const float& delta_time) {}

void Entity::e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision) {
    this->e_hitbox->update();
}

const sf::Vector2f& Entity::e_getPosition() {
    return this->m_sprite.getPosition();
}

const sf::Vector2f Entity::e_getGridPositionFloat(const float& gridsize) {
    return sf::Vector2f(this->m_sprite.getPosition().x / gridsize, this->m_sprite.getPosition().y / gridsize);
}

const sf::Vector2i Entity::e_getGridPositionInt(const unsigned int& grisSize) {
    if (this->e_hitbox)
        return sf::Vector2i(
            static_cast<int>(this->e_hitbox->getPosition().x) / grisSize,
            static_cast<int>(this->e_hitbox->getPosition().y) / grisSize);

    return sf::Vector2i(
        static_cast<int>(this->m_sprite.getPosition().x) / grisSize,
        static_cast<int>(this->m_sprite.getPosition().y) / grisSize);
}
const sf::Vector2f& Entity::e_getVelocity() {
    return this->e_movement->getVelocity();
}
void Entity::e_updateMovement(const float& delta_time) {
    this->e_movement->update(delta_time);
}