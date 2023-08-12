#ifndef ITEMSTUFF_INVENTORY_H
#define ITEMSTUFF_INVENTORY_H
#include "Coins.hpp"
#include "Item.hpp"
#include "Items/itemlist.hpp"

class Cell : public sf::Drawable {
public:
    Cell(sf::Vector2f pos, float cell_size, sf::Texture& texture, unsigned int ID = 0)
        : m_texture(texture)
    {
        m_shape.setPosition(pos);
        m_shape.setSize(sf::Vector2f(cell_size, cell_size));
        m_shape.setTexture(&m_texture);
        m_shape.setOutlineThickness((-cell_size) * 1 / 16);
    }
    virtual ~Cell() { }

    const unsigned int getID(sf::Vector2i mouse_pos) { return this->m_ID; }

    const sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    const sf::Vector2f getSize() const { return m_shape.getSize(); }

    inline const bool getGlobalBounds(sf::Vector2i mouse_pos) { return m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos)); }

    inline void update(sf::Vector2i mouse_pos)
    {
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

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw((m_shape));
    }
};

class Inventory {
public:
    Inventory(sf::Vector2f screen_size, float gridSize_cell, sf::Font& font, unsigned int character_size);
    virtual ~Inventory();

    const unsigned int getCurrentCellID(sf::Vector2i mousePos);
    void update(sf::Vector2i mouse_pos);
    void render(sf::RenderTarget& target);

    // funcrions for manipulating with items
    void addItem(Item* item);
    void removeItem(Item* item);
    void removeItem(unsigned int ID);
    void clear();

    Item* getItem(unsigned int ID);
    Item* getItemFromNumSlot(unsigned int num_slot);

    // functions for manipulating with inventory
    void openInventory();
    void closeInventory();
    void toggleSwitch() { this->isOpened = !this->isOpened; }
    const bool getIsOpened() const { return this->isOpened; }
    const int getSizeInventory() { return this->CellsInventory.size(); }

    // functions for manipulating with coins
    Coins* getCoins();

private:
    bool isOpened;

    // containers for items and ect.
    Coins* m_Coins;
    std::map<unsigned int, Item*> m_InventoryMap;
    std::vector<Cell> CellsInventory;

    // variables
    sf::Font& m_font;
    sf::Text m_Text;
    std::stringstream m_StringStream;
    sf::RectangleShape m_CellInvenrotyShape;
    sf::Texture m_CellInvTex;
    sf::RectangleShape m_background_inventory;
};
#endif