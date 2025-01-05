#ifndef PARSER_JSON_FILE_HPP
#define PARSER_JSON_FILE_HPP

#include "../../Content/ItemsStuff/Inventory.hpp"
#include "../../entitys/entity.hpp"
#include "../../entitys/player.hpp"
#include "../../math/ProcessGenerationNoice.hpp"
#include "../../states/VolumeManager.hpp"

class Gamedata;
class NodeViewer;

// The ParserJson class provides methods for loading and saving game data to/from a JSON file
class ParserJson {
public:
    ParserJson() { }
    virtual ~ParserJson() { }

    // Load functions from JSON file
    static const bool loadPlayer(Entity& player); // Load player data
    static const bool loadNoiceData(mmath::noiceData& data); // Load noise data
    static const bool loadInventory(const std::shared_ptr<Inventory>& inventory); // Load inventory data
    static const bool loadEntitys(std::vector<Entity*>& entitys); // Load entities data
    static const bool loadKeyBinds(std::map<std::string, int>& keyBinds); // Load key bindings
    static const bool loadSoundVolumes(VolumeManager* data); // Load game data

    // Save functions to JSON file
    static const bool savePlayer(Entity* player); // Save player data
    static const bool saveNoiceData(mmath::noiceData data); // Save noise data
    static const bool saveInventory(const std::shared_ptr<Inventory>& inventory); // Save inventory data
    static const bool saveEntitys(std::vector<Entity*> entitys); // Save entities data
    static const bool saveKeyBinds(std::map<std::string, int>& keyBinds); // Save key bindings
    static const bool saveSoundVolumes(VolumeManager* data); // Save game data
};

#endif // PARSER_JSON_FILE_HPP