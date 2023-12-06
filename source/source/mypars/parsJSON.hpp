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
    const bool loadPlayer(Entity& player);
    const bool loadGameData(Gamedata data);
    const bool loadNoiceData(mmath::noiceData& data);
    const bool loadInventory(Inventory& inventory);
    const bool loadEntitys(std::vector<Entity*>& entitys);
    const bool loadKeyBinds(std::map<std::string, int>& keyBinds);

    // save functions to json file
    const bool savePlayer(Entity* player);
    const bool saveGameData(Gamedata& data);
    const bool saveNoiceData(mmath::noiceData data);
    const bool saveInventory(Inventory* inventory);
    const bool saveEntitys(std::vector<Entity*> entitys);
    const bool saveKeyBinds(std::map<std::string, int>& keyBinds);
};
}; // namespace mypars
#endif // PARSER_JSON_FILE_HPP