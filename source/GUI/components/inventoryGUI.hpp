#ifndef INVENTORY_GUI_HPP
#define INVENTORY_GUI_HPP

#include "../../Content/ItemsStuff/Inventory.hpp"

namespace GUI {
class Cell : public sf::Drawable {
public:
  Cell(sf::Vector2f pos, float cell_size, unsigned int ID = 0)
      : m_texture(TextureManager::getTexture("inventory_cell_texture")),
        m_ID_Cell(ID) {
    m_shape.setPosition(pos);
    m_shape.setSize(sf::Vector2f(cell_size, cell_size));
    m_shape.setTexture(&m_texture);
    m_shape.setFillColor(sf::Color(40, 40, 40, 127));
    m_shape.setOutlineThickness(-1.f);
    m_shape.setOutlineColor(sf::Color::Green);
  }

  virtual ~Cell() {}

  const unsigned int getIDCell() const { return this->m_ID_Cell; }
  void setID(unsigned int newID) { m_ID_Cell = newID; }

  const sf::Vector2f getPosition() const { return m_shape.getPosition(); }
  const sf::Vector2f getSize() const { return m_shape.getSize(); }

  inline const bool getGlobalBounds(sf::Vector2i mouse_pos) {
    return m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos));
  }

  void update(sf::Vector2i mouse_pos) {
    sf::Color newColor =
        m_shape.getGlobalBounds().contains(sf::Vector2f(mouse_pos))
            ? sf::Color::Green
            : sf::Color(80, 70, 40, 127);

    if (m_shape.getOutlineColor() != newColor) {
      m_shape.setOutlineColor(newColor);
    }
  }

private:
  unsigned int m_ID_Cell;
  sf::Texture m_texture;
  sf::RectangleShape m_shape;

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw((m_shape));
  }
};

class InventoryGUI : public sf::Drawable {
private:
  // Weak pointer to the inventory object
  std::weak_ptr<Inventory> m_inventory;
  // Background for the inventory GUI
  sf::RectangleShape m_background_inventory;
  // Text for the inventory GUI
  sf::Text m_text_Coins;
  sf::Text m_text_Inventory;
  sf::Text m_hovered_item_text;

  // Font for the text and some other elements
  sf::Font &m_font;

public:
  InventoryGUI(std::weak_ptr<Inventory> _inventory, sf::Vector2f _screen_size,
               sf::Font &_font, float _cell_size, unsigned int _character_size);

  void update(const float &delta_time);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
} // namespace GUI

#endif /* INVENTORYGUI */
