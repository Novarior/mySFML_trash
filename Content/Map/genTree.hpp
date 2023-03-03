#ifndef CPP_MAP_TREE_HPP
#define CPP_MAP_TREE_HPP
#include "../../header.h"

class GenTree
{
private:
    sf::RectangleShape m_shapeSquare;
    sf::CircleShape m_shapeCircle;

    std::vector<sf::RectangleShape> m_arrayshape;


    const unsigned stepsize = 5;
    const unsigned brushsize = 10;

    std::vector<sf::Vector2f> recordstepBuffer;
    std::string commands;

    void clear();
public:

    GenTree();
    /**
     * @brief Destroy the Gen Tree object
     * 
     */
    virtual ~GenTree();

    void generateTree();
    void update();
    /**
     * @brief 
     * 
     * @param target render targer for render
     */
    void render(sf::RenderTarget* target);
    
};
#endif 