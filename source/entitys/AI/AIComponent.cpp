#include "AIComponent.hpp"

AIComponent::AIComponent(Entity& self, Entity& entity)
    : _self(self)
    , _entity(entity)
{
    _follow = nullptr;
    _attack = nullptr;
}

AIComponent::~AIComponent() { }

void AIComponent::update(const float& delta_time)
{
    _follow->update(delta_time);
    _attack->update(delta_time);
}

void AIComponent::create_follow(int stopDistance)
{
    _follow = std::make_unique<AIFollow>(_self, _entity, stopDistance);
}
void AIComponent::create_attack()
{
    _attack = std::make_unique<AIAttack>(_self, _entity);
}