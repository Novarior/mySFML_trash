#ifndef CPP_CONTENT_ROTATIONCIRCLE_HPP
#define CPP_CONTENT_ROTATIONCIRCLE_HPP

#include "../header.h"
#include "../math/mymath.hpp"

struct BlocksGenData
{
    sf::Vector2u windowSize;
    sf::Vector2f offset;
    sf::Vector2f pos ;
    float amplifire;
    unsigned countPhantomBlocks;
    float frequency;
};

class RotarionCircle
{
private:
    sf::CircleShape shape;
    std::list<sf::CircleShape> phantoms;
    float i;
    BlocksGenData bgd;
    bool fastRm;


public:
    RotarionCircle(BlocksGenData gendata);
    virtual ~RotarionCircle();

    void update(const float& deltatime);
    void setShape(sf::CircleShape shape);
    void render(sf::RenderTarget* target);
};
#endif 