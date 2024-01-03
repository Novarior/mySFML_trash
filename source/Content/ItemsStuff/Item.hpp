#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../header.h"
#include "Coins.hpp"
#include "itemtextures.hpp"

class Item {
private:
public:
    Item()
        : m_Usable(false)
        , m_stacable(false)
        , m_pickable(false)
        , m_amount(0)
        , m_maxAmount(0)
        , m_price({ 0, 0, 1 })
        , m_name("Default")
    {
    }
    inline virtual ~Item() noexcept { }

    inline void dropItem() noexcept { this->~Item(); }

    // modificators
    const bool pickedUp() const noexcept { return this->m_pickable; }

    // set from
    inline void setItemPositionOnInventory(sf::Vector2f position) noexcept { this->m_shape.setPosition(position); }

    // modifiers functions
    inline void addAmount(int _amount) noexcept { this->m_amount += _amount; }
    inline void removeAmount(int _amount) noexcept { this->m_amount -= _amount; }

    // inline functions get
    inline const unsigned int getID() const noexcept { return this->item_ID; }
    inline const std::string getName() const noexcept { return this->m_name; }
    inline const int getAmount() const noexcept { return this->m_amount; }
    inline const int getMaxAmount() const noexcept { return this->m_maxAmount; }
    inline const bool isPickable() const noexcept { return this->m_pickable; }
    inline const bool isStackable() const noexcept { return this->m_stacable; }
    inline const bool isUsable() const noexcept { return this->m_Usable; }
    inline Coins& getPrice() noexcept { return this->m_price; }

    // inline functions set
    inline void setID(const unsigned int ID) noexcept { this->item_ID = ID; }
    inline void setName(const std::string name) noexcept { this->m_name = name; }
    inline void setAmount(const int _amount) noexcept { this->m_amount = _amount; }
    inline void setPickable(const bool pickable) noexcept { this->m_pickable = pickable; }
    inline void setStackable(const bool stacable) noexcept { this->m_stacable = stacable; }

    virtual void useItem() = 0;
    virtual void update(const float& delta_time, sf::Vector2i mouse_pos) = 0;
    virtual void render(sf::RenderTarget& target) noexcept { target.draw(this->m_shape); }

    inline void setPosistion(sf::Vector2f position) noexcept { this->m_shape.setPosition(position); }
    inline void setSize(sf::Vector2f size) noexcept { this->m_shape.setSize(size); }

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