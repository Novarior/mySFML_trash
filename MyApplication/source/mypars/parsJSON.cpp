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
    std::string line;
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n", filename.c_str());
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
            // read game data
            if (line.find("is_game_started") != std::string::npos) {
                data.game_started = std::stoi(line.substr(line.find(":") + 2, line.find(",") - line.find(":") - 2));
                continue;
            }

        } else {
            // if line is not empty and not special symbols, then this is error
            printf("ERROR::PARSER::LOAD::GAMEDATA::UNKNOWN_LINE\n   %s\n", line.c_str());
            return false;
        }
    }
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
    ofs << "{\n";
    ofs << "\t\"player\": {\n";
    ofs << "\t\t\"entity_uid\":" << player->e_getID() << ",\n";
    ofs << "\t\t\"position\": {\n";
    ofs << "\t\t\t\"x\": " << player->e_getPosition().x << ",\n";
    ofs << "\t\t\t\"y\": " << player->e_getPosition().y << "\n";
    ofs << "\t\t},\n";
    // save player attributes
    ofs << "\t\t\"attributes\": {\n";
    ofs << "\t\t\t\"hp\": " << player->getAttributes()->getAttributes()->health << ",\n";
    ofs << "\t\t\t\"max_hp\": " << player->getAttributes()->getAttributes()->max_health << ",\n";
    ofs << "\t\t\t\"current_exp\": " << player->getAttributes()->getAttributes()->experience << ",\n";
    ofs << "\t\t\t\"exp_for_level\": " << player->getAttributes()->getAttributes()->experience_for_level << ",\n";
    ofs << "\t\t\t\"level\": " << player->getAttributes()->getAttributes()->level << ",\n";
    ofs << "\t\t\t\"some_points\": " << player->getAttributes()->getAttributes()->some_points << "\n";
    ofs << "\t\t}\n";
    ofs << "\t}\n";
    ofs << "}\n";
    // close file
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
    ofs << "{\n";
    ofs << "\t\"inventory\": {\n";
    ofs << "\t\t\"size\": " << inventory->getSizeInventory() << ",\n";
    ofs << "\t\t\"items\": [\n";
    for (size_t i = 0; i < inventory->getSizeInventory(); i++) {
        ofs << "\t\t\t{\n";
        // check item if null
        if (inventory->getItemFromNumSlot(i) != nullptr) {
            // write "slot if is not empty
            ofs << "\t\t\t\t\"slot\": " << i << ",\n";
            ofs << "\t\t\t\t\"name\": \"" << inventory->getItemFromNumSlot(i)->getName() << "\",\n";
            ofs << "\t\t\t\t\"count\": " << inventory->getItemFromNumSlot(i)->getQuantity() << ",\n";
            ofs << "\t\t\t\t\"price\": " << inventory->getItemFromNumSlot(i)->getPrice() << ",\n";
            ofs << "\t\t\t\t\"stackable\": " << inventory->getItemFromNumSlot(i)->getStackable() << ",\n";
            ofs << "\t\t\t\t\"unic ID\": " << inventory->getItemFromNumSlot(i)->getID() << "\n";

            if (i != inventory->getSizeInventory() - 1)
                ofs << "\t\t\t},\n";
            else
                ofs << "\t\t\t}\n";
        } else {
            // write "slot" if is empty
            ofs << "\t\t\t\t\"slot\": " << i << ",\n";
            ofs << "\t\t\t\t\"name\": null,\n";
            ofs << "\t\t\t\t\"count\": null,\n";
            ofs << "\t\t\t\t\"price\": null,\n";
            ofs << "\t\t\t\t\"stackable\": null,\n";
            ofs << "\t\t\t\t\"unic ID\": null\n";

            if (i != inventory->getSizeInventory() - 1)
                ofs << "\t\t\t},\n";
            else
                ofs << "\t\t\t}\n";
        }
    }

    ofs << "\t\t],\n";
    ofs << "\t\t\"coins\": {\n";
    ofs << "\t\t\t\"gold\": " << inventory->getCoins()->get_GoldCointCount() << ",\n";
    ofs << "\t\t\t\"silver\": " << inventory->getCoins()->get_SilverCointCount() << ",\n";
    ofs << "\t\t\t\"copper\": " << inventory->getCoins()->get_CopperCointCount() << "\n";
    ofs << "\t\t}\n";
    ofs << "\t}\n";
    ofs << "}\n";
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
    ofs << "{\n";
    ofs << "\t\"entity list\": [\n";
    // save entitys
    for (size_t i = 0; i < entitys.size(); i++) {
        // check entity if null, is null continue
        if (entitys[i] == nullptr || entitys[i]->e_getAlive() == false)
            continue;

        ofs << "\t\t{\n";
        ofs << "\t\t\t\"ID_record\": " << i << ",\n";
        ofs << "\t\t\t\"entity_uid\":" << entitys[i]->e_getID() << ",\n";
        ofs << "\t\t\t\"position\": {\n";
        ofs << "\t\t\t\t\"x\": " << entitys[i]->e_getPosition().x << ",\n";
        ofs << "\t\t\t\t\"y\": " << entitys[i]->e_getPosition().y << "\n";
        ofs << "\t\t\t},\n";
        ofs << "\t\t\t\"attributes\": {\n";
        ofs << "\t\t\t\t\"hp\": " << entitys[i]->getAttributes()->getAttributes()->health << ",\n";
        ofs << "\t\t\t\t\"max_hp\": " << entitys[i]->getAttributes()->getAttributes()->max_health << ",\n";
        ofs << "\t\t\t\t\"level\": " << entitys[i]->getAttributes()->getAttributes()->level << "\n";
        ofs << "\t\t\t}\n";
        ofs << "\t\t}";
        if (i != entitys.size() - 1) {
            ofs << ",";
        }
        ofs << "\n";
    }
    ofs << "\t]\n";
    ofs << "}\n";
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
    ofs << "{\n";
    ofs << "\t\"key_binds\": [\n";
    for (auto& i : keyBinds) {
        ofs << "\t\t{\n";
        ofs << "\t\t\t\"name\": \"" << i.first << "\",\n";
        ofs << "\t\t\t\"key\": " << i.second << "\n";
        // if last key bind
        if (i.first == keyBinds.rbegin()->first) {
            ofs << "\t\t}\n";
        } else {
            ofs << "\t\t},\n";
        }
    }
    ofs << "\t]\n";
    ofs << "}";
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
    // save to json file
    ofs << "{\n";
    ofs << "\t\"game_data\": {\n";
    // save bool flag about is game has be started
    ofs << "\t\t\"is_game_started\": " << data.game_started << "\n";
    ofs << "\t}\n";
    ofs << "}\n";
    // close file
    ofs.close();
    return true;
}
