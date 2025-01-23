#ifndef ITEMSTUFF_INVENTORY_H
#define ITEMSTUFF_INVENTORY_H

#include "Coins.hpp"
#include "Items/ItemRegister.hpp"

class Cell : public sf::Drawable {
public:
    Cell(sf::Vector2f pos, float cell_size, sf::Texture& texture, unsigned int ID = 0)
        : m_texture(texture)
        , m_ID(ID)
    {
        m_shape.setPosition(pos);
        m_shape.setSize(sf::Vector2f(cell_size, cell_size));
        m_shape.setTexture(&m_texture);
        m_shape.setFillColor(sf::Color(40, 40, 40, 127));
        m_shape.setOutlineThickness(-1.f);
        m_shape.setOutlineColor(sf::Color::Green);
    }

    virtual ~Cell()
    {
    }

    const unsigned int getID() const { return this->m_ID; }
    void setID(unsigned int newID) { m_ID = newID; }

    const sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    const sf::Vector2f getSize() const { return m_shape.getSize(); }

    inline const bool getGlobalBounds(sf::Vector2i mouse_pos) { return m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos)); }

    void update(sf::Vector2i mouse_pos)
    {
        if (m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
            m_shape.setOutlineColor(sf::Color::Green);
        } else {
            m_shape.setOutlineColor(sf::Color(80, 70, 40, 127));
        }
    }

private:
    unsigned int m_ID;
    sf::Texture m_texture;
    sf::RectangleShape m_shape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw((m_shape));
    }
};

class Inventory {
public:
    Inventory(sf::Vector2f screen_size, unsigned int rows, unsigned int cols, sf::Font& font, float cell_size);
    virtual ~Inventory();

    // Основные функции
    unsigned int getCurrentCellID(sf::Vector2i mouse_pos) const;
    void update(sf::Vector2i mouse_pos);
    void render(sf::RenderTarget& target);

    // Функции для работы с предметами
    bool addItem(std::shared_ptr<Item> _item);
    //  bool removeItem(std::shared_ptr<Item> _item);
    bool removeItemByID(unsigned int _id);
    void clearInventory();

    std::shared_ptr<Item> getItem(unsigned int _id) const;
    std::shared_ptr<Item> getItemFromSlot(unsigned int slot) const;

    std::vector<std::vector<std::shared_ptr<Item>>> getInventoryArray() const
    {
        return InventoryArray;
    }

    // Управление открытием/закрытием инвентаря
    void openInventory() { isOpened = true; }
    void closeInventory() { isOpened = false; }
    void toggleInventory() { isOpened = !isOpened; }
    const bool isInventoryOpened() const { return isOpened; }

    // Получение состояния
    int getTotalSlots() const;
    Coins& getCoins();

    void initializeCells(unsigned int rows, unsigned int cols, float cell_size);
    void updateTextPosition();

private:
    bool isOpened; // Открыт ли инвентарь

    // Слоты для предметов
    std::vector<std::vector<Cell>> CellsInventory;
    std::vector<std::vector<std::shared_ptr<Item>>> InventoryArray;

    // Монеты
    Coins m_Coins;

    // Для отображения
    sf::Text m_Text;
    sf::Texture m_CellInvTex;
    sf::RectangleShape m_background_inventory;
    std::stringstream m_StringStream;

    // Вспомогательные функции
};

#endif