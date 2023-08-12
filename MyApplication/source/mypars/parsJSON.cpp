#include "parsJSON.hpp"
using namespace mypars;

parsJSON::parsJSON() { }
parsJSON::~parsJSON() { }

const bool parsJSON::loadKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds)
{
    // load key binds from json file
    std::ifstream ifs(filename);
    std::string line;
    std::string name = "";
    int value = 0;
    // check open file
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::JSON::KEYBINDS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
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

const bool parsJSON::saveKeyBinds(const std::string& filename, std::map<std::string, int>& keyBinds)
{
    // save key binds to json file on json format key : value
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::JSON::KEYBINDS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
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

// load functions from json file
const bool parsJSON::loadPlayer(const std::string& filename, Player& player)
{
    // open json file
    std::ifstream ifs;
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::JSON::PLAYER::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // load from json file

    return true;
}

const bool parsJSON::loadInventory(const std::string& filename, Inventory& inventory)
{
    // open json file
    std::ifstream ifs;
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::JSON::INVENTORY::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    return true;
}

// save player to json file
const bool parsJSON::savePlayer(const std::string& filename, Player* player)
{
    // open json file
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::JSON::PLAYER::FILE_NOT_OPEN\n   %s\n", filename.c_str());
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

// save inventory to json file
const bool parsJSON::saveInventory(const std::string& filename, Inventory* inventory)
{
    // save player inventory
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::JSON::INVENTORY::FILE_NOT_OPEN\n   %s\n", filename.c_str());
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
        if (inventory->getItemFromNumSlot(i) == nullptr) {
            // write "slot i is empty
            ofs << "\t\t\t\t\"slot\": " << i << ",\n";
            continue;
        }
        ofs << "\t\t\t\t\"name\": \"" << inventory->getItemFromNumSlot(i)->getName() << "\",\n";
        ofs << "\t\t\t\t\"count\": " << inventory->getItemFromNumSlot(i)->getQuantity() << ",\n";
        ofs << "\t\t\t\t\"price\": " << inventory->getItemFromNumSlot(i)->getPrice() << ",\n";
        ofs << "\t\t\t\t\"stackable\": " << inventory->getItemFromNumSlot(i)->getStackable() << ",\n";
        ofs << "\t\t\t\t\"unic ID\": " << inventory->getItemFromNumSlot(i)->getID() << "\n";
        ofs << "\t\t\t}";
        if (i != inventory->getSizeInventory() - 1) {
            ofs << ",";
        }
        ofs << "\n";
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

// save Entitys to json file
const bool parsJSON::saveEntitys(const std::string& filename, std::vector<Entity*> entitys)
{
    // open json file
    std::ofstream ofs(filename);
    // check open file
    if (!ofs.is_open()) {
        printf("ERROR::PARSER::JSON::ENTITYS::FILE_NOT_OPEN\n   %s\n", filename.c_str());
        return false;
    }
    // chek entetys for null

    // save to json file
    ofs << "{\n";
    ofs << "\t\"entity list\": [\n";
    // save entitys
    for (size_t i = 0; i < entitys.size(); i++) {
        // check entity if null, is null continue
        if (entitys[i] == nullptr) {
            continue;
        }
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