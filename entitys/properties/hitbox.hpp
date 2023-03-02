#ifndef CPP_HITBOX_HPP
#define CPP_HITBOX_HPP
#include "../../header.h"

class HitboxCounter
{
    private:
    sf::RectangleShape& sprite;
    sf::RectangleShape hitbox;
    sf::Vector2f offset;

    public:
    HitboxCounter(sf::RectangleShape& sprite, sf::Vector2f size, sf::Vector2f offset);
    virtual ~HitboxCounter();

    void collision();
    bool getCollison();
    bool intersects(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget* target);

};
#endif