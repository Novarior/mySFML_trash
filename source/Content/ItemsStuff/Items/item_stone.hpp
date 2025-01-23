#ifndef item_stone_hpp
#define item_stone_hpp
#include "../Item.hpp"

namespace Items {
class Stone : public Item {
public:
    Stone(unsigned int gridSizeI)
        : Item(1, "Stone", true, true, false, 1, 8, { 0, 0, 1 })
    {
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
        this->m_shape.setTexture(&TextureManager::getTexture("items_stone"));
        // Остальная инициализация конкретных свойств для Stone
    }
    virtual ~Stone() { }

    void useItem() override
    {
        // print to console that you used this item
        std::cout << this->m_name << " is not usable" << std::endl;
    }

    void update(const float& delta_time, sf::Vector2i mouse_pos)
    {
    }
};
};
#endif /* item_stone_hpp */