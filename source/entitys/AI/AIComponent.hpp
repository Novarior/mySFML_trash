#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include "../entity.hpp"
#include "AIAttack.hpp"
#include "AIFollow.hpp"

class AIComponent {
private:
    Entity& _entity;
    Entity& _self;

    std::unique_ptr<AIFollow> _follow;
    std::unique_ptr<AIAttack> _attack;

public:
    AIComponent(Entity& self, Entity& entity);
    ~AIComponent();

    void create_follow(int stopDistance);
    void create_attack();

    void update(const float& delta_time);
};
#endif