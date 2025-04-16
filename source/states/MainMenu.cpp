#include "MainMenu.hpp"

void MainMenu::initRenderDefines() {
  if (!this->renderTexture.resize({this->IstateData->sd_Window->getSize().x,
                                   this->IstateData->sd_Window->getSize().y}))
    Logger::logStatic("renderTexture cannot be resize",
                      "MainMenu::initRenderDefines()", logType::ERROR);
  this->renderTexture.setSmooth(true);

  this->renderSprite.setTexture(this->renderTexture.getTexture());
  this->renderSprite.setTextureRect(sf::IntRect(
      {0, 0}, {static_cast<int>(this->IstateData->sd_Window->getSize().x),
               static_cast<int>(this->IstateData->sd_Window->getSize().y)}));

  this->view.setSize(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x),
      static_cast<float>(this->IstateData->sd_Window->getSize().y)));

  this->view.setCenter(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2));
}

void MainMenu::initKeybinds() {
  this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
  this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
  this->Ikeybinds["KEY_R"] = this->IsupportedKeys->at("R");
}

void MainMenu::initBackground() {

  sf::Texture tx;
  for (int i = 0; i < 3; i++) {
    this->background_textures.push_back(sf::Texture());
  }
  tx = TextureManager::getTexture("texture_background_lay_3");
  this->background_textures[0] = tx;
  tx = TextureManager::getTexture("texture_background_lay_2");
  this->background_textures[1] = tx;
  tx = TextureManager::getTexture("texture_background_lay_1");
  this->background_textures[2] = tx;

  // init background shapes
  for (size_t i = 0; i < 3; i++) {
    this->background_textures[i].setSmooth(true);
    this->backgrond_shapes.push_back(sf::RectangleShape());

    this->backgrond_shapes[i].setSize(
        sf::Vector2f(this->background_textures[i].getSize()));
    this->backgrond_shapes[i].setTexture(&this->background_textures[i], true);

    this->backgrond_shapes[i].setOrigin(
        sf::Vector2f(this->backgrond_shapes[i].getSize().x / 2,
                     this->backgrond_shapes[i].getSize().y / 2));

    this->backgrond_shapes[i].setPosition(sf::Vector2f(
        static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2 -
            (this->backgrond_shapes[i].getSize().x / 2) +
            this->backgrond_shapes[i].getOrigin().x,
        static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2 -
            (this->backgrond_shapes[i].getSize().y / 2) +
            this->backgrond_shapes[i].getOrigin().y));
  }
  this->backgrond_shapes[0].scale(sf::Vector2f(2.f, 2.f));
}

void MainMenu::initButtons() {
  struct ButtonInfo {
    std::string key;
    std::string text;

    ButtonInfo(const char *k, std::string t) : key(k), text(t) {}
  };

  float offsetX = mmath::p2pX(5, this->Iwindow->getSize().x);
  float offsetY = mmath::p2pX(5, this->Iwindow->getSize().y);

  sf::Vector2f sizebutton = {mmath::p2pX(15, this->Iwindow->getSize().x),
                             mmath::p2pX(7, this->Iwindow->getSize().y)};
  // Массив с координатами для каждой кнопки
  std::vector<sf::Vector2f> buttonOffsets = {
      {offsetX * 15.5f, offsetY * 2},  // noice
      {offsetX * 15.5f, offsetY * 10}, // continue
      {offsetX * 15.5f, offsetY * 12}, // start
      {offsetX * 15.5f, offsetY * 14}, // settings
      {offsetX * 15.5f, offsetY * 18}  // exit
  };

  // Данные о кнопках
  std::vector<ButtonInfo> buttonData = {
      {"NOICE_BTN", helperText::Button::BUTTON_NOICE_EDITOR},
      {"CONT_BTN", helperText::Button::BUTTON_CONTINUE},
      {"START_BTN", helperText::Button::BUTTON_PLAY},
      {"SETTINGS_BTN", helperText::Button::BUTTON_OPTIONS},
      {"EXIT_BTN", helperText::Button::BUTTON_EXIT}};

// Добавляем кнопку для отладки в режиме отладки
#if __MDEBUG__ == 1
  buttonData.push_back(
      {"DRS_BTN", helperText::Button::BUTTON_DEBUG_ROOM_STATE});

  // Добавляем позицию для кнопки отладки
  buttonOffsets.push_back({offsetX, offsetY});
#endif

  // Цикл для создания кнопок с данными из массива
  for (size_t i = 0; i < buttonData.size(); ++i) {
    const auto &button = buttonData[i];
    this->buttons[button.key] = std::make_unique<gui::Button>(
        buttonOffsets[i], sizebutton, button.text,
        gui::styles::buttons::btn_default, gui::type::BUTTON);
  }
}
void MainMenu::initGUI() {
  this->initBackground();
  this->initButtons();
}

