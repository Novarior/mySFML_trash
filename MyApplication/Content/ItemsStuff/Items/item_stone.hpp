#ifndef item_stone_hpp
#define item_stone_hpp
#include "../Item.hpp"


class Stone : public Item
{
    public:
    Stone(sf::Vector2f pos, sf::Vector2f size, std::string texture_path, bool stacable, int quantity, int price, bool picked_up)
    {
        this->name = "Stone";
        this->m_shape.setPosition(pos);
        this->m_shape.setSize(size);
        this->m_texture.loadFromFile(texture_path);
        this->m_shape.setTexture(&this->m_texture);
        this->stacable = stacable;
        this->quantity = quantity;
        this->price = price;
        this->pickable = picked_up;
    }
    virtual ~Stone() {}

    void update(sf::Vector2i mouse_pos) {}
    void render(sf::RenderTarget& target)
    {
        target.draw(this->m_shape);
    }
};
#endif /* item_stone_hpp */