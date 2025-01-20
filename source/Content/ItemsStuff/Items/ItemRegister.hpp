#ifndef itemlist_hpp
#define itemlist_hpp

#include "../Item.hpp"
#include "item_poison_small_regeneration.hpp"
#include "item_stone.hpp"

class ItemRegistry {
private:
    static std::map<int, std::shared_ptr<Item>> items;

public:
    static bool registerItem(int id, std::shared_ptr<Item> item)
    {
        if (items.find(id) == items.end()) {
            items[id] = item;
            Logger::logStatic("Item with id: " + std::to_string(id) + " has been registered", "ItemRegistry", logType::INFO);
            return true;
        } else {
            Logger::logStatic("Item with id: " + std::to_string(id) + " alredy was bew registered", "ItemRegistry", logType::WARNING);
            return false; // Item with this ID already exists
        }
    }

    static Item* getItem(int id)
    {
        if (items.find(id) != items.end())
            return items[id].get();
        else
            return nullptr;
    }
    static std::vector<Item*> getAllItems()
    {
        std::vector<Item*> allItems;
        for (const auto& pair : items)
            allItems.push_back(pair.second.get());
        return allItems;
    }
    static void unregisterItem(int id) { items.erase(id); }

    static bool containsItem(int id) { return items.find(id) != items.end(); }
};

#endif /* itemlist_hpp */
