#ifndef item_poison_small_regeneration_hpp
#define item_poison_small_regeneration_hpp
#include "../Item.hpp"

class PoisonSmallRegeneration : public Item {
private:
public:
    PoisonSmallRegeneration(unsigned int gridSizeI, std::string texture_path, bool stacable, int quantity, int price, bool picked_up)
    {
        this->m_name = "Poison of Regeneration";
        this->m_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
        this->m_Usable = true;

        if (this->m_texture.loadFromFile(texture_path))
            this->m_shape.setTexture(&this->m_texture);

        this->m_stacable = stacable;
        this->m_quantity = quantity;
        this->m_price = price;
        this->m_pickable = picked_up;
    }
    virtual ~PoisonSmallRegeneration() { }

    void useItem() override
    {
        // print to console that you used this item
        std::cout << "You used " << this->m_name << std::endl;
        // add regeneration to player
        // remove item from inventory
        // if quantity == 0 remove item from inventory

        if (this->m_quantity <= 0)
            this->~PoisonSmallRegeneration();
        else if (this->m_quantity > 0)
            this->m_quantity--;
        else
            std::cout << "Error: Quantity of item is less than 0" << std::endl;
    }

    void update(const float& delta_time, sf::Vector2i mouse_pos) override { }
    void render(sf::RenderTarget& target) override
    {
        target.draw(this->m_shape);
    }
};
#endif /* item_poison_small_regeneration_hpp */