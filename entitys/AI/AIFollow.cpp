#include "AIFollow.hpp"

AIFollow::AIFollow(Entity& self, Entity& entity)
    : AIOption(self, entity)
{

}

AIFollow::~AIFollow()
{

}

void AIFollow::update(const float& delta_time)
{
    sf::Vector2f moveVec;
    moveVec.x = entity.e_getPosition().x - self.e_getPosition().x;
    moveVec.y = entity.e_getPosition().y - self.e_getPosition().y;

    float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

    moveVec /= vecLength;

    if ((self.e_getPosition().x != entity.e_getPosition().x) && std::abs(vecLength) < 500.f)
        self.e_move(moveVec.x, moveVec.y, delta_time);
}