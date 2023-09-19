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
    float gridSizeF;
    unsigned int ID_entity;

    movementState mState;

    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity);
    void createAttributesComponent(Atri* attributes = nullptr);

public:
    // count of entitys
    static unsigned int count_entitys;

    Entity();
    virtual ~Entity();

    // inline getters functions for components

    /// @brief Get the Hitbox Component object
    /// @return HitboxComponent *ptr
    inline HitboxComponent* getHitbox() { return this->e_hitbox; }
    /// @brief  Get the Movement Component object
    /// @return MovementComponent *ptr
    inline MovementComponent* getMovement() { return this->e_movement; }
    /// @brief Get the Attributes Component object
    /// @return Attributes *ptr
    inline Attributes* getAttributes() { return this->e_attributes; }
    /// @brief get the ID of entity
    /// @return unsigned int
    inline const unsigned int& e_getID() const { return this->ID_entity; }
    /// @brief  get the count of entitys
    /// @return unsigned int
    inline const unsigned int& e_getCountEntitys() const { return this->count_entitys; }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // inline getters functions

    /// @brief  get the state of entity
    /// @return bool<-attribute<-isAlive
    inline const bool e_isAlive() const { return this->e_attributes->getAttributes().isAlive; }
    /// @brief get the grid size of entity
    /// @return float &
    inline virtual const float getGridSizeFloat() const { return this->gridSizeF; }
    /// @brief  get velocity of entity
    /// @return sf::Vector2f &
    inline virtual const sf::Vector2f e_getVelocity() { return this->e_movement->getVelocity(); }
    /// @brief  get the position of entity
    /// @return sf::Vector2f &
    inline virtual const sf::Vector2f e_getPosition() { return this->m_sprite.getPosition(); }
    /// @brief  get the center position of entity
    /// @return sf::Vector2f
    virtual const sf::Vector2f e_getCenterPosition();
    /// @brief get the grid position of entity
    /// @param gridsize float
    /// @return sf::Vector2i &
    virtual const sf::Vector2f e_getGridPositionFloat(const float& gridsize)
    {
        return sf::Vector2f(this->m_sprite.getPosition().x / gridsize, this->m_sprite.getPosition().y / gridsize);
    }
    /// @brief  get the global bounds of entity
    /// @return sf::FloatRect
    virtual const sf::FloatRect getGlobalBounds();
    /// @brief              get the next position of entity
    /// @param delta_time   const float &
    /// @return             const sf::FloatRect &
    virtual const sf::FloatRect getNextPositionBounds(const float& delta_time);
    /// @brief  get the grid position of entity
    /// @param grisSize float
    /// @return sf::Vector2i &
    virtual const sf::Vector2i e_getGridPositionInt(const unsigned int& grisSize);
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief  set the flag of collision
    /// @param isCollision bool
    inline virtual void e_setCollision(const bool isCollision) { this->isCollision = isCollision; }
    /// @brief load texture from file
    /// @param file_path    std::string
    inline virtual void e_loadTexture(const std::string file_path) { this->m_texture.loadFromFile(file_path); }
    /// @brief set texture from sf::Texture
    /// @param texture  sf::Texture *
    inline virtual void e_setTexture(sf::Texture* texture) { this->m_sprite.setTexture(*texture); }
    /// @brief set texture from sf::Texture
    /// @param texture  sf::Texture &
    inline virtual void e_setTexture(sf::Texture& texture) { this->m_sprite.setTexture(texture); }
    /// @brief set position of entity
    /// @param pos  sf::Vector2f
    inline virtual void e_setPosition(const sf::Vector2f pos) { this->m_sprite.setPosition(pos); }
    /// @brief set position of entity
    /// @param floatX float
    /// @param floatY float
    inline virtual void e_setPosition(const float pos_x, const float pos_y) { this->m_sprite.setPosition(sf::Vector2f(pos_x, pos_y)); }
    /// @brief set ID of entity
    /// @param ID   unsigned int &
    inline virtual void e_setID(const unsigned int& ID) { this->ID_entity = ID; }

    // inline update functions
    inline virtual void e_updateMovement(const float& delta_time) { this->e_movement->update(delta_time); }
    inline virtual void e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision) { this->e_hitbox->update(); }

    virtual void e_updateAnimation(std::string keyNameAnimation, const float& delta_time) { }

    /// @brief  move function of entity (pure virtual function)
    /// @param dir_x    const float &
    /// @param dir_y    const float &
    /// @param delta_time   const float &
    virtual void e_move(const float& dir_x, const float& dir_y, const float& delta_time);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // action functions
    /// @brief  attack function of entity (pure virtual function)
    /// @param _entity  Entity *
    /// @param delta_time   const float &
    virtual void e_attack(Entity* target, const float& delta_time) { }
    /// @brief  take damage function of entity (pure virtual function)
    /// @param damage   const int &
    inline virtual void e_takeDamage(const int& damage) { this->e_attributes->takeDamage(damage); }
    /// @brief  die function of entity (pure virtual function)
    void e_die();
    /// @brief interact function of entity (pure virtual function)
    void e_interact();
    /// @brief  interact function of entity (pure virtual function)
    /// @param _entity  Entity *
    void e_interact(Entity& _entity);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief  update function of entity (pure virtual function)
    /// @param dt   const float &
    virtual void e_update(const float& dt) = 0;
    /// @brief  render function of entity (pure virtual function)
    /// @param target   sf::RenderTarget &
    virtual void e_render(sf::RenderTarget& target, const bool show_hitbox = false) = 0;
};
#endif