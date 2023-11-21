#ifndef PARSER_JSON_FILE_HPP
#define PARSER_JSON_FILE_HPP
#include "../../Content/ItemsStuff/Inventory.hpp"

#include "../../entitys/entity.hpp"
#include "../../entitys/player.hpp"
#include "../../math/ProcessGenerationNoice.hpp"
#include "../../states/State.hpp"
class Gamedata;

namespace mypars {
class parsJSON {
private:
    json m_js;

public:
    parsJSON();
    virtual ~parsJSON();

    // load functions from json file
    const bool loadPlayer(const std::string& filename, Entity& player);
    const bool loadGameData(const std::string& filename, Gamedata data);
    const bool loadNoiceData(const std::string& filename, mmath::noiceData& data);
    const bool loadInventory(const std::string& filename, Inventory& inventory);
    const bool loadEntitys(const std::string& filename, std::vector<Entity*>& entitys);
    const bool loadKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds);

    // save functions to json file
    const bool savePlayer(const std::string& filename, Entity* player);
    const bool saveGameData(const std::string& filename, Gamedata& data);
    const bool saveNoiceData(const std::string& filename, mmath::noiceData data);
    const bool saveInventory(const std::string& filename, Inventory* inventory);
    const bool saveEntitys(const std::string& filename, std::vector<Entity*> entitys);
    const bool saveKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds);
};
}; // namespace mypars
#endif // PARSER_JSON_FILE_HPP