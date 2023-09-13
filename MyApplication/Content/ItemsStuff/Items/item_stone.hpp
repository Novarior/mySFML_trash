#ifndef item_stone_hpp
#define item_stone_hpp
#include "../Item.hpp"

class Stone : public Item {
public:
    Stone(unsigned int gridSizeI, std::string texture_path, bool stacable, int quantity, int price, bool picked_up)
    {
        this->m_name = "Stone";
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
        this->m_Usable = false;

        if (this->m_texture.loadFromFile(texture_path))
            this->m_shape.setTexture(&this->m_texture);

        this->m_stacable = stacable;
        this->m_quantity = quantity;
        this->m_price = price;
        this->m_pickable = picked_up;
    }
    virtual ~Stone() { }

    void useItem() override
    {
        // print to console that you used this item

        std::cout << this->m_name << " is not usable" << std::endl;
    }

    void update(const float& delta_time, sf::Vector2i mouse_pos) override { }
    void render(sf::RenderTarget& target) override
    {
        target.draw(this->m_shape);
    }
};
#endif /* item_stone_hpp */