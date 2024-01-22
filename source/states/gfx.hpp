#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
#include "../header.h"

struct myGFXStruct {
    // Variables
    std::string title;
    sf::VideoMode resolution;
    sf::Vector2u _winResolutions;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    float gridSize;

    // sound variables
    float _sound_master_vol;
    float _sound_music_vol;
    float _sound_sfx_vol;
    float _sound_player_vol;
};

class GraphicsSettings {
public:
    myGFXStruct _struct;

    GraphicsSettings()
    {
        _struct.title = myConst::app_name;
        _struct.verticalSync = false;
        _struct.resolution = sf::VideoMode::getDesktopMode();
        _struct.videoModes = sf::VideoMode::getFullscreenModes();
        _struct.fullscreen = true;
        _struct.frameRateLimit = 120;
        _struct.contextSettings.antialiasingLevel = 0;
        _struct.gridSize = 16.f;
        _struct._sound_master_vol = 50.f;
        _struct._sound_music_vol = 50.f;
        _struct._sound_sfx_vol = 50.f;
        _struct._sound_player_vol = 50.f;
    }

    void setgfxsettings(const myGFXStruct gfx) { _struct = gfx; }
    const myGFXStruct getgfxsettings() { return _struct; }

    // save to file
    const bool
    saveToFile(const std::string directoryPath)
    {
        // Создаем объект JSON
        json j;

        // Заполняем объект данными
        j["resolution"]["width"] = _struct.resolution.width;
        j["resolution"]["height"] = _struct.resolution.height;
        j["fullscreen"] = _struct.fullscreen;
        j["frameRateLimit"] = _struct.frameRateLimit;
        j["verticalSync"] = _struct.verticalSync;
        j["antialiasingLevel"] = _struct.contextSettings.antialiasingLevel;
        j["gridSize"] = _struct.gridSize;

        // Создаем путь к файлу
        std::string filePath = directoryPath + "/Config/config.json";

        // Открываем файл для записи
        std::ofstream ofs(filePath);

        // Проверяем, открылся ли файл
        if (!ofs.is_open()) {
            Logger::log("GFX::COULD NOT SAVE TO FILE: " + filePath, "GFX()", logType::ERROR);
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
        _struct.resolution.width = j["resolution"]["width"];
        _struct.resolution.height = j["resolution"]["height"];
        _struct.fullscreen = j["fullscreen"];
        _struct.frameRateLimit = j["frameRateLimit"];
        _struct.verticalSync = j["verticalSync"];
        _struct.contextSettings.antialiasingLevel = j["antialiasingLevel"];
        _struct.gridSize = j["gridSize"];

        return true;
    }
};

#endif