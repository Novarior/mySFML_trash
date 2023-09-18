#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"
#include "Coins.hpp"

class Item {
private:
public:
    static unsigned int count_items;

    Item()
    {
        this->m_Usable = false;
        this->m_stacable = false;
        this->m_pickable = false;
        this->m_amount = 0;
        this->m_maxAmount = 0;
        this->m_price = { 0, 0, 1 };
        this->m_name = this->m_name = "Default";
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
    inline void addAmount(int _amount) { this->m_amount += _amount; }
    inline void removeAmount(int _amount) { this->m_amount -= _amount; }

    // inline functions get
    inline const unsigned int getID() const { return this->item_ID; }
    inline const std::string getName() const { return this->m_name; }
    inline const int getAmount() const { return this->m_amount; }
    inline const int getMaxAmount() const { return this->m_maxAmount; }
    inline const bool isPickable() const { return this->m_pickable; }
    inline const bool isStackable() const { return this->m_stacable; }
    inline const bool isUsable() const { return this->m_Usable; }
    inline Coins& getPrice() { return this->m_price; }

    // inline functions set
    inline void setID(const unsigned int ID) { this->item_ID = ID; }
    inline void setName(const std::string name) { this->m_name = name; }
    inline void setAmount(const int _amount) { this->m_amount = _amount; }
    inline void setPickable(const bool pickable) { this->m_pickable = pickable; }
    inline void setStackable(const bool stacable) { this->m_stacable = stacable; }

    virtual void useItem() = 0;
    virtual void update(const float& delta_time, sf::Vector2i mouse_pos) = 0;
    virtual void render(sf::RenderTarget& target) { target.draw(this->m_shape); }

    inline void setPosistion(sf::Vector2f position) { this->m_shape.setPosition(position); }
    inline void setSize(sf::Vector2f size) { this->m_shape.setSize(size); }

protected:
    bool m_Usable;
    unsigned int item_ID;
    bool m_stacable;
    unsigned m_maxAmount;
    bool m_pickable;
    int m_amount;
    std::string m_name;
    sf::Texture m_texture;
    sf::RectangleShape m_shape;
    Coins m_price;
};
#endif