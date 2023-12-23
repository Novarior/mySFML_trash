#include "parsJSON.hpp"

// load playes
const bool ParserJson::loadPlayer(Entity& player)
{ // open json file
    std::ifstream ifs(sAppFunctions::getDocumentsAppFolder() + myConst::config_playerdata);
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::PLAYER::FILE_NOT_OPEN\n   %s\n", myConst::config_playerdata);
        return false;
    }
    // load from json file

    return true;
}
// load inventory
const bool ParserJson::loadInventory(Inventory* inventory)
{ // Check if inventory is null
    if (!inventory) {
        printf("ERROR::PARSER::LOAD::INVENTORY::INVENTORY_IS_NULL\n");
        return false;
    }

    // Open the file
    std::ifstream ifs(sAppFunctions::getDocumentsAppFolder() + myConst::config_inventory);

    // Check if the file is open
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::LOAD::INVENTORY::FILE_NOT_OPEN\n   %s\n", myConst::config_inventory);
        return false;
    }

    // Parse the JSON from the file
    try {
        json j;
        ifs >> j;

        // Load items
        for (auto& item : j["inventory"]["items"]) {
            if (item["slot"] != nullptr) {
                // Create a new item
                Item* newItem = static_cast<Item*>(ItemRegistry::getItem(item["unic ID"]));

                // Add the item to the inventory
                inventory->addItem(newItem);
            }
        }

        // Load coins
        inventory->getCoins().set_GoldCoinCouns(j["inventory"]["coins"]["gold"]);
        inventory->getCoins().set_SilverCoinCouns(j["inventory"]["coins"]["silver"]);
        inventory->getCoins().set_CopperCoinCouns(j["inventory"]["coins"]["copper"]);

    } catch (const std::exception& e) {
        Logger::log("Cant load inventory: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::LOAD::INVENTORY::UNKNOWN_LINE\n   %s\n", e.what());
        return false;
    }

    return true;
}
// load  entitys
const bool ParserJson::loadEntitys(std::vector<Entity*>& entitys)
{ // open json file

    return false;
}
// load keybinds
const bool ParserJson::loadKeyBinds(std::map<std::string, int>& keyBinds)
{ // load key binds from json file
    std::ifstream ifs(sAppFunctions::getDocumentsAppFolder() + myConst::config_keybinds);
    if (!ifs.is_open()) {
        printf("PARSER cant open file: %s\n", std::string(sAppFunctions::getDocumentsAppFolder() + myConst::config_keybinds).c_str());
        Logger::log("Parcer cant open file: " + sAppFunctions::getDocumentsAppFolder() + myConst::config_keybinds, "CORE->PARS", logType::ERROR);
        return false;
    }

    try {
        json j;
        ifs >> j;

        for (auto& element : j["key_binds"].items()) {
            std::string name = element.key();
            int value = element.value();
            keyBinds[name] = value;
        }
    } catch (json::parse_error& e) {
        printf("ERROR::PARSER::JSON::PARSE_ERROR\n   %s\n", e.what());
        Logger::log("JSON parse error: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        return false;
    }

    ifs.close();
    return true;
}

// load noice data
const bool ParserJson::loadNoiceData(mmath::noiceData& data)
{
    // Open the file
    std::ifstream ifs(sAppFunctions::getDocumentsAppFolder() + myConst::config_noicedata);

    // Check if the file is open
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::NOICEDATA::FILE_NOT_OPEN\n   %s\n", myConst::config_playerdata);
        return false;
    }

    // Parse the JSON from the file
    try {
        json j;
        ifs >> j;

        // Read the noise data from the JSON
        data.seed = j["noice"]["seed"];
        data.octaves = j["noice"]["octaves"];
        data.frequency = j["noice"]["frequency"];
        data.amplifire = j["noice"]["amplifire"];
        data.persistence = j["noice"]["persistence"];
        data.smoothMode = j["noice"]["smooth"];
    } catch (const std::exception& e) {
        printf("ERROR::PARSER::LOAD::NOICEDATA::UNKNOWN_LINE\n   %s\n", e.what());
        return false;
    }

    return true;
}

