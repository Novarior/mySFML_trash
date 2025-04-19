#include "Core.h"
#include "LOGGER.hpp"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "keyboard.hpp"
#include <IOKit/hid/IOHIDUsageTables.h>
#include <iostream>
#include <memory>

#if __APPLE__
void Core::initDirectories() { // check if app directory exists
  if (ApplicationsFunctions::checkAppDirectoryExists())
    Logger::logStatic("App directory already exists",
                      "l:7 -> Core::initDirectories()");
}
#endif

// initialisations root data and build first frame app
void Core::initVar() {
  this->mWindow = NULL;

  if (!this->gfxSettings.loadFromFile())
    this->gfxSettings.saveToFile();
}

void Core::initStateData() {
  this->mStatedata.sd_Window = this->mWindow;
  this->mStatedata.sd_States = &this->mState;
  if (!this->mStatedata.sd_font.openFromFile(
          std::string(ApplicationsFunctions::get_resources_dir() +
                      myConst::fonts::data_gameproces_font_path_3))) {
    Logger::logStatic(
        "ERROR::GAMEPROCES::COULD NOT LOAD TO FILE: " +
            std::string(ApplicationsFunctions::get_resources_dir() +
                        myConst::fonts::data_gameproces_font_path_3),
        "Core::initStateData()");
  }
  if (!this->mStatedata.sd_debugFont.openFromFile(
          std::string(ApplicationsFunctions::get_resources_dir() +
                      myConst::fonts::data_debugfont_path))) {
    Logger::logStatic(
        "ERROR::DEBUG::COULD NOT LOAD TO FILE: " +
            std::string(ApplicationsFunctions::get_resources_dir() +
                        myConst::fonts::data_debugfont_path),
        "Core::initStateData()");
  }
  this->mStatedata.sd_supportedKeys = &this->supportedKeys;
  this->mStatedata.sd_gfxSettings = &this->gfxSettings;
  this->mStatedata.sd_gridSize = this->gfxSettings._struct.gridSize;
  this->mStatedata.sd_characterSize_debug =
      mmath::calcCharSize(this->mWindow->getSize(), 150);
  this->mStatedata.sd_characterSize_game_big =
      mmath::calcCharSize(this->mWindow->getSize(), 60);
  this->mStatedata.sd_characterSize_game_medium =
      mmath::calcCharSize(this->mWindow->getSize(), 85);
  this->mStatedata.sd_characterSize_game_small =
      mmath::calcCharSize(this->mWindow->getSize(), 100);
  this->mStatedata.reserGUI = false;

  this->mStatedata.sd_volumeManager =
      std::shared_ptr<VolumeManager>(new VolumeManager());

  // share acsess to keyboard
  this->keyboard = std::make_shared<keyboardOSX>();
  this->mStatedata.sd_keyboard = this->keyboard;

#if __MDEBUG__ == 1
  // logger moment

  // check if window is not null
  if (!this->mStatedata.sd_Window.lock())
    Logger::logStatic("ERROR::WINDOW::NOT INITED", "Core::initStateData()",
                      logType::ERROR);

  // check if states is not empty or null idk
  if (!this->mStatedata.sd_States->empty())
    Logger::logStatic("ERROR::STATES::NOT INITED", "Core::initStateData()",
                      logType::ERROR);

#endif
}

