#include "parsJSON.hpp"
using namespace mypars;

parsJSON::parsJSON() { }
parsJSON::~parsJSON() { }

// load playes
const bool parsJSON::loadPlayer(const std::string& filename, Entity& player)
{ // open json file
    std::ifstream ifs;
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::PLAYER::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // load from json file

    return true;
}
// load inventory
const bool parsJSON::loadInventory(const std::string& filename, Inventory& inventory)
{ // open json file
    std::ifstream ifs;
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::INVENTORY::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    return true;
}
// load  entitys
const bool parsJSON::loadEntitys(const std::string& filename, std::vector<Entity*>& entitys)
{ // open json file
    std::ifstream ifs(filename);
    std::string line;
    int value = 0;
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::ENTITYS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // load from json file
    while (std::getline(ifs, line)) {
        // check if line is not empty
        if (line != "") {
            // skip "entity list" and all special symbols
            if (line.find("entity list") != std::string::npos)
                continue;
            if (line.find("{") != std::string::npos)
                continue;
            if (line.find("}") != std::string::npos)
                continue;
            if (line.find("[") != std::string::npos)
                continue;
            if (line.find("]") != std::string::npos)
                continue;

            if (line.find("ID_record") != std::string::npos) {
                // get entity ID_record
                value = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
            } else if (line.find("entity_uid") != std::string::npos) {
                // get entity UID
                value = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
            } else if (line.find("position") != std::string::npos) {
                // get entity position
                int x = std::stoi(line.substr(line.find("x") + 4, line.find(",") - line.find("x") - 4)),
                    y = std::stoi(line.substr(line.find("y") + 4, line.find("}") - line.find("y") - 4));
                entitys[value]->e_setPosition(sf::Vector2f(x, y));
            } else if (line.find("attributes") != std::string::npos) {
                // get entity attributes
                int hp = std::stoi(line.substr(line.find("hp") + 4, line.find(",") - line.find("hp") - 4)),
                    max_hp = std::stoi(line.substr(line.find("max_hp") + 8, line.find(",") - line.find("max_hp") - 8)),
                    level = std::stoi(line.substr(line.find("level") + 6, line.find("}") - line.find("level") - 6));
                entitys[value]->getAttributes()->getAttributes()->health = hp;
                entitys[value]->getAttributes()->getAttributes()->max_health = max_hp;
                entitys[value]->getAttributes()->getAttributes()->level = level;

            } else {
                // if line is not empty and not special symbols, then this is error
                printf("ERROR::PARSER::LOAD::ENTITYS::UNKNOWN_LINE\n   %s\n", line.c_str());
                return false;
            }

            // if entity is not null
            if (entitys[value] != nullptr) {
                // set entity ID_record
                entitys[value]->e_setID(value);
            }
        }
    }
    return true;
}
// load keybinds
const bool parsJSON::loadKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds)
{ // load key binds from json file
    std::ifstream ifs(filename);
    std::string line;
    std::string name = "";
    int value = 0;
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::KEYBINDS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // load from json file
    while (std::getline(ifs, line)) {
        // check if line is not empty
        if (line != "") {
            // skip "key_binds" and all special symbols
            if (line.find("key_binds") != std::string::npos)
                continue;
            if (line.find("{") != std::string::npos)
                continue;
            if (line.find("}") != std::string::npos)
                continue;
            if (line.find("[") != std::string::npos)
                continue;
            if (line.find("]") != std::string::npos)
                continue;

            if (line.find("name") != std::string::npos) {
                // get key bind name
                name = line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4);
            } else if (line.find("key") != std::string::npos) {
                // get key bind key
                value = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
            }
            keyBinds[name] = value;
        }
    }

    // close file
    ifs.close();
    return true;
}
// load noice data
const bool parsJSON::loadNoiceData(const std::string& filename, noiceData& data)
{ // load noice data
    std::ifstream ifs(filename);
    std::string line;
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::NOICEDATA::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // load from json file
    while (std::getline(ifs, line)) {
        // check if line is not empty
        if (line != "") {
            // skip "game_data" and all special symbols
            if (line.find("game_data") != std::string::npos)
                continue;
            if (line.find("{") != std::string::npos)
                continue;
            if (line.find("}") != std::string::npos)
                continue;
            if (line.find("[") != std::string::npos)
                continue;
            if (line.find("]") != std::string::npos)
                continue;
            // read noise data
            if (line.find("seed") != std::string::npos) {
                data.seed = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }
            if (line.find("octaves") != std::string::npos) {
                data.octaves = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }
            if (line.find("frequency") != std::string::npos) {
                data.frequency = std::stof(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }
            if (line.find("amplifire") != std::string::npos) {
                data.amplifire = std::stof(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }
            if (line.find("persistence") != std::string::npos) {
                data.persistence = std::stof(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }
            if (line.find("smooth") != std::string::npos) {
                data.smoothMode = std::stoi(line.substr(line.find(":") + 2, line.find("}") - line.find(":") - 2));
                continue;
            }

        } else {
            // if line is not empty and not special symbols, then this is error
            printf("ERROR::PARSER::LOAD::NOICEDATA::UNKNOWN_LINE\n   %s\n", line.c_str());
            return false;
        }
        // set noice data
    }

    return true;
}
// load gameData
const bool parsJSON::loadGameData(const std::string& filename, Gamedata data)
{ // load game data
    std::ifstream ifs(filename);
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    json js = json::parse(ifs);
    js.at("game_data").at("is_game_started").get_to(data.game_started);

    return true;
}
// SAVES
// save player
const bool parsJSON::savePlayer(const std::string& filename, Entity* player)
{
    // open json file
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::OPEN::PLAYER::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // save to json file
    json jk;
    jk["player"];
    jk["player"]["entity_uid"] = player->e_getID();
    jk["player"]["position"]["x"] = player->e_getPosition().x;
    jk["player"]["position"]["y"] = player->e_getPosition().y;
    // save player attributes
    jk["player"]["attributes"];
    jk["player"]["attributes"]["hp"] = player->getAttributes()->getAttributes()->health;
    jk["player"]["attributes"]["max_hp"] = player->getAttributes()->getAttributes()->max_health;
    jk["player"]["attributes"]["current_exp"] = player->getAttributes()->getAttributes()->experience;
    jk["player"]["attributes"]["exp_for_level"] = player->getAttributes()->getAttributes()->experience_for_level;
    jk["player"]["attributes"]["level"] = player->getAttributes()->getAttributes()->level;
    jk["player"]["attributes"]["some_points"] = player->getAttributes()->getAttributes()->some_points;
    // close file
    ofs << std::setw(4) << jk;
    ofs.close();
    return true;
}
// save inventory
const bool parsJSON::saveInventory(const std::string& filename, Inventory* inventory)
{
    // save player inventory
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::OPEN::INVENTORY::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // save to json file
    // variables
    json jk;
    std::vector<std::vector<Item*>> iArr = inventory->getInventoryArray();

    jk["inventory"];
    jk["inventory"]["size"] = inventory->getSizeInventory();
    jk["inventory"]["items"];
    int slot = 0;
    // save items
    for (auto& row : iArr) {
        for (auto& item : row) {
            // check item if null
            if (item != nullptr) { // write "slot if is not empty
                jk["inventory"]["items"][slot]["slot"] = inventory->getNumSlot(item);
                jk["inventory"]["items"][slot]["name"] = item->getName();
                jk["inventory"]["items"][slot]["amount"] = item->getAmount();
                jk["inventory"]["items"][slot]["price"];
                jk["inventory"]["items"][slot]["price"]["Gold"] = item->getPrice().get_GoldCointCount();
                jk["inventory"]["items"][slot]["price"]["Silver"] = item->getPrice().get_SilverCointCount();
                jk["inventory"]["items"][slot]["price"]["Copper"] = item->getPrice().get_CopperCointCount();
                jk["inventory"]["items"][slot]["stackable"] = item->isStackable();
                jk["inventory"]["items"][slot]["usable"] = item->isUsable();
                jk["inventory"]["items"][slot]["unic ID"] = item->getID();
            } else {
                // write "slot" if is empty
                jk["inventory"]["items"][slot]["slot"] = nullptr;
                jk["inventory"]["items"][slot]["name"] = nullptr;
                jk["inventory"]["items"][slot]["amount"] = nullptr;
                jk["inventory"]["items"][slot]["price"] = nullptr;
                jk["inventory"]["items"][slot]["stackable"] = nullptr;
                jk["inventory"]["items"][slot]["usable"] = nullptr;
                jk["inventory"]["items"][slot]["unic ID"] = nullptr;
            }
            slot++;
        }
    }

    jk["inventory"]["coins"];
    jk["inventory"]["coins"]["gold"] = inventory->getCoins().get_GoldCointCount();
    jk["inventory"]["coins"]["silver"] = inventory->getCoins().get_SilverCointCount();
    jk["inventory"]["coins"]["copper"] = inventory->getCoins().get_CopperCointCount();
    // save to json file
    ofs << std::setw(4) << jk;
    // close file
    ofs.close();
    return true;
}
// save entitys
const bool parsJSON::saveEntitys(const std::string& filename, std::vector<Entity*> entitys)
{
    // open json file
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::OPEN::ENTITYS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }

    // save to json file
    json jk;
    jk["entity list"];
    // save entitys
    for (size_t i = 0; i < entitys.size(); i++) {
        // check entity if null, is null continue
        if (entitys[i] == nullptr || entitys[i]->e_getAlive() == false)
            continue;

        jk["entity list"][i];
        jk["entity list"][i]["ID_record"] = i;
        jk["entity list"][i]["entity_uid"] = entitys[i]->e_getID();
        jk["entity list"][i]["position"]["x"] = entitys[i]->e_getPosition().x;
        jk["entity list"][i]["position"]["y"] = entitys[i]->e_getPosition().y;
        // save entity attributes
        jk["entity list"][i]["attributes"];
        jk["entity list"][i]["attributes"]["hp"] = entitys[i]->getAttributes()->getAttributes()->health;
        jk["entity list"][i]["attributes"]["max_hp"] = entitys[i]->getAttributes()->getAttributes()->max_health;
        jk["entity list"][i]["attributes"]["level"] = entitys[i]->getAttributes()->getAttributes()->level;
    }
    // save to json file
    ofs << std::setw(4) << jk;
    // close file
    ofs.close();
    return true;
}
// save noicedata
const bool parsJSON::saveNoiceData(const std::string& filename, noiceData _dataNoice)
{
    // open json file
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // save to json file
    ofs << "{\n";
    // noice section
    ofs << "\t\"noice\": {\n";
    ofs << "\t\t\"seed\": " << _dataNoice.seed << ",\n";
    ofs << "\t\t\"octaves\": " << _dataNoice.octaves << ",\n";
    ofs << "\t\t\"frequency\": " << _dataNoice.frequency << ",\n";
    ofs << "\t\t\"amplifire\": " << _dataNoice.amplifire << ",\n";
    ofs << "\t\t\"persistence\": " << _dataNoice.persistence << ",\n";
    ofs << "\t\t\"smooth\": " << _dataNoice.smoothMode << "\n";
    ofs << "\t}\n";
    ofs << "}\n";

    // close file
    ofs.close();
    return true;
}
// save keybinds
const bool parsJSON::saveKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds)
{
    // save key binds to json file on json format key : value
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::OPEN::KEYBINDS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
    }

    // save to json file
    json jk;
    jk["key_binds"];
    // save key binds
    for (auto& i : keyBinds) {
        jk["key_binds"][i.first] = i.second;
    }
    // save to json file
    ofs << std::setw(4) << jk;
    // close file
    ofs.close();
    return true;
}
// save gamedata
const bool parsJSON::saveGameData(const std::string& filename, Gamedata& data)
{
    // save game data
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::SAVE::GAMEDATA::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    json jk;
    // save to json file
    jk["game_data"];
    jk["game_data"]["is_game_started"] = data.game_started;
    // save to json file
    ofs << std::setw(4) << jk;
    // close file
    ofs.close();
    return true;
}
