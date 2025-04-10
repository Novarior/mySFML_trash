#include "inventoryGUI.hpp"

GUI::InventoryGUI::InventoryGUI(std::weak_ptr<Inventory> _inventory,
                                sf::Vector2f _screen_size, sf::Font &_font,
                                float _cell_size, unsigned int _character_size)
    : m_inventory(_inventory), m_font(_font),
      m_hovered_item_text(_font, "", _character_size),
      m_text_Inventory(_font, "", _character_size),
      m_text_Coins(_font, "", _character_size) {
  // Initialize the inventory GUI with the provided parameters
  // calculate the background size 70% of the screen size
  sf::Vector2f bsize(mmath::p2pX(0.7f, _screen_size.x),
                     mmath::p2pY(0.7f, _screen_size.y));
  m_background_inventory.setSize(bsize);
  m_background_inventory.setPosition(
      {_screen_size.x / 2 - bsize.x / 2, _screen_size.y / 2 - bsize.y / 2});
  m_background_inventory.setFillColor(sf::Color(41, 49, 51));

  // Initialize the text for coins
  m_text_Coins.setFillColor(sf::Color::White);
  m_text_Coins.setPosition({m_background_inventory.getPosition().x + 10,
                            m_background_inventory.getPosition().y + 10});
  m_text_Coins.setString("Coins: ");

  // Initialize the text for inventory
  m_text_Inventory.setFillColor(sf::Color::White);
  m_text_Inventory.setPosition({m_background_inventory.getPosition().x + 10,
                                m_background_inventory.getPosition().y + 40});
  m_text_Inventory.setString("Inventory");

  // Initialize the hovered item text
  m_hovered_item_text.setFillColor(sf::Color::White);
  m_hovered_item_text.setPosition(
      {m_background_inventory.getPosition().x + 10,
       m_background_inventory.getPosition().y + 70});
  m_hovered_item_text.setString("Hovered Item: ");
}

void GUI::InventoryGUI::draw(sf::RenderTarget &target,
                             sf::RenderStates states) const {

  // Отображение фона и ячеек
  target.draw(m_background_inventory);
  for (const auto &row : m_inventory.lock()->getCellsInventory()) {
    for (const auto &cell : row) {
      target.draw(cell);
    }
  }

  // Отображение текста монет
  target.draw(m_text_Coins);
  target.draw(m_text_Inventory);

  // Отображение предметов
  for (const auto &row : m_inventory.lock()->getInventoryArray()) {
    for (const auto &item : row) {
      if (item) {
        item->render(target);
      }
    }
  }
}