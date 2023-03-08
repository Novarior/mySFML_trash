#pragma once
#include "AIOption.hpp"


class AIFollow:
    public AIOption
{
    private:
    unsigned short followTarget;

    public:
    AIFollow(Entity& self, Entity& entity);
    ~AIFollow();

    void update(const float& delta_time);

};