void MainMenu::resetGUI() {
  // delete buttons
  if (!this->buttons.empty())
    this->buttons.clear();

  this->backgrond_shapes.clear();

  this->initBackground();
  this->initButtons();
  this->initRenderDefines();
  this->IstateData->reserGUI = false;
}

void MainMenu::resetView() {
  this->view.setSize(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x),
      static_cast<float>(this->IstateData->sd_Window->getSize().y)));

  this->view.setCenter(sf::Vector2f(
      static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
      static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2));
}

void MainMenu::initSounds() {
  // link to volume manager
  this->IvolumeManager = this->IstateData->sd_volumeManager;

  try {
    for (const auto &[category, soundKey, mapKey] :
         {std::tuple{SoundCategory::vol_MUSIC, myConst::sounds::music_menu,
                     "MAIN_MENU"},
          {SoundCategory::vol_UI, myConst::sounds::selbtn_menu, "SELECT_MENU"},
          {SoundCategory::vol_UI, myConst::sounds::press_newg,
           "PRESS_NEW_GAME"},
          {SoundCategory::vol_UI, myConst::sounds::press_btn,
           "PRESS_BUTTON"}}) {
      if (!this->loadSoundtoBuffer(category, soundKey, mapKey)) {
        throw soundKey;
      }
    }
  } catch (std::exception &e) {
    Logger::logStatic("can't load: " + std::string(e.what()),
                      "MainMenu::initSounds()", logType::ERROR);
  }

  // Upload sounds from buffer
  for (const auto &[mapKey, category] :
       {std::pair{"MAIN_MENU", SoundCategory::vol_MUSIC},
        {"SELECT_MENU", SoundCategory::vol_UI},
        {"PRESS_NEW_GAME", SoundCategory::vol_UI},
        {"PRESS_BUTTON", SoundCategory::vol_UI}}) {
    this->IsoundsMap.emplace(mapKey, this->IsoundBufferMap[category][mapKey]);
  }

  // set volume in sound map
  this->updateSounds(0.f);
}

MainMenu::MainMenu(StateData *statedata)
    : State(statedata),
      renderSprite(TextureManager::getTexture("texture_null")) {
  // logger
  Logger::logStatic("MainMenu constructor", "MainMenu");
  this->initRenderDefines();
  this->initGUI();
  this->initKeybinds();
  this->initButtons();
  this->initSounds();
}

MainMenu::~MainMenu() {
  Logger::logStatic("MainMenu destructor", "MainMenu");

  // delete buttons
  if (!this->buttons.empty())
    this->buttons.clear();

  this->backgrond_shapes.clear();
  this->IsoundsMap.clear();
  this->IsoundBufferMap.clear();
}

void MainMenu::update(const float &delta_time) {
  if (this->IstateData->reserGUI)
    this->resetGUI();

  this->updateKeytime(delta_time);

  this->updateGUI(delta_time);

  this->updateMousePositions(&this->view);
  this->updateInput(delta_time);
  this->updateButtons();
  this->updateSounds(delta_time);
}

void MainMenu::updateInput(const float &delta_time) {
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) &&
      this->getKeytime())
    this->Idebud = !this->Idebud;

  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_R"))) &&
      this->getKeytime()) {
    this->resetGUI();
  }
}

void MainMenu::updateButtons() {
  if (!this->buttons.empty()) {
    for (auto &it : this->buttons) {

      it.second->update(this->ImousePosWindow);
      if (it.second->isPressed())
        if (this->IsoundsMap.find("PRESS_BUTTON")->second.getStatus() !=
            sf::Sound::Status::Playing)
          this->IsoundsMap.at("PRESS_BUTTON").play(); // play sound once
      if (it.second->isHover())
        if (this->IsoundsMap.find("SELECT_MENU")->second.getStatus() !=
            sf::Sound::Status::Playing)
          this->IsoundsMap.at("SELECT_MENU").play(); // play sound once
    }

    if (this->buttons["EXIT_BTN"]->isPressed() && this->getKeytime()) {
      this->endState();
    }

    if (this->buttons["START_BTN"]->isPressed() && this->getKeytime()) {
      this->Istates->push(new Process(this->IstateData, false));
    }

    if (this->buttons["CONT_BTN"]->isPressed() && this->getKeytime()) {
      this->Istates->push(new Process(this->IstateData, true));
      this->resetView();
    }
    if (this->buttons["SETTINGS_BTN"]->isPressed() && this->getKeytime())
      this->Istates->push(new SettingsState(this->IstateData));

    if (this->buttons["NOICE_BTN"]->isPressed() && this->getKeytime())
      this->Istates->push(new EditorState(this->IstateData));
  }
}

