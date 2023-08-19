#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "../header.h"
#include "State.hpp"

#include "../Content/ItemsStuff/Inventory.hpp"
#include "../Content/Map/TileMap.hpp"
#include "../GUI/GUISYS.hpp"
#include "../entitys/Enemys/slime.hpp"
#include "../entitys/player.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"

struct Gamedata {
    unsigned seed;
    sf::Vector2f currentPlayerPos;
};

class Process : public State {
private:
    // flag for load data
    bool loaded;
    Gamedata m_gamedata;
    // view and window
    sf::View view;
    sf::View playerView;
    PauseMenu* pausemenu;
    sf::Sprite renderSprite;
    sf::RenderTexture renderTexture;
    // game elements
    Inventory* t_inventory;
    Player* player;
    TileMap* mapTiles;
    noiceData noicedata;
    std::vector<Entity*> entitys;
    ProcessGenerationNoice* myGN;
    sf::Shader shader;
    // GUI
    gui::ProgressBar* playerHPBar;

    // init data who dont use loaded dates
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

    // update functions
    void updateTileMap(const float& delta_time);
    void updateEntitys(const float& delta_time);
    void updateInput(const float& delta_time);
    void updatePlayerInputs(const float& delta_time);
    void update(const float& delta_time);

    // render functions
    void renderPlayer(sf::RenderTarget& target);
    void renderGUI(sf::RenderTarget& target);
    void renderTileMap(sf::RenderTarget& target);
    void renderEntities(sf::RenderTarget& target);
    // main render function
    void render(sf::RenderWindow& target);
};
#endif