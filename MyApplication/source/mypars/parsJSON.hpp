#ifndef PARSER_JSON_FILE_HPP
#define PARSER_JSON_FILE_HPP
#include "../../header.h"
#include "../../entitys/player.hpp"
#include "../../Content/ItemsStuff/Inventory.hpp"

namespace mypars {
    class parsJSON {
        public:
        parsJSON();
        virtual ~parsJSON();

        //load functions from json file
        const bool loadPlayer(const std::string& filename, Player& player);
        const bool loadInventory(const std::string& filename, Inventory& inventory);
        const bool loadKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds);

        //save functions to json file
        const bool savePlayer(const std::string& filename, Player* player);
        const bool saveInventory(const std::string& filename, Inventory* inventory);
        const bool saveEntitys(const std::string& filename, std::vector<Entity*> entitys);
        const bool saveGameData(const std::string& filename);
        const bool saveKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds);


        private:


    };
}; // namespace mypars
#endif // PARSER_JSON_FILE_HPP