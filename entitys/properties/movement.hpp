#ifndef CPP_MOVEMENT_HPP
#define CPP_MOVEMENT_HPP
#include "../../header.h"
#include "../../Content/Map/TileMap.hpp"
#include "../../entitys/entity.hpp"

class BrickBlock;
class TileMap;
class Entity;

enum movestate { NONe = -1, Idle, Jump, Fall };

#define MAXSPEEDENTITY = 0x3ff;
class Movement
{
    private:
    Entity* m_self;
    sf::Vector2f direction;
    float acceleration;
    float deceleration;
    float maxVelocity;
    sf::Vector2f velocity;
    sf::RectangleShape& sprite;
    const float gridSizeF;
    unsigned short m_state;


    public:
    Movement(sf::RectangleShape& sprite, float accel, float decel, float maxVel, const float grid, Entity* self);
    ~Movement();

    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    sf::Vector2f getVelocity();

    void updateWorldCollison(const float& deltatime, TileMap* map);
    void updateTileCollision(const float& deltatime, TileMap* map);

    void jump(const float& dealtatime);
    void move(sf::Vector2f direction, const float& deltatime);
    void update(const float& deltatime, TileMap* map);
};
#endif