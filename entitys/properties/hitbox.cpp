#include "hitbox.hpp"

HitboxCounter::HitboxCounter(sf::RectangleShape& sprite,sf::Vector2f size,sf::Vector2f offset):
sprite(sprite),offset(offset)
{
    this->hitbox.setPosition(this->hitbox.getPosition().x-offset.x, this->hitbox.getPosition().y-offset.y);
    this->hitbox.setSize(size);
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineColor(sf::Color::Red);
    this->hitbox.setOutlineThickness(-1.f);
}
HitboxCounter::~HitboxCounter()
{

}
 
void HitboxCounter::collision()
{

}
bool HitboxCounter::getCollison()
{

}

bool HitboxCounter::intersects(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxCounter::update()
{
    this->hitbox.setPosition(this->sprite.getPosition().x - this->offset.x, this->sprite.getPosition().y - this->offset.y);
}
void HitboxCounter::render(sf::RenderTarget* target)
{
    target->draw(this->hitbox);
}
