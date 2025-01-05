#include "parsJSON.hpp"

// load playes
const bool ParserJson::loadPlayer(Entity& player)
{ // open json file
    std::ifstream ifs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_playerdata);
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::PLAYER::FILE_NOT_OPEN\n   %s\n", myConst::config::config_playerdata);
        return false;
    }
    // load from json file

    return true;
}

// load inventory
const bool ParserJson::loadInventory(const std::shared_ptr<Inventory>& inventory)
{
    // Проверка, что указатель на инвентарь не пустой
    if (!inventory) {
        printf("ERROR::PARSER::LOAD::INVENTORY::INVENTORY_IS_NULL\n");
        return false;
    }

    // Открытие файла
    std::ifstream ifs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_inventory);

    // Проверка, что файл открылся
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::LOAD::INVENTORY::FILE_NOT_OPEN\n   %s\n", myConst::config::config_inventory);
        return false;
    }

    // Парсим JSON из файла
    try {
        json j;
        if (!(ifs >> j)) {
            throw std::runtime_error("Failed to parse JSON from file.");
        }

        // Проверка наличия ключа "inventory" и "items"
        if (!j.contains("inventory") || !j["inventory"].contains("items")) {
            throw std::runtime_error("Missing 'inventory' or 'items' in JSON.");
        }

        // Загружаем предметы
        for (auto& item : j["inventory"]["items"]) {
            if (!item["slot"].is_null()) { // Проверяем на null
                // Получаем предмет по ID
                Item* newItem = static_cast<Item*>(ItemRegistry::getItem(item["unic ID"]));

                // Проверка, что предмет найден
                if (!newItem) {
                    printf("ERROR::PARSER::LOAD::ITEM_NOT_FOUND::ID=%d\n", item["unic ID"].get<int>());
                    continue; // Пропускаем этот предмет
                }

                // Добавляем предмет в инвентарь
                if (!inventory->addItem(std::shared_ptr<Item>(newItem))) {
                    printf("ERROR::PARSER::LOAD::ITEM_ADD_FAILED::ID=%d\n", item["unic ID"].get<int>());
                }
            }
        }

        // Проверка наличия ключа "coins"
        if (!j["inventory"].contains("coins")) {
            throw std::runtime_error("Missing 'coins' in JSON.");
        }

        // Загружаем монеты
        if (j["inventory"]["coins"].contains("gold")) {
            inventory->getCoins().set_GoldCoinCouns(j["inventory"]["coins"]["gold"].get<int>());
        }

        if (j["inventory"]["coins"].contains("silver")) {
            inventory->getCoins().set_SilverCoinCouns(j["inventory"]["coins"]["silver"].get<int>());
        }

        if (j["inventory"]["coins"].contains("copper")) {
            inventory->getCoins().set_CopperCoinCouns(j["inventory"]["coins"]["copper"].get<int>());
        }

    } catch (const std::exception& e) {
        Logger::logStatic("Cant load inventory: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
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
const bool ParserJson::loadKeyBinds(std::map<std::string, int>& keyBinds)
{ // load key binds from json file

    std::ifstream ifs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_window);
    if (!ifs.is_open()) {
        printf("PARSER cant open file: %s\n", std::string(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_window).c_str());
        Logger::logStatic("Parcer cant open file: " + ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_window, "CORE->PARS", logType::ERROR);
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
        Logger::logStatic("JSON parse error: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        return false;
    }

    ifs.close();
    return true;
}
const bool ParserJson::loadNoiceData(mmath::noiceData& data)
{ // load noice data
    // Open the file
    std::ifstream ifs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_noicedata);

    // Check if the file is open
    if (!ifs.is_open()) {
        printf("ERROR::PARSER::OPEN::NOICEDATA::FILE_NOT_OPEN\n   %s\n", myConst::config::config_playerdata);
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

const bool ParserJson::loadSoundVolumes(VolumeManager* data)
{ // loading volumes from window config file in vol
    try {
        json j;
        // Open the file and load the JSON object from it
        std::ifstream ifs(ApplicationsFunctions::getDocumentsAppFolder() + myConst::config::config_window);
        ifs >> j;

        // Create a temporary VolumeManager object
        VolumeManager tempData;

        // Load the sound volumes into the temporary object
        int categoryIndex = 0;
        for (json::iterator it = j["sound_volumes"].begin(); it != j["sound_volumes"].end(); ++it) {
            tempData.setCategoryVolume(static_cast<SoundCategory>(categoryIndex), it.value());
            categoryIndex++;
        }

        // Assign the temporary object to your main data object
        *data = tempData;
    } catch (const std::exception& e) {
        // catch exception
        Logger::logStatic("Cant load sound volumes: " + std::string(e.what()), "CORE->PARS", logType::ERROR);
        return false;
    }
    return true;
}
