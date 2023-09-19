#include "AIAttack.hpp"

AIAttack::AIAttack(Entity& self, Entity& entity)
    : AIOption(self, entity)
{
    // ctor
}

AIAttack::~AIAttack()
{
    // dtor
}

void AIAttack::update(const float& delta_time)
{
    this->rad.setPosition(this->self.e_getPosition());

    if (this->rad.getGlobalBounds().intersects(this->entity.getGlobalBounds())) {
        this->entity.e_takeDamage(this->self.getAttributes()->getAttributes().damage);
    }
}