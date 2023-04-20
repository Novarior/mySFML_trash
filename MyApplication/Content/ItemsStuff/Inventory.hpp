#ifndef ITEMSTUFF_INVENTORY_H
#define ITEMSTUFF_INVENTORY_H
#include "Item.hpp"
#include "Coins.hpp"

class Cell:public sf::Drawable
{
    public:
    sf::Texture& m_texture;
    sf::RectangleShape m_shape;
    Cell(sf::Vector2f pos, float cell_size, sf::Texture& texture):m_texture(texture)
    {
        m_shape.setPosition(pos);
        m_shape.setSize(sf::Vector2f(cell_size, cell_size));
        m_shape.setTexture(&m_texture);
    }
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw((m_shape));
    }
};

class Inventory
{
    public:
    Inventory(sf::Vector2f screen_size, float cell_size);
    virtual ~Inventory();
    std::vector<Cell> CellsInventory;

    void update(const float& delta_time);
    void render(sf::RenderTarget* target);

    private:
    sf::RectangleShape m_CellInvenrotyShape;
    sf::Texture m_CellInvTex;
    sf::RectangleShape m_BackShape;
    std::vector<Item> m_ItemVec;
    Item m_Item;
    Coins m_Coins;
};
#endif