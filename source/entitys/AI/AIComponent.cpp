#include "AIComponent.hpp"

AIComponent::AIComponent(Entity& self, Entity& entity)
    : self(self)
    , entity(entity)
{
    this->follow = nullptr;
    this->attack = nullptr;
}

AIComponent::~AIComponent()
{
    delete this->follow;
    delete this->attack;
}

void AIComponent::update(const float& delta_time)
{
    this->follow->update(delta_time);
    this->attack->update(delta_time);
}

void AIComponent::create_follow(AIFollow* follow)
{
    this->follow = follow;
}

void AIComponent::create_attack(AIAttack* attack)
{
    this->attack = attack;
}