#include "Item.hpp"

Item::Item(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, bool stacable, int quantity, int price, bool picked_up) :
    stacable(stacable), quantity(quantity), price(price), pickable(picked_up)
{
    this->name = "Default";
    this->m_shape.setPosition(pos);
    this->m_shape.setSize(size);
    this->m_shape.setTexture(&texture);
}

Item::~Item()
{
}

std::string Item::getInfo() {
    std::stringstream ss;
    ss << "Name: " << this->name << "\n"
        << "Stacable: " << this->stacable << "\n"
        << "Quantity: " << this->quantity << "\n"
        << "Price: " << this->price << "\n";
    return ss.str();
}