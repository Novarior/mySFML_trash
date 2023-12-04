#include "gfx.hpp"

GraphicsSettings::GraphicsSettings()
{
    this->title = "Ekzeckt";
    this->verticalSync = false;
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->frameRateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
    this->gridSize = 16.f;
}

// save to file
const bool GraphicsSettings::saveToFile(const std::string directoryPath)
{
    // Создаем объект JSON
    json j;

    // Заполняем объект данными
    j["title"] = this->title;
    j["resolution"]["width"] = this->resolution.width;
    j["resolution"]["height"] = this->resolution.height;
    j["fullscreen"] = this->fullscreen;
    j["frameRateLimit"] = this->frameRateLimit;
    j["verticalSync"] = this->verticalSync;
    j["antialiasingLevel"] = this->contextSettings.antialiasingLevel;
    j["gridSize"] = this->gridSize;

    // Создаем путь к файлу
    std::string filePath = directoryPath + "/config.json";

    // Открываем файл для записи
    std::ofstream ofs(filePath);

    // Проверяем, открылся ли файл
    if (!ofs.is_open()) {
        std::cerr << "ERROR::GRAPHICSSETTINGS::COULD NOT SAVE TO FILE: " << filePath << std::endl;
        return false;
    }

    // Записываем JSON в файл
    ofs << j;

    // Закрываем файл
    ofs.close();

    return true;
}

// load from file
const bool GraphicsSettings::loadFromFile(const std::string directoryPath)
{
    // Создаем путь к файлу
    std::string filePath = directoryPath + "/config.json";

    // Открываем файл для чтения
    std::ifstream ifs(filePath);

    // Проверяем, открылся ли файл
    if (!ifs.is_open()) {
        std::cerr << "ERROR::GRAPHICSSETTINGS::COULD NOT LOAD TO FILE: " << filePath << std::endl;
        return false;
    }

    // Создаем объект JSON
    nlohmann::json j;

    // Читаем JSON из файла
    ifs >> j;

    // Закрываем файл
    ifs.close();

    // Заполняем данные из JSON
    this->title = j["title"];
    this->resolution.width = j["resolution"]["width"];
    this->resolution.height = j["resolution"]["height"];
    this->fullscreen = j["fullscreen"];
    this->frameRateLimit = j["frameRateLimit"];
    this->verticalSync = j["verticalSync"];
    this->contextSettings.antialiasingLevel = j["antialiasingLevel"];
    this->gridSize = j["gridSize"];

    return true;
}