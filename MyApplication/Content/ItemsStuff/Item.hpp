#ifndef ITEM_H
#define ITEM_H
#include "../../header.h"
#include "Coins.hpp"
class Item
{
private:
    sf::RectangleShape m_shape;
    bool stacable;
    int quantity;
public:
    int price;
    Item(){};
    virtual ~Item(){};
};
#endif