#include "MainMenu.hpp"

void MainMenu::initRenderDefines()
{
    if (!this->renderTexture.resize({this->IstateData->sd_Window->getSize().x, this->IstateData->sd_Window->getSize().y}))
        Logger::logStatic("renderTexture cannot be resize", "MainMenu::initRenderDefines()", logType::ERROR);
    this->renderTexture.setSmooth(true);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect({0, 0},
                                                  {static_cast<int>(this->IstateData->sd_Window->getSize().x),
                                                   static_cast<int>(this->IstateData->sd_Window->getSize().y)}));

    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sd_Window->getSize().x),
        static_cast<float>(this->IstateData->sd_Window->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
        static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2));
}

void MainMenu::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
}

void MainMenu::initBackground()
{

    sf::Texture tx;
    for (int i = 0; i < 3; i++) {
        this->background_textures.push_back(sf::Texture());
    }
    tx.update(TextureManager::getTexture("texture_background_lay_1"));
    this->background_textures[0] = tx;
    tx.update(TextureManager::getTexture("texture_background_lay_2"));
    this->background_textures[1] = tx;
    tx.update(TextureManager::getTexture("texture_background_lay_3"));
    this->background_textures[2] = tx;

    // init background shapes
    for (size_t i = 0; i < 3; i++)
    {
        this->backgrond_shapes.push_back(sf::RectangleShape());

        this->backgrond_shapes[i].setSize(sf::Vector2f(this->background_textures[i].getSize()));
        this->backgrond_shapes[i].setTexture(&this->background_textures[i], true);

        this->backgrond_shapes[i].setOrigin(sf::Vector2f(
            this->backgrond_shapes[i].getSize().x / 2,
            this->backgrond_shapes[i].getSize().y / 2));

        this->backgrond_shapes[i].setPosition(sf::Vector2f(
            static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2 - (this->backgrond_shapes[i].getSize().x / 2) + this->backgrond_shapes[i].getOrigin().x,
            static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2 - (this->backgrond_shapes[i].getSize().y / 2) + this->backgrond_shapes[i].getOrigin().y));
    }
    this->backgrond_shapes[0].scale(sf::Vector2f(2.f, 2.f));
}

void MainMenu::initButtons()
{
    int offsetX = mmath::p2pX(5, this->Iwindow->getSize().x);
    int offsetY = mmath::p2pX(5, this->Iwindow->getSize().y);

    this->buttons["CONT_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(60, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->sd_font, helperText::Button::BUTTON_CONTINUE, this->IstateData->sd_characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["START_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(70, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->sd_font, helperText::Button::BUTTON_PLAY, this->IstateData->sd_characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["SETTINGS_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(80, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->sd_font, helperText::Button::BUTTON_OPTIONS, this->IstateData->sd_characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(90, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->sd_font, helperText::Button::BUTTON_EXIT, this->IstateData->sd_characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["NOICE_BNT"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(10, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->sd_font, helperText::Button::BUTTON_NOICE_EDITOR, this->IstateData->sd_characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));
}

void MainMenu::initGUI()
{
    this->initBackground();
    this->initButtons();
}

void MainMenu::resetGUI()
{
    // delete buttons
    if (!this->buttons.empty())
        for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
            delete it->second;
    this->buttons.clear();

    this->backgrond_shapes.clear();

    this->initBackground();
    this->initButtons();
    this->initRenderDefines();
    this->IstateData->reserGUI = false;
}

void MainMenu::resetView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sd_Window->getSize().x),
        static_cast<float>(this->IstateData->sd_Window->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sd_Window->getSize().x) / 2,
        static_cast<float>(this->IstateData->sd_Window->getSize().y) / 2));
}

void MainMenu::initSounds()
{
    // link to volume manager
    this->IvolumeManager = this->IstateData->sd_volumeManager;
#if __MDEBUG__ == 1
    if (!this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::music_menu), "MAIN_MENU"))
        Logger::logStatic("Cannot load to buffer" + std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::music_menu), "MainMenu::initSounds()", logType::ERROR);
    if (!this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::selbtn_menu), "SELECT_MENU"))
        Logger::logStatic("Cannot load to buffer" + std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::selbtn_menu), "MainMenu::initSounds()", logType::ERROR);
    if (!this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_newg), "PRESS_NEW_GAME"))
        Logger::logStatic("Cannot load to buffer" + std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_newg), "MainMenu::initSounds()", logType::ERROR);
    if (!this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_btn), "PRESS_BUTTON"))
        Logger::logStatic("Cannot load to buffer" + std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_btn), "MainMenu::initSounds()", logType::ERROR);

    // upload sounds from buffer

    this->IsoundsMap.get()->at("MAIN_MENU") = sf::Sound(this->IsoundBufferMap.get()->at("MAIN_MENU"));

#else
    // load sounds
    this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::music_menu), "MAIN_MENU");
    this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::selbtn_menu), "SELECT_MENU");
    this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_newg), "PRESS_NEW_GAME");
    this->loadSoundtoBuffer(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sounds::press_btn), "PRESS_BUTTON");

    // upload sounds from buffer
    this->IsoundBufferMap.get()->emplace("MAIN_MENU", std::make_shared<sf::SoundBuffer>(this->IsoundBufferMap.get()->at("MAIN_MENU")));
    this->IsoundBufferMap.get()->emplace("SELECT_MENU", std::make_shared<sf::SoundBuffer>(this->IsoundBufferMap.get()->at("SELECT_MENU")));
    this->IsoundBufferMap.get()->emplace("PRESS_NEW_GAME", std::make_shared<sf::SoundBuffer>(this->IsoundBufferMap.get()->at("PRESS_NEW_GAME")));
    this->IsoundBufferMap.get()->emplace("PRESS_BUTTON", std::make_shared<sf::SoundBuffer>(this->IsoundBufferMap.get()->at("PRESS_BUTTON")));

