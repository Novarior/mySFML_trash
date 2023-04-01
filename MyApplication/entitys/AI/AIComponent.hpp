#ifndef AIComponent_H
#define AIComponent_H
#include "../entity.hpp"
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
#endif