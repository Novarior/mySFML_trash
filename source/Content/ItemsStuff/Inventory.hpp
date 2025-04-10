#ifndef INVENTORY
#define INVENTORY

#include "Coins.hpp"
#include "Items/ItemRegister.hpp"

class Inventory {
public:
  Inventory(unsigned int rows, unsigned int cols);
  virtual ~Inventory();

  // Основные функции
  unsigned int getCurrentCellID(sf::Vector2i mouse_pos) const;
  void update(sf::Vector2i mouse_pos);
  void render(sf::RenderTarget &target);

  // Функции для работы с предметами
  bool addItem(std::shared_ptr<Item> _item);
  //  bool removeItem(std::shared_ptr<Item> _item);
  bool removeItemByID(unsigned int _id);
  void clearInventory();

  std::shared_ptr<Item> getItem(unsigned int _id) const;
  std::shared_ptr<Item> getItemFromSlot(unsigned int slot) const;

  // get cells

  // get inventory array
  const std::vector<std::vector<std::shared_ptr<Item>>> &
  getInventoryArray() const {
    return InventoryArray;
  }

  // Управление открытием/закрытием инвентаря
  void openInventory() { isOpened = true; }
  void closeInventory() { isOpened = false; }
  void toggleInventory() { isOpened = !isOpened; }
  const bool isInventoryOpened() const { return isOpened; }

  // Получение состояния
  int getTotalSlots() const;
  Coins &getCoins();

  void initializeCells(unsigned int rows, unsigned int cols, float cell_size,
                       sf::Vector2f _offset);

  // for GUI

private:
  bool isOpened; // Открыт ли инвентарь

  // Слоты для предметов
  std::vector<std::vector<std::shared_ptr<Item>>> InventoryArray;

  sf::Vector2f inventoryPosition;

  // Монеты
  Coins m_Coins;
};

#endif /* INVENTORY */
