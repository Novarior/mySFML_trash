#ifndef CPP_MOVEMENT_HPP
#define CPP_MOVEMENT_HPP
#include "../../header.h"
#include "../../Content/Map/TileMap.hpp"

class BrickBlock;
class TileMap;

enum movestate {NONe=-1,Idle, Jump, Fall};

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
    

    public:
    Movement(sf::RectangleShape& sprite, float accel, float decel, float maxVel);
    ~Movement();

    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void jump(const float& dealtatime);

    sf::Vector2f getVelocity();
    void move(sf::Vector2f direction, const float& deltatime);
    void update(const float& deltatime);
    void updateCollison(TileMap* map, const float& deltatime);
};
#endif