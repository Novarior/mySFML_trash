#include "gfx.hpp"

GraphicsSettings::GraphicsSettings()
{
    this->title = "DEFAULT";
    this->verticalSync = false;
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->frameRateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
    this->gridSize = 16.f;
}

// Functions
const bool GraphicsSettings::saveToFile(const std::string path)
{
    // open json file
    std::ofstream ofs(path);
    // check if file is open
    if (!ofs.is_open()) {
        printf("ERROR::GRAPHICSSETTINGS::COULD NOT SAVE TO FILE: %s\n", path.c_str());
        return false;
    }
    // save to json file
    ofs << "{\n";
    ofs << "\t\"title\""
        << ": "
        << "\"" << this->title << "\""
        << ",\n";
    ofs << "\t\"resolution\": "
        << "{\n";
    ofs << "\t\t\"width\": "
        << "\"" << this->resolution.width << "\""
        << ",\n";
    ofs << "\t\t\"height\": "
        << "\"" << this->resolution.height << "\""
        << "\n";
    ofs << "\t},\n";
    ofs << "\t\"fullscreen\""
        << ": "
        << "\"" << this->fullscreen << "\""
        << ",\n";
    ofs << "\t\"frameRateLimit\""
        << ": "
        << "\"" << this->frameRateLimit << "\""
        << ",\n";
    ofs << "\t\"verticalSync\""
        << ": "
        << "\"" << this->verticalSync << "\""
        << ",\n";
    ofs << "\t\"antialiasingLevel\""
        << ": "
        << "\"" << this->contextSettings.antialiasingLevel << "\""
        << ",\n";
    ofs << "\t\"gridSize\""
        << ": "
        << "\"" << this->gridSize << "\""
        << "\n";
    ofs << "}";
    // close json file
    ofs.close();
    return true;
}

const bool GraphicsSettings::loadFromFile(const std::string path)
{
    // load json file
    std::ifstream ifs(path);
    std::string line;
    // chek if file is open
    if (!ifs.is_open()) {
        printf("ERROR::GRAPHICSSETTINGS::COULD NOT LOAD TO FILE: %s\n", path.c_str());
        return false;
    }
    // load from json file
    while (std::getline(ifs, line)) {
        if (line == "{")
            continue;
        if (line == "}")
            continue;
        else if (line.find("\"title\":") != std::string::npos)
            this->title = line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4);
        else if (line.find("\"resolution\":") != std::string::npos) {
            std::getline(ifs, line);
            this->resolution.width = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
            std::getline(ifs, line);
            this->resolution.height = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
        } else if (line.find("\"fullscreen\":") != std::string::npos)
            this->fullscreen = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
        else if (line.find("\"frameRateLimit\":") != std::string::npos)
            this->frameRateLimit = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
        else if (line.find("\"verticalSync\":") != std::string::npos)
            this->verticalSync = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
        else if (line.find("\"antialiasingLevel\":") != std::string::npos)
            this->contextSettings.antialiasingLevel = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
        else if (line.find("\"gridSize\":") != std::string::npos)
            this->gridSize = std::stoi(line.substr(line.find(":") + 3, line.find(",") - line.find(":") - 4));
    }
    // close json file
    ifs.close();
    return true;
}