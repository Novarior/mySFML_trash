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

    return false;
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
const bool parsJSON::loadNoiceData(const std::string& filename, mmath::noiceData& data)
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
    //  this->m_js.clear();
    json js = json::parse(ifs);
    js.at("game_data").at("is_game_started").get_to(data.game_started);

    return true;
}
// SAVES
// save player
const bool parsJSON::savePlayer(const std::string& filename, Entity* player)
{
    return false;
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

    std::vector<std::vector<Item*>> iArr = inventory->getInventoryArray();
    this->m_js.clear();
    this->m_js["inventory"];
    this->m_js["inventory"]["size"] = inventory->getSizeInventory();
    this->m_js["inventory"]["items"];
    int slot = 0;
    // save items
    for (auto& row : iArr) {
        for (auto& item : row) {
            // check item if null
            if (item != nullptr) { // write "slot if is not empty
                this->m_js["inventory"]["items"][slot]["slot"] = inventory->getNumSlot(item);
                this->m_js["inventory"]["items"][slot]["name"] = item->getName();
                this->m_js["inventory"]["items"][slot]["amount"] = item->getAmount();
                this->m_js["inventory"]["items"][slot]["price"];
                this->m_js["inventory"]["items"][slot]["price"]["Gold"] = item->getPrice().get_GoldCointCount();
                this->m_js["inventory"]["items"][slot]["price"]["Silver"] = item->getPrice().get_SilverCointCount();
                this->m_js["inventory"]["items"][slot]["price"]["Copper"] = item->getPrice().get_CopperCointCount();
                this->m_js["inventory"]["items"][slot]["stackable"] = item->isStackable();
                this->m_js["inventory"]["items"][slot]["usable"] = item->isUsable();
                this->m_js["inventory"]["items"][slot]["unic ID"] = item->getID();
            } else {
                // write "slot" if is empty
                this->m_js["inventory"]["items"][slot]["slot"] = nullptr;
                this->m_js["inventory"]["items"][slot]["name"] = nullptr;
                this->m_js["inventory"]["items"][slot]["amount"] = nullptr;
                this->m_js["inventory"]["items"][slot]["price"] = nullptr;
                this->m_js["inventory"]["items"][slot]["stackable"] = nullptr;
                this->m_js["inventory"]["items"][slot]["usable"] = nullptr;
                this->m_js["inventory"]["items"][slot]["unic ID"] = nullptr;
            }
            slot++;
        }
    }

    this->m_js["inventory"]["coins"];
    this->m_js["inventory"]["coins"]["gold"] = inventory->getCoins().get_GoldCointCount();
    this->m_js["inventory"]["coins"]["silver"] = inventory->getCoins().get_SilverCointCount();
    this->m_js["inventory"]["coins"]["copper"] = inventory->getCoins().get_CopperCointCount();
    // save to json file
    ofs << std::setw(4) << this->m_js;
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
    this->m_js.clear();
    this->m_js["entity list"];
    // save entitys
    for (size_t i = 0; i < entitys.size(); i++) {
        // check entity if null, is null continue
        if (entitys[i] == nullptr || entitys[i]->e_isAlive() == false)
            continue;

        this->m_js["entity list"][i];
        this->m_js["entity list"][i]["ID_record"] = i;
        this->m_js["entity list"][i]["entity_uid"] = entitys[i]->e_getID();
        this->m_js["entity list"][i]["position"]["x"] = entitys[i]->e_getPosition().x;
        this->m_js["entity list"][i]["position"]["y"] = entitys[i]->e_getPosition().y;
        // save entity attributes
        this->m_js["entity list"][i]["attributes"];
        this->m_js["entity list"][i]["attributes"]["hp"] = entitys[i]->getAttributes()->getAttributes().health;
        this->m_js["entity list"][i]["attributes"]["max_hp"] = entitys[i]->getAttributes()->getAttributes().max_health;
        this->m_js["entity list"][i]["attributes"]["level"] = entitys[i]->getAttributes()->getAttributes().level;
    }
    // save to json file
    ofs << std::setw(4) << this->m_js;
    // close file
    ofs.close();
    return true;
}
// save noicedata
const bool parsJSON::saveNoiceData(const std::string& filename, mmath::noiceData _dataNoice)
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

    this->m_js["key_binds"];
    // save key binds
    for (auto& i : keyBinds) {
        this->m_js["key_binds"][i.first] = i.second;
    }
    // save to json file
    ofs << std::setw(4) << this->m_js;
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

    // save to json file
    this->m_js["game_data"];
    this->m_js["game_data"]["is_game_started"] = data.game_started;
    // save to json file
    ofs << std::setw(4) << this->m_js;
    // close file
    ofs.close();
    return true;
}
