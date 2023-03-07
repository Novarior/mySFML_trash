#ifndef CPP_MOVEMENT_HPP
#define CPP_MOVEMENT_HPP
#include "../../header.h"
#include "../../Content/Map/TileMap.hpp"

class BrickBlock;
class TileMap;

enum movestate { NONe = -1, Idle, Jump, Fall };

#define MAXSPEEDENTITY = 0x3ff;
class Movement
{
    private:
    sf::Vector2f direction;
    float acceleration;
    float deceleration;
    float maxVelocity;
    sf::Vector2f velocity;
    sf::RectangleShape& sprite;

    unsigned short m_state;

    void updateCollison(const float& deltatime, TileMap* map);

    public:
    Movement(sf::RectangleShape& sprite, float accel, float decel, float maxVel);
    ~Movement();

    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    sf::Vector2f getVelocity();


    void jump(const float& dealtatime);
    void move(sf::Vector2f direction, const float& deltatime);
    void update(const float& deltatime, TileMap* map);
};
#endif