void MainMenu::updateGUI(const float &delta_time) {
  // update debug text
  if (this->Idebud) {
    this->IstringStream
        << "\nver:\t" << CMAKE_PROJECT_VERSION << "\nCurrent memory usage:\t"
        << MemoryUsageMonitor::formatMemoryUsage(
               MemoryUsageMonitor::getCurrentMemoryUsage())
        << "\nCurrent state memory usage:\t" << getMemoryUsage() << " bytes"
        << "\nFPS delta:\t" << 1 / delta_time << "\nFPS Clock:\t"
        << FPS::getFPS() << "\nFPS limit:\t"
        << this->IstateData->sd_gfxSettings->_struct.frameRateLimit
        << "\nDelta Time:\t" << delta_time << "\nResolution:\t"
        << this->IstateData->sd_Window->getSize().x << " x "
        << this->IstateData->sd_Window->getSize().y << "\nAntialiasing:\t"
        << this->IstateData->sd_Window->getSettings().antiAliasingLevel
        << "\nvSync:\t"
        << this->IstateData->sd_gfxSettings->_struct.verticalSync
        << "\nMouse Pos:\t" << this->ImousePosWindow.x << " x "
        << this->ImousePosWindow.y << "\nVolume: "
        << "\n\tMASTER: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_MASTER))
        << "\n\tSFX: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_SFX))
        << "\n\tMUSIC: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_MUSIC))
        << "\n\tAMBIENT: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_AMBIENT))
        << "\n\tENTITY: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_ENTITY))
        << "\n\tUI: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_UI))
        << "\n\tDIALOGUE: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_DIALOGUE))
        << "\n\tFOLEY: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_FOLEY))
        << "\n\tWEAPON: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_WEAPON))
        << "\n\tENVIRONMENT: " +
               std::to_string(this->IvolumeManager.get()->getCategoryVolume(
                   SoundCategory::vol_ENVIRONMENT));
    this->Itext.setString(this->IstringStream.str());
    this->IstringStream.str("");
  }

  // update GUI
  this->backgrond_shapes[0].rotate(sf::degrees(delta_time));
  this->backgrond_shapes[1].rotate(sf::degrees(-delta_time));
}

void MainMenu::updateSounds(const float &delta_time) {
  // update for music menu
  for (const auto &[key, category] :
       {std::pair{"MAIN_MENU", SoundCategory::vol_MUSIC},
        {"SELECT_MENU", SoundCategory::vol_UI},
        {"PRESS_NEW_GAME", SoundCategory::vol_UI},
        {"PRESS_BUTTON", SoundCategory::vol_UI}}) {
    auto it = this->IsoundsMap.find(key);
    if (it != this->IsoundsMap.end()) {
      it->second.setVolume(this->IvolumeManager->getCategoryVolume(category));
    }
  }

  // check for playing music "main menu"
  if (this->IsoundsMap.find("MAIN_MENU")->second.getStatus() !=
      sf::Sound::Status::Playing)
    this->IsoundsMap.find("MAIN_MENU")->second.play();

  // check for playing sound "select menu" when cursor on button

  // stop if lost focus on window
  if (!this->Iwindow->hasFocus())
    for (auto &it : this->IsoundsMap)
      it.second.pause();
}

void MainMenu::render(sf::RenderWindow &target) {
  this->renderTexture.clear();
  this->renderTexture.setView(this->view);

  // render background shapes
  for (auto &it : this->backgrond_shapes)
    renderTexture.draw(it);

  // render GUI
  if (!this->buttons.empty())
    for (auto &it : this->buttons)
      renderTexture.draw(
          *it.second
               .get()); // Отрисовываем кнопки в renderTexture, а не в target

  // debug text
  if (this->Idebud)
    this->renderTexture.draw(this->Itext);

  this->renderTexture.setView(this->renderTexture.getDefaultView());

  this->renderTexture.display();

  target.draw(this->renderSprite);
}