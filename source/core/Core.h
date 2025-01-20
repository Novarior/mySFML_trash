#ifndef CPP_COREPROGRAM_H
#define CPP_COREPROGRAM_H

#include "../states/MainMenu.hpp"
#include "../states/gfx.hpp"
#include "_cmakever.h"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "dataCollector/_man_Volume.hpp"
#include "systemFunctionUNIX.hpp"

class Core {
private:
    float deltaTime;
    sf::Clock deltaClock;

    std::shared_ptr<sf::RenderWindow> mWindow;
    StateData mStatedata;
    std::stack<State*> mState;
    GraphicsSettings gfxSettings;
    std::map<std::string, int> supportedKeys;

    // initilization functions
    void initDirectories();
    void initKeyBinds();
    void initVar();
    void initStateData();
    void initState();
    void initWindow();
    void initLocations();

public:
    Core();
    virtual ~Core();
    void run();

    void updateEventsWindow();
    void updateDeltaTime();
    void update();
    void render();
};

#endif