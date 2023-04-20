#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"

class Item
{
    private:
    sf::RectangleShape m_shape;
    bool stacable;
    int quantity;
    public:
    int price;
    Item();
    virtual ~Item();
};
#endif