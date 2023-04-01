#ifndef CPP_MovementComponent_HPP
#define CPP_MovementComponent_HPP
#include "../../header.h"
enum movestate { NONe = -1, Idle, Jump, Fall, Shift };

#define MAXSPEEDENTITY = 0x3ff;
class MovementComponent
{
    private:
    sf::Sprite& sprite;

    float acceleration;
    float deceleration;
    float maxVelocity;
    sf::Vector2f velocity;
    public:
    MovementComponent(sf::Sprite& sprite, float accel, float decel, float maxVel);
    ~MovementComponent();

    //Accessors
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;

    //Functions
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void move(const float& dir_x, const float& dir_y, const float& delta_time);
    void update(const float& dt);
};
#endif