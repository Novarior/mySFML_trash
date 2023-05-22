#ifndef CPP_ENTITYCLASS_HPP
#define CPP_ENTITYCLASS_HPP

#include "../header.h"
#include "properties/movement.hpp"
#include "properties/hitbox.hpp"
#include "properties/attributes.hpp"

enum movementState { IDLE = 0, WALK, JUMP, DUCK };

class Entity
{
    private:
    protected:
    sf::Sprite m_sprite;
    MovementComponent* e_movement;
    HitboxComponent* e_hitbox;
    Attributes* e_attributes;

    bool isCollision;
    bool isAlive;
    float gridSizeF;

    movementState mState;

    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity);
    void createAttributesComponent();

    public:
    Entity();
    virtual ~Entity();

    HitboxComponent* getHitbox();
    MovementComponent* getMovement();
    Attributes* getAttributes();

    virtual void setTexture(sf::Texture& texture);

    virtual void e_move(const float& dir_x, const float& dir_y, const float& delta_time);
    virtual void e_updateAnimation(std::string keyNameAnimation, const float& delta_time);
    virtual void e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision);
    virtual void e_updateMovement(const float& delta_time);

    virtual const float& getGridSizeFloat() const;
    virtual const sf::FloatRect getGlobalBounds();
    virtual const sf::FloatRect getNextPositionBounds(const float& delta_time);
    virtual const sf::Vector2f& e_getVelocity();
    virtual const sf::Vector2f& e_getPosition();
    virtual const sf::Vector2f e_getGridPositionFloat(const float& gridsize);
    virtual const sf::Vector2i e_getGridPositionInt(const unsigned int& grisSize);
    virtual void e_setPosition(const sf::Vector2f pos);
    virtual void e_setPosition(const float pos_x, const float pos_y);

    virtual void e_update(const float& dt) = 0;
    virtual void e_render(sf::RenderTarget& target, const bool show_hitbox = false) = 0;
};
#endif 