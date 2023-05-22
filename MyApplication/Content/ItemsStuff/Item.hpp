#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"

class Item
{
    private:
    bool stacable;
    bool pickable;
    int quantity;
    std::string name;
    public:
    sf::RectangleShape m_shape;
    int price;
    Item(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, bool stacable, int quantity, int price, bool picked_up = false);
    virtual ~Item();


    void dropItem() { this->~Item(); }

    void setStacable(bool stacable) { this->stacable = stacable; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(int price) { this->price = price; }

    const bool pickedUp() const { return this->pickable; }
    const bool getPrice() const { return this->price; }
    const bool getStacable() const { return this->stacable; }
    const bool getQuantity() const { return this->quantity; }


    std::string getInfo();

    void update(sf::Vector2i mouse_pos) { }
    virtual void render(sf::RenderTarget& target) = 0;
};
#endif