#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "State.hpp"
#include "../header.h"

#include "../GUI/GUISYS.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"
#include "../entitys/player.hpp"
#include "../entitys/Enemys/slime.hpp"
#include "../Content/Map/TileMap.hpp"
#include "../Content/ItemsStuff/Inventory.hpp"

struct Gamedata
{
    unsigned seed;
    sf::Vector2f currentPlayerPos;

};

class Process :public State
{
    private:
    bool loaded;
    sf::Clock gameClock;
    sf::View view;
    sf::View playerView;
    TileMap* mapTiles;

    noiceData noicedata;
    ProcessGenerationNoice* myGN;
    PauseMenu* pausemenu;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    Gamedata m_gamedata;
    Player* player;
    sf::Texture playerTextureSHIT;
    Inventory* t_inventory;

    std::vector<Entity*> entitys;

    //init data who dont use loaded dates
    void initKeybinds();
    void initPauseMenu();
    void initView();
    void initTileMap();
    void initTileMapData();
    void initPlayer();
    void initEntitys();

    const bool loadGameData();
    const bool saveGameData();

    public:
    Process(StateData* state_data, const bool defaultLoad);
    virtual ~Process();

    //update functions
    void updateTileMap(const float& delta_time);
    void updateEntitys(const float& delta_time);
    void updateInput(const float& delta_time);
    void updatePlayerInputs(const float& delta_time);
    void update(const float& delta_time);

    //render functions 
    void renderPlayer(sf::RenderTarget& target);
    void renderGUI(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderEntities(sf::RenderTarget& target);
    //main render function
    void render(sf::RenderWindow& target);
};
#endif