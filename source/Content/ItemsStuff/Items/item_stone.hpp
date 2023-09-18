#ifndef item_stone_hpp
#define item_stone_hpp
#include "../Item.hpp"

namespace Items {
class Stone : public Item {
public:
    Stone(unsigned int gridSizeI)
    {
        this->m_name = "Stone";
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
        this->m_Usable = false;

        if (this->m_texture.loadFromFile(myConst::item_img_stone2))
            this->m_shape.setTexture(&this->m_texture);
        else
            std::cout << "ERROR::ITEM::COULD_NOT_LOAD_TEXTURE" << std::endl;

        this->m_stacable = true;
        this->m_amount = 1;
        this->m_price = { 0, 0, 1 };
        this->m_pickable = true;
        this->m_maxAmount = 8;
    }
    virtual ~Stone() { }

    void useItem() override
    {
        // print to console that you used this item

        std::cout << this->m_name << " is not usable" << std::endl;
    }

    void update(const float& delta_time, sf::Vector2i mouse_pos) override { }
};
};
#endif /* item_stone_hpp */