void Core::initKeyBinds() { // init default keys

  // load key binds from file
  // if (!ParserJson::loadKeyBinds(this->supportedKeys)) {
  //   Logger::logStatic("Key binds not loaded", "Core::initKeyBinds()");
  // } else { // load default key binds
  //   Logger::logStatic("Key binds loaded", "Core::initKeyBinds()");
  supportedKeys["Escape"] = kHIDUsage_KeyboardEscape;
  supportedKeys["A"] = kHIDUsage_KeyboardA;
  supportedKeys["C"] = kHIDUsage_KeyboardC;
  supportedKeys["D"] = kHIDUsage_KeyboardD;
  supportedKeys["E"] = kHIDUsage_KeyboardE;
  supportedKeys["F"] = kHIDUsage_KeyboardF;
  supportedKeys["Q"] = kHIDUsage_KeyboardQ;
  supportedKeys["R"] = kHIDUsage_KeyboardR;
  supportedKeys["S"] = kHIDUsage_KeyboardS;
  supportedKeys["W"] = kHIDUsage_KeyboardW;
  supportedKeys["X"] = kHIDUsage_KeyboardX;
  supportedKeys["Z"] = kHIDUsage_KeyboardZ;
  supportedKeys["1"] = kHIDUsage_Keyboard1;
  supportedKeys["2"] = kHIDUsage_Keyboard2;
  supportedKeys["3"] = kHIDUsage_Keyboard3;
  supportedKeys["4"] = kHIDUsage_Keyboard4;
  supportedKeys["5"] = kHIDUsage_Keyboard5;
  supportedKeys["6"] = kHIDUsage_Keyboard6;
  supportedKeys["7"] = kHIDUsage_Keyboard7;
  supportedKeys["8"] = kHIDUsage_Keyboard8;
  supportedKeys["9"] = kHIDUsage_Keyboard9;
  supportedKeys["0"] = kHIDUsage_Keyboard0;
  supportedKeys["Space"] = kHIDUsage_KeyboardSpacebar;
  supportedKeys["Enter"] = kHIDUsage_KeyboardReturnOrEnter;
  supportedKeys["BackSpace"] = kHIDUsage_KeyboardDeleteOrBackspace;
  supportedKeys["Slash"] = kHIDUsage_KeyboardSlash;
  supportedKeys["Tab"] = kHIDUsage_KeyboardTab;
  supportedKeys["F1"] = kHIDUsage_KeyboardF1;
  supportedKeys["F2"] = kHIDUsage_KeyboardF2;
  supportedKeys["F3"] = kHIDUsage_KeyboardF3;

#if __MDEBUG__ == 1
  // logger moment with key binds
  Logger::logStatic("Key binds inited by deafault", "Core::initKeyBinds()");

#endif
  // save default keys to file
  //  ParserJson::saveKeyBinds(this->supportedKeys);

#if __MDEBUG__ == 1
  // logger moment with key binds
  Logger::logStatic("Key binds inited", "Core::initKeyBinds()");

  // log all keys
  for (auto &i : supportedKeys)
    Logger::logStatic("Key: " + i.first + " Value: " +
                          std::to_string(static_cast<int>(i.second)),
                      "Core::initKeyBinds()");

#endif
}

void Core::initState() {
  this->mState.push(new MainMenu(&this->mStatedata));

#if __MDEBUG__ == 1
  // logger moment with states
  Logger::logStatic("State inited", "Core::initState()");
  Logger::logStatic("State size: " + std::to_string(this->mState.size()),
                    "Core::initState()");
#endif
}

void Core::initLocations() {
  helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);
}

void Core::initWindow() {
  mWindow = std::make_shared<sf::RenderWindow>(
      sf::RenderWindow(gfxSettings._struct.resolution,
                       gfxSettings._struct.title, sf::State::Windowed));

  if (gfxSettings._struct.fullscreen && mWindow->isOpen()) {

    gfxSettings._struct._winResolutions = mWindow->getSize();
    mWindow->create(sf::VideoMode({gfxSettings._struct._winResolutions.x,
                                   gfxSettings._struct._winResolutions.y}),
                    gfxSettings._struct.title, sf::State::Fullscreen,
                    gfxSettings._struct.contextSettings);
  }

  mWindow->setFramerateLimit(gfxSettings._struct.frameRateLimit);
  mWindow->setVerticalSyncEnabled(gfxSettings._struct.verticalSync);
  mWindow->setKeyRepeatEnabled(false);
}
void Core::initTextures() {
  // null текстура
  TextureManager::loadTexture(TextureID::TEXTURE_NULL,
                              myConst::textures::texture_NULL);
  // текстуры для карты
  TextureManager::loadTexture(TextureID::TEXTURE_DEEP_OCEAN,
                              myConst::textures::texture_DEEP_OCEAN);
  TextureManager::loadTexture(TextureID::TEXTURE_OCEAN,
                              myConst::textures::texture_OCEAN);
  TextureManager::loadTexture(TextureID::TEXTURE_SAND,
                              myConst::textures::texture_SAND);
  TextureManager::loadTexture(TextureID::TEXTURE_GRASS,
                              myConst::textures::texture_GRASS);
  TextureManager::loadTexture(TextureID::TEXTURE_DIRT,
                              myConst::textures::texture_DIRT);
  TextureManager::loadTexture(TextureID::TEXTURE_STONE,
                              myConst::textures::texture_STONE);
  TextureManager::loadTexture(TextureID::TEXTURE_SNOW,
                              myConst::textures::texture_SNOW);

  // загружаем текстуры сущностей
  TextureManager::loadTexture(TextureID::TEXTURE_PLAYER,
                              myConst::sprites::texture_PLAYER);
  TextureManager::loadTexture(TextureID::TEXTURE_SLIME,
                              myConst::sprites::texture_SLIME);

  // бек в главном меню
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_1,
                              myConst::gui::texture_background_mainmenu_lay_1);
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_2,
                              myConst::gui::texture_background_mainmenu_lay_2);
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_3,
                              myConst::gui::texture_background_mainmenu_lay_3);

  // текстуры итемов и тп
  // Загружаем текстуру для ячеек и предметов
  TextureManager::loadTexture(TextureID::ITEMS_NULL, ItemTextures::item_NULL);
  TextureManager::loadTexture(TextureID::INVENTORY_CELL_TEXTURE,
                              ItemTextures::inv_cell_back);
  TextureManager::loadTexture(
      TextureID::ITEMS_POISON_SMALL_REGENERATION,
      ItemTextures::poison::item_img_poison_small_regeneration);
  TextureManager::loadTexture(TextureID::ITEMS_STONE,
                              ItemTextures::items::item_img_stone);

  // Дополнительные текстуры для новых предметов
  // Эти текстуры должны быть добавлены в resources, пока используем
  // существующие
  TextureManager::loadTexture(
      TextureID::ITEMS_WOOD,
      ItemTextures::items::item_img_stone2); // Временно используем текстуру
                                             // камня
  TextureManager::loadTexture(
      TextureID::ITEMS_IRON_SWORD,
      ItemTextures::items::item_img_claster_crystal); // Временно используем
                                                      // текстуру кристалла
  TextureManager::loadTexture(
      TextureID::ITEMS_BREAD,
      ItemTextures::item_NULL); // Временно используем пустую текстуру
  TextureManager::loadTexture(
      TextureID::ITEMS_LEATHER_ARMOR,
      ItemTextures::item_NULL); // Временно используем пустую текстуру
  TextureManager::loadTexture(
      TextureID::ITEMS_HEALTH_POTION,
      ItemTextures::poison::item_img_poison_small_regeneration); // Временно
                                                                 // используем
                                                                 // текстуру яда

  // текстуры для монет
  TextureManager::loadTexture(TextureID::COINS_GOLD_NUGGET,
                              ItemTextures::coins::item_img_gold_nugget);
  TextureManager::loadTexture(TextureID::COINS_COPPER_NUGGET,
                              ItemTextures::coins::item_img_copper_nuggen);
  TextureManager::loadTexture(TextureID::COINS_SILVER_NUGGET,
                              ItemTextures::coins::item_img_silver_nuggen);
  TextureManager::loadTexture(
      TextureID::ITEMS_GOLD_COIN,
      ItemTextures::coins::item_img_gold_nugget); // Используем текстуру золотой
                                                  // монеты
}

