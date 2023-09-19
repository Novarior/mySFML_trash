#ifndef AI_OPTIONS_HPP
#define AI_OPTIONS_HPP
#include "../entity.hpp"

enum FollowTargetEnum { NONE,
    T_PLAYER,
    T_ENTITY,
    T_POINT };

class AIOption {
protected:
    Entity& entity;
    Entity& self;
    sf::CircleShape rad;

public:
    AIOption(Entity& self, Entity& entity)
        : self(self)
        , entity(entity)
    {
        rad = sf::CircleShape(25);
        rad.setOrigin(25, 25);
    }

    virtual void update(const float& delta_time) = 0;
};
#endif