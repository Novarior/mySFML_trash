#include "AIComponent.hpp"

AIComponent::AIComponent(Entity& self, Entity& entity)
    : self(self), entity(entity)
{
}

AIComponent::~AIComponent()
{
}

void AIComponent::update(const float& delta_time)
{
}