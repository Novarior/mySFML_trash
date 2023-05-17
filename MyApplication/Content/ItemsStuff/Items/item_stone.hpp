#ifndef item_stone_hpp
#define item_stone_hpp
#include "../Item.hpp"


class Stone : public Item
{
    public:
    Stone(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, bool stacable, int quantity, int price, bool picked_up) :
        Item(pos, size, texture, stacable, quantity, price, picked_up)
    {
        this->m_shape.setPosition(pos);
        this->m_shape.setSize(size);
        this->m_shape.setTexture(&texture);
    }
    virtual ~Stone() {}

    void update(sf::Vector2i mouse_pos) {}
    void render(sf::RenderTarget& target)
    {
        target.draw(this->m_shape);
    }
};
#endif /* item_stone_hpp */