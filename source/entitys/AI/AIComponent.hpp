#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include "../entity.hpp"
#include "AIAttack.hpp"
#include "AIFollow.hpp"

class AIComponent {
private:
    Entity& entity;
    Entity& self;

    AIFollow* follow;
    AIAttack* attack;

public:
    AIComponent(Entity& self, Entity& entity);
    ~AIComponent();

    void create_follow(AIFollow* follow);
    void create_attack(AIAttack* attack);

    void update(const float& delta_time);
};
#endif