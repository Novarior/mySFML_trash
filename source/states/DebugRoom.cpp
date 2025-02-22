#include "DebugRoom.hpp"

// init DRS
void DebugRoomStaet ::init_DRS() {
  // init DebugRoomStaet for view all posible item on app
  this->init_View();
}
void DebugRoomStaet::init_View() {
  // init view with window size
  sf::Vector2f halfSize = sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2);

  this->mView.setSize(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x),
      static_cast<float>(this->IstateData->sd_Window->getSize().y)));
  this->mView.setCenter(halfSize);
}

// initialisation game data for nex debug...
void DebugRoomStaet::init_pPlayerView() {
  // set viewport like a  window size for next rendering
  sf::Vector2f halfSize = sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2);

  // multi haflSize * 2.f same like a zoom (or scale)
  this->p_playerView.setSize(halfSize * 2.f);
  this->p_playerView.setCenter(halfSize);
}
void DebugRoomStaet::init_pPausemenu() {
  // init "Pause Menu" monent
  //
  const sf::VideoMode &vm =
      this->IstateData->sd_gfxSettings->_struct.resolution;
  this->p_pausemenu = std::make_unique<PauseMenu>(
      this->IstateData->sd_gfxSettings->_struct.resolution,
      this->IstateData->sd_font);

  this->p_pausemenu->addButton("EXIT_BUTTON", mmath::p2pY(74.f, vm),
                               mmath::p2pX(13.f, vm), mmath::p2pY(6.f, vm),
                               mmath::calcCharSize(vm), "Quit");
  this->p_pausemenu->addButton("GEN", mmath::p2pX(20, vm),
                               mmath::p2pY(74.f, vm), mmath::p2pX(13.f, vm),
                               mmath::calcCharSize(vm), "Generate");
}
void DebugRoomStaet::init_pRenderSprite() {
  // init render sprite
  // using like a default strite (look on sf::Sprite)
  // but for rendering current frame
  // bing our texture for sprite
  this->p_renderSprite.setTexture(this->p_renderTexture.getTexture());
  // setup position and size
  this->p_renderSprite.setTextureRect(sf::IntRect(
      {0, 0}, sf::Vector2i(this->IstateData->sd_Window->getSize().x,
                           this->IstateData->sd_Window->getSize().y)));
}
void DebugRoomStaet::init_pRenderTexture() {
  // init texture for next render
  // texture have a win.size
  //  will be linked to the sprite in the next step
  this->p_renderTexture =
      sf::RenderTexture({this->IstateData->sd_Window->getSize().x,
                         this->IstateData->sd_Window->getSize().y});
}
void DebugRoomStaet::init_pInventory() {
  this->p_inventory = std::make_shared<Inventory>(
      sf::Vector2f(this->IstateData->sd_Window->getSize()), 10, 4,
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big);
}
void DebugRoomStaet::init_pPlayer() {
  this->p_player = std::make_shared<Player>(sf::Vector2f(0, 0));
}
void DebugRoomStaet::init_pMapTiles() {
  this->p_mapTiles =
      std::make_shared<TileMap>(this->p_noicedata, this->p_myGN.get());
}
void DebugRoomStaet::init_pNoicedata() {
  this->p_noicedata.seed = 0;
  this->p_noicedata.gridSize = this->IstateData->sd_gridSize;
  this->p_noicedata.octaves = 9;
  this->p_noicedata.frequency = 8;
  this->p_noicedata.persistence = 0.6f;
  this->p_noicedata.amplifire = 0.7f;
  this->p_noicedata.fastMode = 1;
  this->p_noicedata.smoothMode = 1;
  this->p_noicedata.RenderWindowX =
      this->IstateData->sd_gfxSettings->_struct.resolution.size.x;
  this->p_noicedata.RenderWindowY =
      this->IstateData->sd_gfxSettings->_struct.resolution.size.y;
  this->p_noicedata.mapSizeX = 128;
  this->p_noicedata.mapSizeY = 96;
  this->p_noicedata.smoothMode = 0;
}
void DebugRoomStaet::init_pEntitys() {
  this->p_entitys.push_back(
      std::make_shared<Slime>(30, 0, *this->p_player.get()));
}
void DebugRoomStaet::init_pMyGN() {
  this->p_myGN = std::make_unique<ProcessGenerationNoice>(this->p_noicedata);
}
// initialisation editor data for nex debug...
void DebugRoomStaet::init_edNoiceViewer() {
  // init data for noice viewer
  this->ed_m_NoiceViewer = std::make_unique<NoiceViewer>(this->p_noicedata);
  this->ed_m_NoiceViewer->generateNoice();
}
void DebugRoomStaet::init_edMYLS() {
  this->ed_myLS = std::make_unique<LSystem>();
  this->ed_myLS->setRule('d', "qd");
  this->ed_myLS->setRule('s', "d[[-qqs]qs]+qqs[+q|]-q|");
  this->ed_myLS->setOffsetPos(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2.0,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) * 0.90));
  this->ed_myLS->generate();
}
void DebugRoomStaet::init_edButtons() {
  this->ed_buttons["G_NOICE"] = std::make_unique<gui::Button>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(90, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x / 2,
                   mmath::p2pX(10, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, "Gen Noice",
      this->IstateData->sd_characterSize_game_big, sf::Color(200, 200, 200),
      sf::Color(180, 180, 180), sf::Color(160, 160, 180),
      sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
      sf::Color::Black, sf::Color::Black, sf::Color::Black);

  this->ed_buttons["G_TREE"] = std::make_unique<gui::Button>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x + this->ed_tabShape.getSize().x / 2,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(90, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x / 2,
                   mmath::p2pX(10, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, "Gen Tree",
      this->IstateData->sd_characterSize_game_big, sf::Color(200, 200, 200),
      sf::Color(180, 180, 180), sf::Color(160, 160, 180),
      sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
      sf::Color::Black, sf::Color::Black, sf::Color::Black);

  this->ed_buttons["SAVE_GENDATA"] = std::make_unique<gui::Button>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(80, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x / 2,
                   mmath::p2pX(10, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, "Save",
      this->IstateData->sd_characterSize_game_big, sf::Color(200, 200, 200),
      sf::Color(180, 180, 180), sf::Color(160, 160, 180),
      sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
      sf::Color::Black, sf::Color::Black, sf::Color::Black);

  this->ed_buttons["LOAD_GENDATA"] = std::make_unique<gui::Button>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x + this->ed_tabShape.getSize().x / 2,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(80, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x / 2,
                   mmath::p2pX(10, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, "Load",
      this->IstateData->sd_characterSize_game_big, sf::Color(200, 200, 200),
      sf::Color(180, 180, 180), sf::Color(160, 160, 180),
      sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
      sf::Color::Black, sf::Color::Black, sf::Color::Black);
}
void DebugRoomStaet::init_edTabShape() {
  this->ed_tabShape.setPosition(sf::Vector2f(
      mmath::p2pX(70, this->IstateData->sd_Window->getSize().x), 0));
  this->ed_tabShape.setSize(
      sf::Vector2f(mmath::p2pX(30, this->IstateData->sd_Window->getSize().x),
                   this->IstateData->sd_Window->getSize().y));
  // half transparent gray
  this->ed_tabShape.setFillColor(sf::Color(150, 150, 150, 200));
  this->ed_tabShape.setOutlineThickness(5.f);
  this->ed_tabShape.setOutlineColor(sf::Color(100, 100, 100, 192));
  this->ed_showTabmenu = false;
}
void DebugRoomStaet::init_edStaticSelector() {
  this->ed_staticSelector["OCTAVES"] = std::make_unique<gui::StaticSelector>(
      sf::Vector2f(this->ed_tabShape.getPosition()),
      sf::Vector2f(this->ed_tabShape.getSize().x,
                   mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big, 0,
      10, 1.f, true, "Octaves: ");

  this->ed_staticSelector["FREQUENCY"] = std::make_unique<gui::StaticSelector>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x,
                   mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big, 0,
      10, 0.1f, true, "Frequency: ");

  this->ed_staticSelector["PERSISTENCE"] =
      std::make_unique<gui::StaticSelector>(
          sf::Vector2f(
              this->ed_tabShape.getPosition().x,
              this->ed_tabShape.getPosition().y +
                  mmath::p2pX(14, this->IstateData->sd_Window->getSize().y)),
          sf::Vector2f(
              this->ed_tabShape.getSize().x,
              mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
          this->IstateData->sd_font,
          this->IstateData->sd_characterSize_game_big, 0, 5, 0.1f, true,
          "Persistence: ");

  this->ed_staticSelector["AMPLIFIRE"] = std::make_unique<gui::StaticSelector>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(21, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x,
                   mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big, 0,
      10, 0.1f, true, "Amplifire: ");

  // set default value for static selector
  this->ed_staticSelector["OCTAVES"]->setCurrentValue(
      this->ed_m_NoiceViewer->getNoiceData().octaves);
  this->ed_staticSelector["FREQUENCY"]->setCurrentValue(
      this->ed_m_NoiceViewer->getNoiceData().frequency);
  this->ed_staticSelector["AMPLIFIRE"]->setCurrentValue(
      this->ed_m_NoiceViewer->getNoiceData().amplifire);
  this->ed_staticSelector["PERSISTENCE"]->setCurrentValue(
      this->ed_m_NoiceViewer->getNoiceData().persistence);
}
void DebugRoomStaet::init_edSelector() {
  std::vector<std::string> list = {"Linear",  "Cosine",    "Cubic",  "Quintic",
                                   "Quartic", "Quadratic", "Hermite"};

  this->ed_selector = std::make_unique<gui::Selector>(
      sf::Vector2f(
          this->ed_tabShape.getPosition().x,
          this->ed_tabShape.getPosition().y +
              mmath::p2pX(28, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(this->ed_tabShape.getSize().x,
                   mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big,
      list.data(), list.size(), 0);
}

DebugRoomStaet::DebugRoomStaet(StateData *_data)
    : State(_data), p_renderSprite(TextureManager::getTexture("texture_null")) {
  // init DRS
  this->init_DRS();
  // init PGS
  this->init_pPlayerView();    // 1
  this->init_pRenderTexture(); // 2
  this->init_pRenderSprite();  // 3
  this->init_pPausemenu();     // 4
  this->init_pInventory();     // 5
  this->init_pNoicedata();     // 6
  this->init_pMyGN();          // 7
  this->init_pMapTiles();      // 8
  this->init_pPlayer();        // 9
  this->init_pEntitys();       // 10
  // init editor data
  this->init_edTabShape();       // 1
  this->init_edButtons();        // 2
  this->init_edSelector();       // 3
  this->init_edStaticSelector(); // 4
  this->init_edNoiceViewer();    // 6
  this->init_edMYLS();           // 5
}
DebugRoomStaet ::~DebugRoomStaet() {
  this->p_pausemenu.reset();
  this->p_inventory.reset();
  this->p_player.reset();
  this->p_mapTiles.reset();
  if (!this->p_entitys.empty())
    this->p_entitys.clear();
  this->p_myGN.reset();

  this->ed_m_NoiceViewer.reset();
  this->ed_myLS.reset();
  this->ed_selector.reset();
  if (!this->ed_buttons.empty())
    this->ed_buttons.clear();
  this->ed_staticSelector.clear();
}

void DebugRoomStaet::updateSounds(const float &delta_time) {}
void DebugRoomStaet::updateMousePositions(sf::View *view) {}
void DebugRoomStaet::updateKeytime(const float &delta_time) {}
void DebugRoomStaet::updateInput(const float &delta_time) {}
void DebugRoomStaet::update(const float &delta_time) {}
void DebugRoomStaet::render(sf::RenderWindow &target) {
  this->p_renderTexture.clear();
  this->p_renderTexture.setView(this->mView);
  // draw ect
  this->p_renderTexture.display();
  target.draw(this->p_renderSprite);
}
