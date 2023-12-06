#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
#include "../header.h"

class GraphicsSettings {
public:
    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    float gridSize;

    GraphicsSettings()
    {
        this->title = myConst::app_name;
        this->verticalSync = false;
        this->resolution = sf::VideoMode::getDesktopMode();
        this->fullscreen = false;
        this->frameRateLimit = 120;
        this->contextSettings.antialiasingLevel = 0;
        this->videoModes = sf::VideoMode::getFullscreenModes();
        this->gridSize = 16.f;
    }

    // save to file
    const bool saveToFile(const std::string directoryPath)
    {
        // Создаем объект JSON
        json j;

        // Заполняем объект данными
        j["resolution"]["width"] = this->resolution.width;
        j["resolution"]["height"] = this->resolution.height;
        j["fullscreen"] = this->fullscreen;
        j["frameRateLimit"] = this->frameRateLimit;
        j["verticalSync"] = this->verticalSync;
        j["antialiasingLevel"] = this->contextSettings.antialiasingLevel;
        j["gridSize"] = this->gridSize;

        // Создаем путь к файлу
        std::string filePath = directoryPath + "/Config/config.json";

        // Открываем файл для записи
        std::ofstream ofs(filePath);

        // Проверяем, открылся ли файл
        if (!ofs.is_open()) {
            Logger::log("GFX::COULD NOT SAVE TO FILE: " + filePath, "GFX()", false, logType::ERROR);
            return false;
        }

        // Записываем JSON в файл
        ofs << j.dump(4) << std::endl;

        // Закрываем файл
        ofs.close();

        return true;
    }

    // load from file
    const bool loadFromFile(const std::string directoryPath)
    {
        // Создаем путь к файлу
        std::string filePath = directoryPath + "/Config/config.json";

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
        this->resolution.width = j["resolution"]["width"];
        this->resolution.height = j["resolution"]["height"];
        this->fullscreen = j["fullscreen"];
        this->frameRateLimit = j["frameRateLimit"];
        this->verticalSync = j["verticalSync"];
        this->contextSettings.antialiasingLevel = j["antialiasingLevel"];
        this->gridSize = j["gridSize"];

        return true;
    }
};

#endif