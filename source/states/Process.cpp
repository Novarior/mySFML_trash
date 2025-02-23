#include "Process.hpp"

const bool Process::loadGameData() {
  // load noice config
  if (ParserJson::loadNoiceData(this->noicedata))
    printf("ERROR::PROCESS::LOAD::NOICEDATA::COULD_NOT_LOAD\n   %s\n",
           myConst::config::config_noicedata);
  else {
    this->noicedata.mapSizeX = 1000;
    this->noicedata.mapSizeY = 1000;
    this->noicedata.RenderWindowX =
        this->IstateData->sd_gfxSettings->_struct.resolution.size.x;
    this->noicedata.RenderWindowY =
        this->IstateData->sd_gfxSettings->_struct.resolution.size.y;
    this->noicedata.gridSize = this->IstateData->sd_gridSize;
  }
  return true;
}

const bool Process::saveGameData() {
  // save player to JSON file
  if (ParserJson::savePlayer(this->player.get()))
    Logger::logStatic("Parser::savePlayer()::ERROR::",
                      "Process::saveGameData()", logType::ERROR);
  // save inventory to JSON file
  if (ParserJson::saveInventory(t_inventory))
    Logger::logStatic("Parser::saveInventory()::ERROR::",
                      "Process::saveGameData()", logType::ERROR);
  // save entitys pos and other data
  if (ParserJson::saveEntitys(this->entitys))
    Logger::logStatic("Parser::saveEntitys()::ERROR::",
                      "Process::saveGameData()", logType::ERROR);

  return true;
}

// init data who dont use loaded dates
void Process::initKeybinds() {
  this->Ikeybinds["KEY_CLOSE"] = this->IsupportedKeys->at("Escape");
  this->Ikeybinds["KEY_TAB"] = this->IsupportedKeys->at("Tab");
  this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
  this->Ikeybinds["KEY_A"] = this->IsupportedKeys->at("A");
  this->Ikeybinds["KEY_D"] = this->IsupportedKeys->at("D");
  this->Ikeybinds["KEY_S"] = this->IsupportedKeys->at("S");
  this->Ikeybinds["KEY_W"] = this->IsupportedKeys->at("W");
  this->Ikeybinds["KEY_E"] = this->IsupportedKeys->at("E");
  this->Ikeybinds["KEY_Q"] = this->IsupportedKeys->at("Q");
  this->Ikeybinds["KEY_SPACE"] = this->IsupportedKeys->at("Space");
  // debug moment
  // std::cout<<"sizeof keybinds: "<<this->Ikeybinds.size()<<'\n';
}

void Process::initPauseMenu() {
  const sf::VideoMode &vm =
      this->IstateData->sd_gfxSettings->_struct.resolution;
  this->pausemenu =
      new PauseMenu(this->IstateData->sd_gfxSettings->_struct.resolution,
                    this->IstateData->sd_font);
  this->pausemenu->addButton("EXIT_BUTTON", mmath::p2pY(74.f, vm),
                             mmath::p2pX(13.f, vm), mmath::p2pY(6.f, vm),
                             mmath::calcCharSize(vm), "Quit");
  this->pausemenu->addButton("GEN", mmath::p2pX(20, vm), mmath::p2pY(74.f, vm),
                             mmath::p2pX(13.f, vm), mmath::calcCharSize(vm),
                             "Generate");
}

void Process::initTileMap() {
  this->myGN = new ProcessGenerationNoice(this->noicedata);
  this->mapTiles = std::make_shared<TileMap>(this->noicedata, myGN);
}

