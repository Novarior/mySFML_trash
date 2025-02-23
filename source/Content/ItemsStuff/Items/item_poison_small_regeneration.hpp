#ifndef item_poison_small_regeneration_hpp
#define item_poison_small_regeneration_hpp
#include "../Item.hpp"

namespace Items {
class PoisonSmallRegeneration : public Item {
private:
public:
    PoisonSmallRegeneration(unsigned int gridSizeI)
        : Item(2, "Poison of Regeneration", true, true, false, 1, 2, {0, 1, 25})
    {
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
        this->m_shape.setTexture(&TextureManager::getTexture("items_potion_small_regeneration"));
    }
    virtual ~PoisonSmallRegeneration() { }

    void useItem() override
    {
        // print to console that you used this item
        std::cout << "You used " << this->m_name << std::endl;
        // add regeneration to player
        // remove item from inventory
        // if quantity == 0 remove item from inventory

        if (this->m_amount <= 0)
            this->~PoisonSmallRegeneration();
        else if (this->m_amount > 0)
            this->m_amount--;
        else
            std::cout << "Error: Quantity of item is less than 0" << std::endl;
    }

    void update(const float& delta_time, sf::Vector2i mouse_pos)
    {
    }
};
}
#endif /* item_poison_small_regeneration_hpp */