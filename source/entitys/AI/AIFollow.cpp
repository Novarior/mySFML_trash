#include "AIFollow.hpp"

AIFollow::AIFollow(Entity& self, Entity& entity, int stopDistance)
    : AIOption(self, entity)
{
}

AIFollow::~AIFollow()
{
}

void AIFollow::update(const float& delta_time)
{
    sf::Vector2f moveVec;
    moveVec.x = _ai_entity.e_getPosition().x - _ai_self.e_getPosition().x;
    moveVec.y = _ai_entity.e_getPosition().y - _ai_self.e_getPosition().y;

    float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

    moveVec /= vecLength;

    if ((_ai_self.e_getPosition().x != _ai_entity.e_getPosition().x) && std::abs(vecLength) < 500.f)
        _ai_self.e_move(moveVec.x, moveVec.y, delta_time);
}

bool AIFollow::isCloseEnough()
{
    float distance = sqrt(pow(_ai_entity.e_getPosition().x - _ai_self.e_getPosition().x, 2) + pow(_ai_entity.e_getPosition().y - _ai_self.e_getPosition().y, 2));
    return distance <= _ai_stopDistance;
}