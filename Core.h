#ifndef CPP_COREPROGRAM_H
#define CPP_COREPROGRAM_H

#include "states/MainMenu.hpp"
#include "states/gfx.hpp"
class Core
{
private:
    float deltaTime;
    sf::Clock deltaClock;
    void createWindow();

    sf::RenderWindow* mWindow;
    StateData mStatedata;
    std::stack<State*> mState;
    GraphicsSettings gfxSettings;
    sf::Event mEvents;
    std::map<std::string, int> supportedKeys;

    //inits
    void initKeyBinds();
    void initVar();
    void initStateData();
    void initState();

    void initWindow();

public:
    Core();
    virtual ~Core();

    const bool run();
    void updateEventsWindow();
    void updateDeltaTime();
    void update();
    void render();

};

#endif