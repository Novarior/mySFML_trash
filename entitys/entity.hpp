#ifndef CPP_ENTITYCLASS_HPP
#define CPP_ENTITYCLASS_HPP
#include "../header.h"
#include "properties/movement.hpp"
#include "properties/hitbox.hpp"

enum movementState { IDLE = 0, WALK, JUMP, DUCK };

class Entity
{
    private:
    void initHitboxAndSprite();
    void initMovement();
    void initSomeinit();
    void initHitbox();

    protected:
    sf::RectangleShape sprite;
    Movement* e_movement;
    HitboxCounter* e_hitbox;

    bool isCollision;
    bool isAlive;
    bool isDuck;
    bool isFall;
    bool isJump;

    movementState mState;




    public:
    Entity();
    virtual ~Entity();

    sf::Vector2f e_getVelocity();
    virtual void e_move(sf::Vector2f directionalmove, const float& deltaTime);
    virtual void e_updateAnimation(std::string keyNameAnimation, const float& deltaTime);
    virtual void e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision);
    virtual void e_updateCollison(TileMap* map, const float& deltatime);
    virtual void e_jump(const float& deltatime);
    virtual void e_update(const float& deltatime = NULL) = 0;
    virtual void e_render(sf::RenderTarget* target = NULL) = 0;
    HitboxCounter* getHitbox();
    Movement* getMovement();

    virtual sf::Vector2f e_getPosition();
    virtual sf::Vector2i e_getGridPosition(unsigned int grisSize);


};

#endif CPP_ENTITYCLASS_HPP