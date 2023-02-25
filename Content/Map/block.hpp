#ifndef CPP_CONTENT_BLOCKS_HPP
#define CPP_CONTENT_BLOCKS_HPP
#include "../../header.h"

class BrickBlock
{
    private:
    sf::RectangleShape shape;
    sf::RectangleShape hitbox;
    bool collision;

    public:
        BrickBlock(sf::Vector2f size, sf::Vector2f position,sf::Color color,bool collosion);
        virtual ~BrickBlock();

        const bool& getCollision();
        sf::RectangleShape& getRectangleShape();
        void render(sf::RenderTarget* target);
};
#endif