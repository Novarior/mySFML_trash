#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"

class Item {
private:
public:
    static unsigned int count_items;

    Item()
    {
        this->m_Usable = false;
        this->m_stacable = false;
        this->m_pickable = false;
        this->m_quantity = 0;
        this->m_price = 0;
        this->m_name = "Default";
        this->item_ID = count_items++;
    }

    virtual ~Item()
    {
        std::cout << "Item destructor" << std::endl;
        this->count_items--;
    }

    inline void dropItem() { this->~Item(); }

    // modificators

    const bool pickedUp() const { return this->m_pickable; }

    // set from
    inline void setItemPositionOnInventory(sf::Vector2f position) { this->m_shape.setPosition(position); }

    // modifiers functions
    inline void addQuantity(int quantity) { this->m_quantity += quantity; }
    inline void removeQuantity(int quantity) { this->m_quantity -= quantity; }

    // inline functions get
    inline const unsigned int getID() const { return this->item_ID; }
    inline const std::string getName() const { return this->m_name; }
    inline const bool getPrice() const { return this->m_price; }
    inline const int getQuantity() const { return this->m_quantity; }
    inline const bool isPickable() const { return this->m_pickable; }
    inline const bool isStackable() const { return this->m_stacable; }
    inline const bool isUsable() const { return this->m_Usable; }

    // inline functions set
    inline void setID(const unsigned int ID) { this->item_ID = ID; }
    inline void setName(const std::string name) { this->m_name = name; }
    inline void setPrice(const int price) { this->m_price = price; }
    inline void setQuantity(const int quantity) { this->m_quantity = quantity; }
    inline void setPickable(const bool pickable) { this->m_pickable = pickable; }
    inline void setStackable(const bool stacable) { this->m_stacable = stacable; }

    virtual void useItem() = 0;

    virtual void update(const float& delta_time, sf::Vector2i mouse_pos) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

protected:
    bool m_Usable;
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