// SAVES
// save player
const bool ParserJson::savePlayer(Entity* player)
{
    // check if player is not null
    if (player == nullptr) {
        Logger::log("Cant save player: player is null", "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::PLAYER::PLAYER_IS_NULL\n");
        return false;
    }
    // save player
    json j;
    j["player"]["attribute"]["damage"] = player->getAttributes()->getAttributes().damage;
    j["player"]["attribute"]["experience"] = player->getAttributes()->getAttributes().experience;
    j["player"]["attribute"]["experience_for_level"] = player->getAttributes()->getAttributes().experience_for_level;
    j["player"]["attribute"]["health"] = player->getAttributes()->getAttributes().health;
    j["player"]["attribute"]["level"] = player->getAttributes()->getAttributes().level;
    j["player"]["attribute"]["mana"] = player->getAttributes()->getAttributes().mana;
    j["player"]["attribute"]["max_health"] = player->getAttributes()->getAttributes().max_health;
    j["player"]["attribute"]["max_mana"] = player->getAttributes()->getAttributes().max_mana;
    j["player"]["attribute"]["regeneration_health"] = player->getAttributes()->getAttributes().regeneration_health;
    j["player"]["attribute"]["regeneration_mana"] = player->getAttributes()->getAttributes().regeneration_mana;
    j["player"]["attribute"]["some_points"] = player->getAttributes()->getAttributes().some_points;

    j["player"]["position"]["x"] = player->e_getPosition().x;
    j["player"]["position"]["y"] = player->e_getPosition().y;
    j["player"]["entity_uid"] = player->e_getID();
    j["player"]["isAlive"] = player->e_isAlive();

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_playerdata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save player: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::PLAYER::FILE_NOT_OPEN\n   %s\n", myConst::config_playerdata);
        return false;
    }

    return true;
}

// save inventory
const bool ParserJson::saveInventory(Inventory* inventory)
{
    // Check if inventory is null
    if (!inventory) {
        printf("ERROR::PARSER::SAVE::INVENTORY::INVENTORY_IS_NULL\n");
        return false;
    }

    // Create a JSON object
    json j;
    j["inventory"]["size"] = inventory->getSizeInventory();
    const std::vector<std::vector<Item*>>& iArr = inventory->getInventoryArray();
    int slot = 0;

    // Save items
    for (const auto& row : iArr) {
        for (const auto& item : row) {
            // Check item if null
            if (item != nullptr) {
                j["inventory"]["items"][slot]["slot"] = inventory->getNumSlot(item);
                j["inventory"]["items"][slot]["name"] = item->getName();
                j["inventory"]["items"][slot]["amount"] = item->getAmount();
                j["inventory"]["items"][slot]["price"]["Gold"] = item->getPrice().get_GoldCointCount();
                j["inventory"]["items"][slot]["price"]["Silver"] = item->getPrice().get_SilverCointCount();
                j["inventory"]["items"][slot]["price"]["Copper"] = item->getPrice().get_CopperCointCount();
                j["inventory"]["items"][slot]["stackable"] = item->isStackable();
                j["inventory"]["items"][slot]["usable"] = item->isUsable();
                j["inventory"]["items"][slot]["unic ID"] = item->getID();
            } else {
                j["inventory"]["items"][slot]["slot"] = NULL;
            }
            slot++;
        }
    }

    j["inventory"]["coins"]["gold"] = inventory->getCoins().get_GoldCointCount();
    j["inventory"]["coins"]["silver"] = inventory->getCoins().get_SilverCointCount();
    j["inventory"]["coins"]["copper"] = inventory->getCoins().get_CopperCointCount();

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_inventory);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save inventory: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::INVENTORY::FILE_NOT_OPEN\n   %s\n", myConst::config_inventory);
    }
    return true;
}

