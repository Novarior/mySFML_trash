#ifndef PARSER_JSON_FILE_HPP
#define PARSER_JSON_FILE_HPP

#include "../../Content/ItemsStuff/Inventory.hpp"
#include "../../Nodes/Node.hpp"
#include "../../entitys/entity.hpp"
#include "../../entitys/player.hpp"
#include "../../math/ProcessGenerationNoice.hpp"
#include "../../states/State.hpp"

class Gamedata;

class NodeViewer;

class ParserJson {
public:
    ParserJson() { }
    virtual ~ParserJson() { }

    // load functions from json file
    static const bool loadPlayer(Entity& player);
    static const bool loadNoiceData(mmath::noiceData& data);
    static const bool loadInventory(Inventory* inventory);
    static const bool loadEntitys(std::vector<Entity*>& entitys);
    static const bool loadKeyBinds(std::map<std::string, int>& keyBinds);

    // save functions to json file
    static const bool savePlayer(Entity* player);
    static const bool saveNoiceData(mmath::noiceData data);
    static const bool saveInventory(Inventory* inventory);
    static const bool saveEntitys(std::vector<Entity*> entitys);
    static const bool saveKeyBinds(std::map<std::string, int>& keyBinds);
    static const bool saveNodesdata(std::vector<Node*> mNode);
};

#endif // PARSER_JSON_FILE_HPP