void Process::intGUI() // init GUI
{
  // init player HP bar on top right on screen math position using mmath::p2pX/X
  this->playerBar["HP_BAR"] = new gui::ProgressBar(
      sf::Vector2f(mmath::p2pX(75, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(3, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(mmath::p2pX(20, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(3, this->IstateData->sd_Window->getSize().y)),
      sf::Color::Red, this->IstateData->sd_characterSize_game_small,
      this->IstateData->sd_font);
  this->playerBar["MP_BAR"] = new gui::ProgressBar(
      sf::Vector2f(mmath::p2pX(75, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(7, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(mmath::p2pX(20, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(3, this->IstateData->sd_Window->getSize().y)),
      sf::Color::Blue, this->IstateData->sd_characterSize_game_small,
      this->IstateData->sd_font);

  this->initMiniMap();
}

void Process::initView() {
  sf::Vector2f halfSize = sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2.f,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2.f);

  this->view.setSize(halfSize);
  this->view.setCenter(halfSize);
  this->playerView.setSize(halfSize);
  this->playerView.setCenter(halfSize);

  if (!this->renderTexture.resize({this->IstateData->sd_Window->getSize().x,
                                   this->IstateData->sd_Window->getSize().y}))
    sf::RenderTexture _buffRenderTexture(
        {this->IstateData->sd_Window->getSize().x,
         this->IstateData->sd_Window->getSize().y});

  this->renderSprite.setTexture(this->renderTexture.getTexture());
  this->renderSprite.setTextureRect(sf::IntRect(
      {0, 0}, sf::Vector2i(this->IstateData->sd_Window->getSize().x,
                           this->IstateData->sd_Window->getSize().y)));
}

void Process::initPlayer() {
  // get array with posible spawn positions
  std::vector<sf::Vector2f> spawnPosArray = this->mapTiles->getSpawnPosArray();
  // set player position to random position getting from spawnPosArray
  this->player =
      std::make_shared<Player>(spawnPosArray[rand() % spawnPosArray.size()]);
  this->t_inventory = std::make_shared<Inventory>(
      sf::Vector2f(this->IstateData->sd_Window->getSize()), 10, 4,
      this->IstateData->sd_font, this->IstateData->sd_characterSize_game_big);

  std::shared_ptr<Item> stoneItem =
      std::make_shared<Items::Stone>(64); // 64 - это gridSizeI

  t_inventory->addItem(stoneItem);
  //  this->t_inventoryHUD = std::make_unique<InventoryHUD>(
  //     sf::Vector2f(this->IstateData->sd_Window->getSize()), 32.0f,
  //     this->IstateData->sd_font,
  //     this->IstateData->sd_characterSize_game_big);
}

void Process::initMiniMap() // init minimap
{
  sf::IntRect worldBounds({0, 0}, this->mapTiles->getMapSizeOnInt());

  this->minimap = new gui::MiniMap(
      sf::Vector2f(mmath::p2pX(75, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(10, this->IstateData->sd_Window->getSize().y)),
      sf::Vector2f(mmath::p2pX(20, this->IstateData->sd_Window->getSize().x),
                   mmath::p2pX(20, this->IstateData->sd_Window->getSize().y)),
      worldBounds);

  this->minimap->setImage(this->mapTiles->getMinimapImage());
}

// Defauld Init Data
void Process::initTileMapData() {
  this->noicedata.seed = std::time(0);
  this->noicedata.gridSize = this->IstateData->sd_gridSize;
  this->noicedata.octaves = 9;
  this->noicedata.frequency = 8;
  this->noicedata.persistence = 0.6f;
  this->noicedata.amplifire = 0.7f;
  this->noicedata.fastMode = 1;
  this->noicedata.smoothMode = 1;
  this->noicedata.RenderWindowX =
      this->IstateData->sd_gfxSettings->_struct.resolution.size.x;
  this->noicedata.RenderWindowY =
      this->IstateData->sd_gfxSettings->_struct.resolution.size.y;
  this->noicedata.mapSizeX = 620;
  this->noicedata.mapSizeY = 430;
}

void Process::initEntitys() {
  // get random position from map array
  std::vector<sf::Vector2f> spawnPosArray = this->mapTiles->getSpawnPosArray();

  for (size_t i = 0; i < 1; i++) {
    // call function to get random position
    this->entitys.push_back(new Slime(
        spawnPosArray[rand() % spawnPosArray.size()].x,
        spawnPosArray[rand() % spawnPosArray.size()].y, *this->player));
  }
}

void Process::registerItems() {
  int size = this->IstateData->sd_gridSize;

  // register items to registry
  ItemRegistry::registerItem(0, std::make_unique<Items::Stone>(size));
  ItemRegistry::registerItem(
      1, std::make_unique<Items::PoisonSmallRegeneration>(size));

  Logger::logStatic("Items has been registered", "Process::registerItems()");
  Logger::logStatic("Items count: " +
                        std::to_string(ItemRegistry::getAllItems().size()),
                    "Process::registerItems()");
}

Process::Process(StateData *state_data, const bool defaultLoad)
    : State(state_data),
      renderSprite(TextureManager::getTexture("texture_null"))

{ // init Parser
  if (defaultLoad)
    this->loadGameData();
  else
    this->initTileMapData();

  this->initKeybinds();
  this->initView();
  this->initPauseMenu();
  this->registerItems();
  this->initTileMap();
  this->initPlayer();
  this->initEntitys();
  this->intGUI();

  Logger::logStatic("End initilization process", "Process::Process()");
}

Process::~Process() {
  if (this->saveGameData())
    Logger::logStatic("Game Data has be saved",
                      "Process::~Process()::saveGameData()");
  else
    Logger::logStatic("Game Data has not be saved",
                      "Process::~Process()::saveGameData()", logType::ERROR);

  delete this->myGN;
  this->mapTiles.reset();
  delete this->pausemenu;
  this->player.reset();
  this->t_inventory.reset();
  delete this->minimap;

  // clear bar
  for (auto &it : this->playerBar)
    delete it.second;

  // clear vector entitys
  for (size_t i = 0; i < this->entitys.size(); i++) {
    delete this->entitys[i];
  }
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// sub update functions
void Process::updateInput(const float &delta_time) {
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_TAB"))) &&
      this->getKeytime())
    this->t_inventory.get()->toggleInventory();
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_CLOSE"))) &&
      this->getKeytime())
    this->Ipaused = !this->Ipaused;
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) &&
      this->getKeytime())
    this->Idebud = !this->Idebud;
}

void Process::updatePlayerInputs(const float &delta_time) {
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_A"))))
    this->player->e_move(-1.f, 0.f, delta_time);
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_D"))))
    this->player->e_move(1.f, 0.f, delta_time);
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_S"))))
    this->player->e_move(0.f, 1.f, delta_time);
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_W"))))
    this->player->e_move(0.f, -1.f, delta_time);

  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SPACE"))) &&
      this->getKeytime()) {
    for (auto &it : this->entitys)
      this->player->e_attack(it, delta_time);
  }
}

void Process::updateTileMap(const float &delta_time) { // update tilemap
  this->mapTiles->updateRenderArea(
      this->player->e_getGridPositionInt(this->IgridSize));
  this->mapTiles->update(this->player.get(), delta_time);

  // update entitys collision
  for (size_t i = 0; i < this->entitys.size(); i++)
    this->mapTiles->update(this->entitys[i], delta_time);
}

void Process::updateEntitys(const float &delta_time) { // update entitys
  for (size_t i = 0; i < this->entitys.size(); i++) {
    this->entitys[i]->e_update(delta_time);

    if (!this->entitys[i]->e_isAlive())
      this->entitys.erase(this->entitys.begin() + i);
  }
}

void Process::updateGUI(const float &delta_time) {
  if (this->t_inventory->isInventoryOpened()) // update inventory
    this->t_inventory->update(this->ImousePosWindow);
  if (this->minimap != nullptr) // update minimap
    this->minimap->update(this->player->e_getPosition(),
                          this->entitys[0]->e_getPosition());

  this->playerBar["HP_BAR"]->update(
      this->player->getAttributes()->getAttributes().health,
      this->player->getAttributes()->getAttributes().max_health);
  this->playerBar["MP_BAR"]->update(
      this->player->getAttributes()->getAttributes().mana,
      this->player->getAttributes()->getAttributes().max_mana);
}

// main update function
void Process::update(const float &delta_time) {
  // always update mouse position, inputs, and keyTime
  this->updateMousePositions(&this->view);
  this->updateKeytime(delta_time);
  this->updateInput(delta_time);

  // one more update
  if (this->Idebud)
    this->updateDebug(delta_time);

  if (this->Ipaused) { // update pause
    this->pausemenu->update(this->ImousePosWindow);

    if (this->pausemenu->isButtonPressed("EXIT_BUTTON") && this->getKeytime())
      this->endState();
    if (this->pausemenu->isButtonPressed("GEN") && this->getKeytime()) {
      delete this->myGN;
      this->mapTiles.reset();
      delete this->minimap;
      this->initTileMapData();
      this->initTileMap();
      this->initMiniMap();
      this->reCaclulateCharacterSize();
    }
  } else { // update game
    this->updateEntitys(delta_time);
    this->updatePlayerInputs(delta_time);
    this->player->e_update(delta_time);
    if (this->player->e_isAlive() == false)
      this->endState();
    this->updateGUI(delta_time);
  }
  this->updateTileMap(delta_time);
}

void Process::updateDebug(const float &delta_time) {
  double fps = 1.0f / delta_time;
  this->IstringStream
      << "FPS:\t" << fps << "\nCurrent memory usage:\t"
      << MemoryUsageMonitor::formatMemoryUsage(
             MemoryUsageMonitor::getCurrentMemoryUsage())

      << "\nResolution: " << this->Iwindow->getSize().x << " x "
      << this->Iwindow->getSize().y << "\nPlayer:"
      << "\nComponents: "
      << "\n\tvelX: " << this->player->e_getVelocity().x
      << "\n\tvelY: " << this->player->e_getVelocity().y << "\nPosition:"
      << "\n\tx: " << this->player->e_getPosition().x
      << "\n\ty: " << this->player->e_getPosition().y
      << "\n\tSecected Cell ID: "
      << this->t_inventory->getCurrentCellID(this->ImousePosWindow)
      << "\n\tgrid x: "
      << this->player->e_getGridPositionFloat(this->IgridSize).x
      << "\n\tgrid y: "
      << this->player->e_getGridPositionFloat(this->IgridSize).y
      << "\nMap Size: " << this->mapTiles->getMapSizeOnTiles().x << 'x'
      << this->mapTiles->getMapSizeOnTiles().y
      << "\nMap Area Render: " << this->mapTiles->getRenderArea().fromX << ' '
      << this->mapTiles->getRenderArea().fromY << ' '
      << this->mapTiles->getRenderArea().toX << ' '
      << this->mapTiles->getRenderArea().toY << '\n'
      << "Pause:\t" << this->Ipaused
      << "\nMemory Usage: "
      // get memory usage enemys on bytes
      << "\n\tPlayer: " << sizeof(*this->player) << " = " << sizeof(Player)
      << " bytes"
      << "\n\tEntitys: " << this->entitys.size() << " x " << sizeof(Entity)
      << " = " << this->entitys.size() * sizeof(Entity) << " bytes"
      << "\n\tTotal Entitys: " << Entity::count_entitys << "\n\tEntity[0] Data:"
      << "\n\t\tmovDir: "
      << this->entitys[0]->getMovement()->getDirectionVec().x << ' '
      << this->entitys[0]->getMovement()->getDirectionVec().y
      << "\n\t\tmovVel: " << this->entitys[0]->getMovement()->getVelocity().x
      << ' ' << this->entitys[0]->getMovement()->getVelocity().y
      << "\n\tTileMap: " << sizeof(*this->mapTiles) << " bytes"
      << "\n\tPauseMenu: " << sizeof(*this->pausemenu) << " bytes"
      << "\n\tInventory: " << sizeof(*this->t_inventory) << " bytes"
      << "\n\tTotal usage: "
      << sizeof(*this->player) + (this->entitys.size() * sizeof(Entity)) +
             sizeof(this->mapTiles) + sizeof(*this->pausemenu) +
             sizeof(*this->t_inventory)
      << " bytes"
      << "\nGenerator data:"
      << "\n\tSeed:\t" << this->noicedata.seed << "\n\tOctaves:\t"
      << this->noicedata.octaves << "\n\tFrequency:\t"
      << this->noicedata.frequency << "\n\tAmplifire:\t"
      << this->noicedata.amplifire << "\n\tPersistence:\t"
      << this->noicedata.persistence << "\n\tNoiceSizeBYWindowX:\t"
      << this->noicedata.RenderWindowX << "\n\tNoiceSizeBYWindowY:\t"
      << this->noicedata.RenderWindowY << "\n\tNoiceSizeMapX:\t"
      << this->noicedata.mapSizeX << "\n\tNoiceSizeMapY:\t"
      << this->noicedata.mapSizeY;

  this->Itext.setString(this->IstringStream.str());
  this->IstringStream.str("");
}

void Process::updateSounds(const float &delta_time) {}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// sub render functions
void Process::renderGUI(sf::RenderTarget &target) {
  if (this->Idebud) // debuging text render
    target.draw(this->Itext);

  if (this->Ipaused) // Pause menu render
  {
    if (this->pausemenu != nullptr)
      this->pausemenu->render(target);
  } else {
    if (this->t_inventory->isInventoryOpened()) // inventory  menu render
      this->t_inventory->render(target);
    else
      // this->t_inventoryHUD.get()->render(target);
      for (auto &it : this->playerBar) // render player bars
        it.second->render(target);

    if (this->minimap != nullptr)
      this->minimap->render(target);
  }
}

void Process::renderTileMap(sf::RenderTarget &target) {
  this->mapTiles->render(&target);
}

void Process::renderEntities(sf::RenderTarget &target) {
  for (auto *enemy : this->entitys)
    enemy->e_render(target, this->Idebud);
}

void Process::renderPlayer(sf::RenderTarget &target) {
  this->player->e_render(target, this->Idebud);
  this->playerView.setCenter(this->player->e_getPosition());
}

// main render function
void Process::render(sf::RenderWindow &target) {
  // CLEAR pre rendered texture
  this->renderTexture.clear();
  this->renderTexture.setView(this->playerView);
  // render scne in custom view
  this->renderTileMap(this->renderTexture);
  this->renderEntities(this->renderTexture);
  this->renderPlayer(this->renderTexture);
  // reset view
  this->renderTexture.setView(this->renderTexture.getDefaultView());
  // render GUI elements
  this->renderGUI(this->renderTexture);
  // final render
  this->renderTexture.display();
  target.draw(this->renderSprite);
}