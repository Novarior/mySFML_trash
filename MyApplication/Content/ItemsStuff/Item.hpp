#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"

class Item
{
    public:
    Item() {}
    virtual ~Item() {}

    void dropItem() { this->~Item(); }

    //functions get
    const bool getPrice() const { return this->price; }
    const std::string getName() const { return this->name; }
    const bool getQuantity() const { return this->quantity; }
    const bool getStackable() const { return this->stacable; }
    const unsigned int getUnicID() const { return this->item_ID; }

    //functions set
    void setPrice(int price) { this->price = price; }
    void setName(std::string name) { this->name = name; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setStackable(bool stacable) { this->stacable = stacable; }


    //modificators
    void addQuantity(int quantity) { this->quantity += quantity; }

    const bool pickedUp() const { return this->pickable; }

    void update(sf::Vector2i mouse_pos) { }
    virtual void render(sf::RenderTarget& target) = 0;

    protected:
    unsigned int item_ID;
    bool stacable;
    bool pickable;
    int quantity;
    std::string name;
    sf::Texture m_texture;
    sf::RectangleShape m_shape;
    int price;
};
#endif