#include "parsJSON.hpp"

// SAVES
const bool ParserJson::savePlayer(Entity* player)
{ // save player
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
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_playerdata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save player: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::PLAYER::FILE_NOT_OPEN\n   %s\n", myConst::config::config_playerdata);
        return false;
    }

    return true;
}
const bool ParserJson::saveInventory(Inventory* inventory)
{ // save inventory
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
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_inventory);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save inventory: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::INVENTORY::FILE_NOT_OPEN\n   %s\n", myConst::config::config_inventory);
    }
    return true;
}
const bool ParserJson::saveEntitys(std::vector<Entity*> entitys)
{ // save entitys
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
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_entitydata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Pars can't save entities" << ApplicationsFunctions::getDocumentsAppFolder() << myConst::config::config_entitydata;
        Logger::log(ss.str(), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::ENTITYS::FILE_NOT_OPEN\n   %s\n", myConst::config::config_entitydata);
        return false;
    }

    return true;
}
const bool ParserJson::saveNoiceData(mmath::noiceData _dataNoice)
{ // save noicedata
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
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_noicedata);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        Logger::log("Cant save noice data: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n", myConst::config::config_noicedata);
        return false;
    }

    return true;
}
const bool ParserJson::saveKeyBinds(std::map<std::string, int>& keyBinds)
{ // save keybinds
    // Create a JSON object
    json j;
    for (const auto& i : keyBinds) {
        j["key_binds"][i.first] = i.second;
    }

    // Write the JSON object to the file
    try {
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_keybinds);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        std::stringstream ss;
        ss << "Pars can't save keybinds" << ApplicationsFunctions::getDocumentsAppFolder() << myConst::config::config_keybinds;
        Logger::log(ss.str(), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::KEYBINDS::FILE_NOT_OPEN\n   %s\n", myConst::config::config_keybinds);
        return false;
    }

    return true;
}

const bool ParserJson::saveSoundVolumes(VolumeManager* data)
{ // save sound volumes from VolumeManager class
    // Write the JSON object to the file
    try {
        json j;
        // Save the sound volumes to the JSON object
        for (const auto& category : data->getCategoryVolumes()) {
            j["sound_volumes"][static_cast<int>(category.first)] = category.second;
        }
        // Write the JSON object to the file
        std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_soundvolume);
        ofs << std::setw(4) << j;
    } catch (const std::exception& e) {
        // catch exception
        Logger::log("Cant save sound volumes: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        printf("ERROR::PARSER::SAVE::SOUNDVOLUMES::FILE_NOT_OPEN\n   %s\n", myConst::config::config_soundvolume);
        return false;
    }

    return true;
}