// save entitys
const bool ParserJson::saveEntitys(std::vector<Entity*> entitys)
{
    // Create a JSON object
    json j;

    // Save entities
    size_t i = 0;
    for (const auto& entity : entitys) {
        // Check entity if null, is null continue
        if (entity == nullptr || entity->e_isAlive() == false)
            continue;

        auto& entity_js = j["entity list"][i];
        entity_js["ID_record"] = i;
        entity_js["entity_uid"] = entity->e_getID();
        entity_js["position"]["x"] = entity->e_getPosition().x;
        entity_js["position"]["y"] = entity->e_getPosition().y;
        // Save entity attributes
        const auto& attributes = entity->getAttributes()->getAttributes();
        entity_js["attributes"]["hp"] = attributes.health;
        entity_js["attributes"]["max_hp"] = attributes.max_health;
        entity_js["attributes"]["level"] = attributes.level;
        i++;
    }

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_entitydata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Pars can't save entities" << sAppFunctions::getDocumentsAppFolder() << myConst::config_entitydata;
        Logger::log(ss.str(), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::ENTITYS::FILE_NOT_OPEN\n   %s\n", myConst::config_entitydata);
        return false;
    }

    return true;
}

// save noicedata
const bool ParserJson::saveNoiceData(mmath::noiceData _dataNoice)
{
    // Create a JSON object
    json j;
    j["noice"] = {
        { "seed", _dataNoice.seed },
        { "octaves", _dataNoice.octaves },
        { "frequency", _dataNoice.frequency },
        { "amplifire", _dataNoice.amplifire },
        { "persistence", _dataNoice.persistence },
        { "smooth", _dataNoice.smoothMode },
        { "mapSizeX", _dataNoice.mapSizeX },
        { "mapSizeY", _dataNoice.mapSizeY },
        { "fast Mode", _dataNoice.fastMode }
    };

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_noicedata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save noice data: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n", myConst::config_noicedata);
        return false;
    }

    return true;
}

// save keybinds
const bool ParserJson::saveKeyBinds(std::map<std::string, int>& keyBinds)
{
    // Create a JSON object
    json j;
    for (const auto& i : keyBinds) {
        j["key_binds"][i.first] = i.second;
    }

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_keybinds);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Pars can't save keybinds" << sAppFunctions::getDocumentsAppFolder() << myConst::config_keybinds;
        Logger::log(ss.str(), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::KEYBINDS::FILE_NOT_OPEN\n   %s\n", myConst::config_keybinds);
        return false;
    }

    return true;
}

const bool ParserJson::saveNodesdata(std::vector<Node*> mNode)
{
    json j;

    for (const auto& node : mNode) {
        json nodeJson;
        nodeJson["id"] = node->getId();
        // nodeJson["type"] = node->getType();
        nodeJson["position"]["x"] = node->getPosition().x;
        nodeJson["position"]["y"] = node->getPosition().y;

        for (const auto& port : node->get_InputPorts()) {
            json portJson;
            if (port->getLinkNode() != nullptr) {
                portJson["id"] = port->getIndex();
                portJson["type"] = port->getPortType();
                portJson["connectedTo"] = port->getLinkNode()->getName() + ": " + std::to_string(port->getIndex());
                nodeJson["ports"].push_back(portJson);
            }
        }

        j.push_back(nodeJson);
    }

    // Write the JSON object to the file
    try {
        std::ofstream ofs(sAppFunctions::getDocumentsAppFolder() + myConst::config_nodesdata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Parser can't save nodes" << sAppFunctions::getDocumentsAppFolder() << myConst::config_nodesdata;
        Logger::log(ss.str(), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::NODES::FILE_NOT_OPEN\n   %s\n", myConst::config_nodesdata);
        return false;
    }

    return true;
}
