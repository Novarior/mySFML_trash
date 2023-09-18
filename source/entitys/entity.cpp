#include "entity.hpp"

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
    this->e_hitbox = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity)
{
    this->e_movement = new MovementComponent(this->m_sprite, acceleration,
        deceleration, maxVelocity);
}

void Entity::createAttributesComponent(Atri* attributes)
{
    if (attributes != nullptr)
        this->e_attributes = new Attributes(attributes);
    else
        this->e_attributes = new Attributes();
}

Entity::Entity()
{
    this->e_movement = NULL;
    this->e_hitbox = NULL;
    this->e_attributes = NULL;
    this->ID_entity = this->count_entitys;
    this->count_entitys++;
}

Entity::~Entity()
{
    delete this->e_hitbox;
    delete this->e_movement;
    delete this->e_attributes;
    this->count_entitys--;
}

void Entity::e_move(const float& dir_x, const float& dir_y, const float& delta_time)
{
    this->e_movement->move(dir_x, dir_y, delta_time);
}

const sf::FloatRect Entity::getGlobalBounds()
{
    if (this->e_hitbox != nullptr)
        return this->e_hitbox->getGlobalBounds();

    return this->m_sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& delta_time)
{
    if (this->e_hitbox != nullptr && this->e_movement != nullptr)
        return this->e_hitbox->getNextPosition(this->e_movement->getVelocity() * delta_time);

    return sf::FloatRect(0, 0, 1, 1);
}

const sf::Vector2i Entity::e_getGridPositionInt(const unsigned int& grisSize)
{
    if (this->e_hitbox != nullptr)
        return sf::Vector2i(
            static_cast<int>(this->e_hitbox->getPosition().x) / grisSize,
            static_cast<int>(this->e_hitbox->getPosition().y) / grisSize);

    return sf::Vector2i(
        static_cast<int>(this->m_sprite.getPosition().x) / grisSize,
        static_cast<int>(this->m_sprite.getPosition().y) / grisSize);
}

const sf::Vector2f Entity::e_getCenterPosition()
{
    sf::Vector2f cp(0.f, 0.f);
    cp = sf::Vector2f(
        this->m_sprite.getPosition().x + this->m_sprite.getGlobalBounds().width / 2.f,
        this->m_sprite.getPosition().y + this->m_sprite.getGlobalBounds().height / 2.f);
    return cp;
}