#ifndef CPP_ENTITYCLASS_HPP
#define CPP_ENTITYCLASS_HPP

#include "../header.h"
#include "properties/attributes.hpp"
#include "properties/hitbox.hpp"
#include "properties/movement.hpp"

enum movementState { IDLE = 0,
    WALK,
    JUMP,
    DUCK };

class Entity {
private:
protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    MovementComponent* e_movement;
    HitboxComponent* e_hitbox;
    Attributes* e_attributes;

    bool isCollision;
    bool isAlive;
    float gridSizeF;
    unsigned int ID_entity;

    movementState mState;

    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity);
    void createAttributesComponent();

public:
    // count of entitys
    static unsigned int count_entitys;

    Entity();
    virtual ~Entity();

    // inline getters functions for components
    inline HitboxComponent* getHitbox() { return this->e_hitbox; }
    inline MovementComponent* getMovement() { return this->e_movement; }
    inline Attributes* getAttributes() { return this->e_attributes; }

    inline const unsigned int& e_getID() const { return this->ID_entity; }
    inline const unsigned int& e_getCountEntitys() const { return this->count_entitys; }

    // inline getters functions
    inline virtual const bool& e_getAlive() const { return this->isAlive; }
    inline virtual const bool& e_getCollision() const { return this->isCollision; }
    inline virtual const float& getGridSizeFloat() const { return this->gridSizeF; }
    inline virtual const sf::Vector2f& e_getVelocity() { return this->e_movement->getVelocity(); }
    inline virtual const sf::Vector2f& e_getPosition() { return this->m_sprite.getPosition(); }

    // inline setters functions
    inline virtual void e_setTexture(sf::Texture& texture) { this->m_sprite.setTexture(texture); }
    inline virtual void e_setPosition(const sf::Vector2f pos) { this->m_sprite.setPosition(pos); }
    inline virtual void e_setPosition(const float pos_x, const float pos_y) { this->m_sprite.setPosition(sf::Vector2f(pos_x, pos_y)); }

    // inline update functions
    inline virtual void e_updateMovement(const float& delta_time) { this->e_movement->update(delta_time); }
    inline virtual void e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision) { this->e_hitbox->update(); }

    virtual void e_updateAnimation(std::string keyNameAnimation, const float& delta_time) { }
    // getters functions
    // modifiers functions
    virtual void e_move(const float& dir_x, const float& dir_y, const float& delta_time);

    virtual const sf::FloatRect getGlobalBounds();
    virtual const sf::FloatRect getNextPositionBounds(const float& delta_time);
    virtual const sf::Vector2f e_getGridPositionFloat(const float& gridsize);
    virtual const sf::Vector2i e_getGridPositionInt(const unsigned int& grisSize);

    // render functions
    virtual void e_update(const float& dt) = 0;
    virtual void e_render(sf::RenderTarget& target, const bool show_hitbox = false) = 0;
    virtual void e_render(sf::RenderTarget& target, sf::Shader& shader, const bool show_hitbox = false) = 0;
};
#endif