Core::Core() {
  this->initDirectories();
  this->initKeyBinds();
  this->initVar();
  this->initWindow();
  this->initStateData();
  this->initLocations();
  this->initTextures();
  this->initState();

  FPS::reset();

#if __MDEBUG__ == 1
  Logger::logStatic("Core Inited", "Core::Core()");
#endif
}

Core::~Core() {
  this->gfxSettings.saveToFile();

  while (!this->mState.empty()) {
    delete this->mState.top();
    this->mState.pop();
  }
  mWindow.get()->close();
  mWindow.reset();

#if __MDEBUG__ == 1
  // logger moment
  Logger::logStatic("Core Delete...", "Core::~Core()");

  if (this->mState.empty())
    Logger::logStatic("State is empty", "Core::~Core()");
  else
    Logger::logStatic("State is not empty... mem leaked", "Core::~Core()",
                      logType::ERROR);

  if (this->mWindow == NULL)
    Logger::logStatic("Window is null", "Core::~Core()");
  else
    Logger::logStatic("Window is null... mem leaked", "Core::~Core()",
                      logType::ERROR);

  Logger::logStatic("Core Deleted", "Core::~Core()");
#endif
}

void Core::run() {
  Logger::logStatic("Start main loop", "Core::run()");

  while (this->mWindow->isOpen()) {
    this->updateDeltaTime();
    this->update();
    this->updateSound();
    this->render();
  }
}

void Core::update() {
  // state update
  this->updateEventsWindow();

  if (!this->mState.empty()) {
    if (this->mWindow->hasFocus()) {

      keyboard.get()->update();
      this->mState.top()->update(this->deltaTime);

      if (this->mState.top()->getQuit()) {
        delete this->mState.top();
        this->mState.pop();
      }
    }
  }
  // Application end
  else {
    this->mWindow->close();
  }
}

void Core::updateEventsWindow() {
  while (const std::optional event = mWindow.get()->pollEvent())
    if (event->is<sf::Event::Closed>())
      this->mWindow->close();
}

void Core::render() {
  this->mWindow->clear();

  if (!this->mState.empty())
    this->mState.top()->render(*this->mWindow.get());

  this->mWindow->display();
}

void Core::updateSound() {
  if (!this->mState.empty())
    this->mState.top()->updateSounds(deltaTime);
}

void Core::updateDeltaTime() {
  this->deltaTime = 0;
  this->deltaTime = this->deltaClock.restart().asSeconds();
  FPS::update();
}