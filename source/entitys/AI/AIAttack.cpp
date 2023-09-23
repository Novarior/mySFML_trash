#include "AIAttack.hpp"

AIAttack::AIAttack(Entity& self, Entity& entity)
    : AIOption(self, entity)
{
}

AIAttack::~AIAttack() { }

void AIAttack::update(const float& delta_time)
{
    this->updateCooldown(delta_time);

    this->rad.setPosition(this->self.e_getPosition());
    if (this->getCooldown())
        if (this->rad.getGlobalBounds().intersects(this->entity.getGlobalBounds()))
            this->entity.e_takeDamage(this->self.getAttributes()->getAttributes().damage);
}