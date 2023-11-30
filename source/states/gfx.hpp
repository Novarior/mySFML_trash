#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H
#include "../header.h"

class GraphicsSettings {
public:
    GraphicsSettings();

    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    float gridSize;

    // Functions
    const bool saveToFile(const std::string path);
    const bool loadFromFile(const std::string path);
};

#endif