#endif
        // set volume in sound map
        for (auto& it : *this->IsoundsMap.get())
            it.second.setVolume(50.f);
}

MainMenu::MainMenu(StateData *statedata)
    : State(statedata), renderSprite(TextureManager::getTexture("texture_null"))
{
    // logger
    Logger::logStatic("MainMenu constructor", "MainMenu");
    this->initGUI();
    this->initRenderDefines();
    this->initKeybinds();
    this->initButtons();
    this->initSounds();
}

MainMenu::~MainMenu()
{
    Logger::logStatic("MainMenu destructor", "MainMenu");

    // delete buttons
    if (!this->buttons.empty())
        for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
            delete it->second;
    this->buttons.clear();

    this->backgrond_shapes.clear();
    this->IsoundsMap.get()->clear();
    this->IsoundBufferMap.get()->clear();
}

void MainMenu::update(const float& delta_time)
{
    if (this->IstateData->reserGUI)
        this->resetGUI();

    this->updateKeytime(delta_time);

    this->updateGUI(delta_time);

    this->updateMousePositions(&this->view);
    this->updateInput(delta_time);
    this->updateButtons();
    this->updateSounds(delta_time);
}

void MainMenu::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->Idebud = !this->Idebud;
}

void MainMenu::updateButtons()
{
    if (!this->buttons.empty()) {
        for (auto& it : this->buttons) {

            it.second->update(this->ImousePosWindow);
            if (it.second->isPressed())
                if (this->IsoundsMap->at("PRESS_BUTTON").getStatus() != sf::Sound::Status::Playing)
                    this->IsoundsMap->at("PRESS_BUTTON").play(); // play sound once
            if (it.second->isHover())
                if (this->IsoundsMap->at("SELECT_MENU").getStatus() != sf::Sound::Status::Playing)
                    this->IsoundsMap->at("SELECT_MENU").play(); // play sound once
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

        if (this->buttons["NOICE_BNT"]->isPressed() && this->getKeytime())
            this->Istates->push(new EditorState(this->IstateData));
    }
}

void MainMenu::updateGUI(const float& delta_time)
{
    // update debug text
    if (this->Idebud) {
        this->IstringStream
            << "\nver:\t" << CMAKE_PROJECT_VERSION
            << "\nCurrent memory usage:\t" << MemoryUsageMonitor::formatMemoryUsage(MemoryUsageMonitor::getCurrentMemoryUsage())
            << "\nCurrent state memory usage:\t" << getMemoryUsage() << " bytes"
            << "\nFPS delta:\t" << 1 / delta_time
            << "\nFPS Clock:\t" << FPS::getFPS()
            << "\nFPS limit:\t" << this->IstateData->sd_gfxSettings->_struct.frameRateLimit
            << "\nDelta Time:\t" << delta_time
            << "\nResolution:\t" << this->IstateData->sd_Window->getSize().x << " x " << this->IstateData->sd_Window->getSize().y
            << "\nAntialiasing:\t" << this->IstateData->sd_Window->getSettings().antiAliasingLevel
            << "\nvSync:\t" << this->IstateData->sd_gfxSettings->_struct.verticalSync
            << "\nMouse Pos:\t" << this->ImousePosWindow.x << " x " << this->ImousePosWindow.y
            << "\nVolume: "
            << "\n\tMASTER: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_MASTER))
            << "\n\tSFX: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_SFX))
            << "\n\tMUSIC: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_MUSIC))
            << "\n\tAMBIENT: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_AMBIENT))
            << "\n\tENTITY: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_ENTITY))
            << "\n\tUI: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_UI))
            << "\n\tDIALOGUE: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_DIALOGUE))
            << "\n\tFOLEY: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_FOLEY))
            << "\n\tWEAPON: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_WEAPON))
            << "\n\tENVIRONMENT: " + std::to_string(this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_ENVIRONMENT));
        this->Itext.setString(this->IstringStream.str());
        this->IstringStream.str("");
    }

    // update GUI
    this->backgrond_shapes[0].rotate(sf::degrees(delta_time));
    this->backgrond_shapes[1].rotate(sf::degrees(-delta_time));
}

void MainMenu::updateSounds(const float& delta_time)
{
    // update for music menu
    this->IsoundsMap->at("MAIN_MENU").setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER) * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MUSIC) / 100);
    this->IsoundsMap->at("SELECT_MENU").setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER) * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_SFX) / 100);
    this->IsoundsMap->at("PRESS_NEW_GAME").setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER) * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_SFX) / 100);
    this->IsoundsMap->at("PRESS_BUTTON").setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER) * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_SFX) / 100);

    // check for playing music "main menu"
    if (this->IsoundsMap->at("MAIN_MENU").getStatus() != sf::Sound::Status::Playing)
        this->IsoundsMap->at("MAIN_MENU").play();

    // check for playing sound "select menu" when cursor on button
}

void MainMenu::render(sf::RenderWindow& target)
{
    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    // render background shapes
    for (auto& it : this->backgrond_shapes)
        renderTexture.draw(it);
    // render GUI
    if (!this->buttons.empty())
        for (auto& it : this->buttons)
            it.second->render(renderTexture);
    // fadeout fx

    // debug text
    if (this->Idebud)
        this->renderTexture.draw(this->Itext);

    this->renderTexture.setView(this->renderTexture.getDefaultView());

    this->renderTexture.display();

    target.draw(this->renderSprite);
}