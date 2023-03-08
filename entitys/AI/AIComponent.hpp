#pragma once
#include "../Entity.hpp"
#include "AIFollow.hpp"

class AIComponent
{
    private:
    Entity& entity;
    Entity& self;

    public:
    AIComponent(Entity& self, Entity& entity);
    ~AIComponent();

    void update(const float& delta_time);
};