#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "../header.h"
#include "State.hpp"

#include "../Content/ItemsStuff/Inventory.hpp"
#include "../Content/ItemsStuff/Items/itemlist.hpp"
#include "../Content/Map/TileMap.hpp"
#include "../GUI/GUISYS.hpp"
#include "../entitys/Enemys/slime.hpp"
#include "../entitys/player.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"

class Process : public State {
private:
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
    mmath::noiceData noicedata;
    std::vector<Entity*> entitys;
    ProcessGenerationNoice* myGN;
    sf::Shader shader;
    // GUI
    std::map<std::string, gui::ProgressBar*> playerBar;
    gui::MiniMap* minimap;

    // init data who dont use loaded dates
    void initKeybinds();
    void initPauseMenu();
    void initView();
    void initTileMap();
    void initTileMapData();
    void registerItems();
    void initPlayer();
    void initEntitys();
    void initMiniMap();

    void intGUI();

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
    void updateGUI(const float& delta_time);
    void updateDebug(const float& delta_time);
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