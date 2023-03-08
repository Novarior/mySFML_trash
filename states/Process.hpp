#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "State.hpp"
#include "../header.h"

#include "../GUI/GUISYS.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"
#include "../GUI/tabMenu.hpp"
#include "../entitys/player.hpp"
#include "../Content/Map/TileMap.hpp"

struct Gamedata
{
    unsigned seed;
    sf::Vector2f currentPlayerPos;

};

class Process:public State
{
    private:
    bool loaded;
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


    //init data who dont use loaded dates
    void initKeybinds();
    void initPauseMenu();
    void initTabMenu();
    void initView();
    void initTileMap();
    void initTileMapData();
    void initPlayer();

    const bool loadGameData();
    const bool saveGameData();

    public:
    Process(StateData* state_data, const bool defaultLoad);
    virtual ~Process();


    void updateInput(const float& deltatime);
    void updateButtons();
    void updatePlayerInputs(const float& deltatime);
    void update(const float& deltatime);
    void render(sf::RenderWindow* target);
};
#endif