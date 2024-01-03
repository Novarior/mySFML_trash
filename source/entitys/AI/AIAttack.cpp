#include "AIAttack.hpp"

AIAttack::AIAttack(Entity& self, Entity& entity)
    : AIOption(self, entity)
{
}

AIAttack::~AIAttack() { }

void AIAttack::update(const float& delta_time)
{
    updateCooldown(delta_time);

    _ai_rad.setPosition(_ai_self.e_getPosition());
    if (getCooldown())
        if (_ai_rad.getGlobalBounds().intersects(_ai_entity.getGlobalBounds()))
            _ai_entity.e_takeDamage(_ai_self.getAttributes()->getAttributes().damage);
}