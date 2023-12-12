#ifndef item_poison_small_regeneration_hpp
#define item_poison_small_regeneration_hpp
#include "../Item.hpp"

namespace Items {
class PoisonSmallRegeneration : public Item {
private:
public:
    PoisonSmallRegeneration(unsigned int gridSizeI)
    {
        this->m_name = "Poison of Regeneration";
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));

        if (this->m_texture.loadFromFile(std::string(sAppFunctions::get_resources_dir() + myConst::item_img_poison_small_regeneration)))
            this->m_shape.setTexture(&this->m_texture);
        else
            Logger::log("ERROR::ITEM::COULD_NOT_LOAD_TEXTURE", "Items::PoisonSmallRegeneration", logType::WARNING);

        this->m_Usable = true;
        this->m_stacable = true;
        this->m_price = { 0, 1, 25 };
        this->m_pickable = true;
        this->m_amount = 1;
        this->m_maxAmount = 2;
        this->item_ID = 1;
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

    void update(const float& delta_time, sf::Vector2i mouse_pos) override { }
};
}
#endif /* item_poison_small_regeneration_hpp */