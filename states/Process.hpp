#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "State.hpp"
#include "../header.h"
#include "../math/mymath.hpp"
#include "../GUI/GUISYS.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"
#include "../GUI/tabMenu.hpp"
#include "../entitys/player.hpp"
#include "../Content/Map/TileMap.hpp"

struct Gamedata
{
    float timeInitElapsed;
};

class Process:public State
{
    private:
    sf::Clock gameClock;
    sf::View view;
    sf::View playerView;
    TileMap* mapTiles;
    gui::TabMenu* tabmenu;
    noiceData noicedata;
    ProcessGenerationNoice* myGN;
    PauseMenu* pausemenu;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    Gamedata m_gamedata;
    Player* player;

    void initView();
    void initKeybinds();
    void initTileMap();
    void initTabMenu();
    void initPlayer();
    void initPauseMenu();
    void rebuildNoice();
    void loadGameData();
    void saveGameData();

    public:
    Process(StateData* state_data);
    virtual ~Process();


    void updateInput(const float& deltatime);
    void updateButtons();
    void updatePlayerInputs(const float& deltatime);
    void update(const float& deltatime);
    void render(sf::RenderWindow* target);
};
#endif