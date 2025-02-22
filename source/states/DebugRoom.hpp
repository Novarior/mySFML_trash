#ifndef BAFCF8A7_603F_486B_8F6A_5642448E8AB4
#define BAFCF8A7_603F_486B_8F6A_5642448E8AB4
#include "State.hpp"

#include "../Content/ItemsStuff/Inventory.hpp"
#include "../Content/Map/TileMap.hpp"
#include "../GUI/GUISYS.hpp"
#include "../core/header.h"
#include "../entitys/Enemys/slime.hpp"
#include "../entitys/player.hpp"
#include "../math/LSystem.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"
#include "State.hpp"
#include "editModes/NoiceViewer.hpp"
#include <memory>

// кастомный стэйт для отображения всего и всех в качестве отладки и проверки
// тут будет собрано максимально все говнецо которое только можно собрать и тп

class DebugRoomStaet : public State {
private:
  // variabless for DRS
  sf::View mView;
  bool ed_showTabmenu; // Flag to show or hide the tab menu

  void init_DRS();
  void init_View();

  // PROCCES DATA DEBUG
  //  View and window variables

  sf::View p_playerView;
  std::unique_ptr<PauseMenu> p_pausemenu;
  sf::Sprite p_renderSprite;
  sf::RenderTexture p_renderTexture;

  // Game elements
  std::shared_ptr<Inventory> p_inventory; // Inventory
  // std::unique_ptr<InventoryHUD> t_inventoryHUD; // Inventory HUD
  std::shared_ptr<Player> p_player;               // Player
  std::shared_ptr<TileMap> p_mapTiles;            // Tile map
  mmath::noiceData p_noicedata;                   // Noise data
  std::vector<std::shared_ptr<Entity>> p_entitys; // Entities
  std::unique_ptr<ProcessGenerationNoice> p_myGN; // Noise generation

  void init_pPlayerView();
  void init_pPausemenu();
  void init_pRenderSprite();
  void init_pRenderTexture();
  void init_pInventory();
  void init_pPlayer();
  void init_pMapTiles();
  void init_pNoicedata();
  void init_pEntitys();
  void init_pMyGN();

  /// EDITOR DATA DEBUG
  std::unique_ptr<NoiceViewer> ed_m_NoiceViewer; // Noise viewer
  std::unique_ptr<LSystem> ed_myLS; // L-system for generating trees
  std::map<std::string, std::unique_ptr<gui::Button>>
      ed_buttons;                 // Map of buttons
  sf::RectangleShape ed_tabShape; // Shape of the tab
  std::map<std::string, std::unique_ptr<gui::StaticSelector>>
      ed_staticSelector;                      // Map of static selectors
  std::unique_ptr<gui::Selector> ed_selector; // Current selector

  void init_edNoiceViewer();
  void init_edMYLS();
  void init_edButtons();
  void init_edTabShape();
  void init_edStaticSelector();
  void init_edSelector();

public:
  DebugRoomStaet(StateData *_data);
  ~DebugRoomStaet();

  // update sounds (virtual function)
  virtual void updateSounds(const float &delta_time) = 0;
  // Update mouse positions (virtual function)
  virtual void updateMousePositions(sf::View *view = NULL);
  // Update key time (virtual function)
  virtual void updateKeytime(const float &delta_time);
  // Update input (pure virtual function)
  virtual void updateInput(const float &delta_time) = 0;
  // Update the state (pure virtual function)
  virtual void update(const float &delta_time) = 0;
  // Render the state (pure virtual function)
  virtual void render(sf::RenderWindow &target) = 0;
};
#endif /* BAFCF8A7_603F_486B_8F6A_5642448E8AB4 */
