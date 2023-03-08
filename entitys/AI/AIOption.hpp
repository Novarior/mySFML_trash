#pragma once
#include "../Entity.hpp"
enum FollowTargetEnum { NONE, T_PLAYER, T_ENTITY, T_PIONT };

class AIOption
{
    protected:
    Entity& entity;
    Entity& self;

    public:
    AIOption(Entity& self, Entity& entity)
        : self(self), entity(entity)
    {

    }

    virtual void update(const float& delta_time) = 0;
};