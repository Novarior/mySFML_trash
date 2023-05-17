#ifndef ITEMSTUFF_INVENTORY_H
#define ITEMSTUFF_INVENTORY_H
#include "Item.hpp"
#include "Coins.hpp"
#include "Items/itemlist.hpp"

class Cell : public sf::Drawable
{
    public:
    Cell(sf::Vector2f pos, float cell_size, sf::Texture& texture, unsigned int ID) :m_texture(texture) {
        m_shape.setPosition(pos);
        m_shape.setSize(sf::Vector2f(cell_size, cell_size));
        m_shape.setTexture(&m_texture);
        m_shape.setOutlineThickness((-cell_size) * 1 / 16);
    }
    virtual ~Cell() {}
    const unsigned int getID(sf::Vector2i mouse_pos);
    const sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    const sf::Vector2f getSize() const { return m_shape.getSize(); }

    const bool getGlobalBounds(sf::Vector2i mouse_pos) {
        return m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos));
    }
    void update(sf::Vector2i mouse_pos) {
        m_shape.setOutlineColor(sf::Color::Transparent);
        if (m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
            m_shape.setOutlineColor(sf::Color(255, 255, 255, 120));
        }
    }

    private:
    unsigned int m_ID;
    sf::Texture& m_texture;
    sf::RectangleShape m_shape;
    const unsigned int getCountID() { return this->m_ID; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw((m_shape));
    }
};

class Inventory
{
    public:
    Inventory(sf::Vector2f screen_size, float cell_size, sf::Font& font, unsigned int character_size);
    virtual ~Inventory();

    const unsigned int getCurrentCellID(sf::Vector2i mousePos);
    void update(sf::Vector2i mouse_pos);
    void render(sf::RenderTarget& target);

    private:
    void initVectorItems();

    sf::Font& m_font;
    sf::Text m_Text;
    std::stringstream m_StringStream;
    std::vector<Cell> CellsInventory;
    std::vector<Item*> m_ItemVector;
    sf::RectangleShape m_CellInvenrotyShape;
    sf::Texture m_CellInvTex;
    sf::RectangleShape m_BackShape;
    Coins* m_Coins;
};
#endif