#ifndef CPP_MAP_TREE_HPP
#define CPP_MAP_TREE_HPP
#include "../../header.h"

class GenTree
{
private:
    sf::RectangleShape m_shapeSquare;
    sf::CircleShape m_shapeCircle;

    std::vector<sf::RectangleShape> m_arrayshape;


    const unsigned stepsize;
    const unsigned brushsize;
    std::vector<sf::Vector2f> recordstepBuffer;

    std::string commands;
public:
    GenTree();
    virtual ~GenTree();

    void update();
    void render(sf::RenderTarget* target);
    
};
#endif 