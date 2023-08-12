#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"

class Item {
private:
public:
    static unsigned int count_items;

    Item() { this->count_items++; }
    virtual ~Item() { }

    inline void dropItem() { this->~Item(); }

    // modificators

    const bool pickedUp() const { return this->m_pickable; }

    // set from
    inline void setItemPositionOnInventory(sf::Vector2f position) { this->m_shape.setPosition(position); }

    // modifiers functions
    inline void addQuantity(int quantity) { this->m_quantity += quantity; }
    inline void removeQuantity(int quantity) { this->m_quantity -= quantity; }

    // inline functions get
    inline const bool getPrice() const { return this->m_price; }
    inline const std::string getName() const { return this->m_name; }
    inline const bool getQuantity() const { return this->m_quantity; }
    inline const bool getStackable() const { return this->m_stacable; }
    inline const unsigned int getID() const { return this->item_ID; }

    // inline functions set
    inline void setPrice(int price) { this->m_price = price; }
    inline void setName(std::string name) { this->m_name = name; }
    inline void setQuantity(int quantity) { this->m_quantity = quantity; }
    inline void setStackable(bool stacable) { this->m_stacable = stacable; }
    inline void setPickable(bool pickable) { this->m_pickable = pickable; }
    inline void setID(unsigned int ID) { this->item_ID = ID; }

    virtual void update(const float& delta_time, sf::Vector2i mouse_pos) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

protected:
    unsigned int item_ID;
    bool m_stacable;
    bool m_pickable;
    int m_quantity;
    std::string m_name;
    sf::Texture m_texture;
    sf::RectangleShape m_shape;
    int m_price;
};
#endif