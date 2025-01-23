#ifndef ITEMSTUFF_ITEM_H
#define ITEMSTUFF_ITEM_H
#include "../../core/header.h"
#include "Coins.hpp"
#include "itemtextures.hpp"

class Item {
public:
    Item(unsigned int id = 0, const std::string& name = "Default", bool pickable = false, bool stackable = false,
        bool usable = false, int amount = 0, unsigned maxAmount = 0, const Coins& price = { 0, 0, 1 })
        : item_ID(id)
        , m_name(name)
        , m_pickable(pickable)
        , m_stackable(stackable)
        , m_usable(usable)
        , m_amount(amount)
        , m_maxAmount(maxAmount)
        , m_price(price)
    {
    }

    virtual ~Item() noexcept = default;

    // Modifiers
    void addAmount(int _amount) noexcept { m_amount += _amount; }
    void removeAmount(int _amount) noexcept { m_amount -= _amount; }

    // Getters
    unsigned int getID() const noexcept { return item_ID; }
    const std::string& getName() const noexcept { return m_name; }
    int getAmount() const noexcept { return m_amount; }
    unsigned getMaxAmount() const noexcept { return m_maxAmount; }
    bool isPickable() const noexcept { return m_pickable; }
    bool isStackable() const noexcept { return m_stackable; }
    bool isUsable() const noexcept { return m_usable; }
    Coins& getPrice() noexcept { return m_price; }

    // Setters
    void setID(unsigned int ID) noexcept { item_ID = ID; }
    void setName(const std::string& name) noexcept { m_name = name; }
    void setAmount(int amount) noexcept { m_amount = amount; }
    void setPickable(bool pickable) noexcept { m_pickable = pickable; }
    void setStackable(bool stackable) noexcept { m_stackable = stackable; }

    virtual void useItem() = 0;
    virtual void update(float delta_time, sf::Vector2i mouse_pos) { }
    virtual void render(sf::RenderTarget& target) noexcept { target.draw(m_shape); }

    void setPosition(sf::Vector2f position) noexcept { m_shape.setPosition(position); }
    void setSize(sf::Vector2f size) noexcept { m_shape.setSize(size); }

protected:
    unsigned int item_ID;
    std::string m_name;
    bool m_pickable;
    bool m_stackable;
    bool m_usable;
    int m_amount;
    unsigned m_maxAmount;
    Coins m_price;

    sf::RectangleShape m_shape;
};

#endif