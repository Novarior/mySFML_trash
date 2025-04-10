#ifndef ITEMREGISTER
#define ITEMREGISTER

#include "../Item.hpp"
#include "item_NULL.hpp"
#include "item_poison_small_regeneration.hpp"
#include "item_stone.hpp"

class ItemRegistry {
private:
  static std::map<int, std::shared_ptr<Item>> items;

public:
  static bool registerItem(int id, std::shared_ptr<Item> item) {
    if (items.find(id) == items.end()) {
      items[id] = item;
      Logger::logStatic("Item with id: " + std::to_string(id) +
                            " has been registered",
                        "ItemRegistry", logType::INFO);
      return true;
    } else {
      Logger::logStatic("Item with id: " + std::to_string(id) +
                            " alredy was bew registered",
                        "ItemRegistry", logType::WARNING);
      return false; // Item with this ID already exists
    }
  }

  static std::shared_ptr<Item> getItem(int id) {
    auto it = items.find(id);
    if (it != items.end())
      return it->second; // Возвращаем
    else
      return items[0]; // Return a default item if not found
  }

  static const std::map<int, std::shared_ptr<Item>> &getAllItems() {
    return items;
  }

  static void unregisterItem(int id) { items.erase(id); }

  static bool containsItem(int id) { return items.find(id) != items.end(); }
};

#endif /* ITEMREGISTER */
