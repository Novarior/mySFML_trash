#include "MainMenu.hpp"
#include "VolumeManager.hpp"

void MainMenu::initRenderDefines()
{
    this->renderTexture.create(
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y);
    this->renderTexture.setSmooth(true);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0,
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y));

    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x) / 2,
        static_cast<float>(this->IstateData->sWindow->getSize().y) / 2));
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
    tx.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::texture_background_mainmenu_lay_3));
    tx.setSmooth(true);
    this->background_textures[0] = tx;
    tx.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::texture_background_mainmenu_lay_2));
    tx.setSmooth(true);
    this->background_textures[1] = tx;
    tx.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::texture_background_mainmenu_lay_1));
    tx.setSmooth(true);
    this->background_textures[2] = tx;

    // init background shapes
    for (size_t i = 0; i < 3; i++) {
        this->backgrond_shapes.push_back(sf::RectangleShape());

        this->backgrond_shapes[i].setSize(sf::Vector2f(this->background_textures[i].getSize()));
        this->backgrond_shapes[i].setTexture(&this->background_textures[i], true);

        this->backgrond_shapes[i].setOrigin(sf::Vector2f(
            this->backgrond_shapes[i].getSize().x / 2,
            this->backgrond_shapes[i].getSize().y / 2));

        this->backgrond_shapes[i].setPosition(sf::Vector2f(
            static_cast<float>(this->IstateData->sWindow->getSize().x) / 2 - (this->backgrond_shapes[i].getSize().x / 2) + this->backgrond_shapes[i].getOrigin().x,
            static_cast<float>(this->IstateData->sWindow->getSize().y) / 2 - (this->backgrond_shapes[i].getSize().y / 2) + this->backgrond_shapes[i].getOrigin().y));
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
        this->IstateData->font, helperText::Button::BUTTON_CONTINUE, this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["START_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(70, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, helperText::Button::BUTTON_PLAY, this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["SETTINGS_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(80, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, helperText::Button::BUTTON_OPTIONS, this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(90, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, helperText::Button::BUTTON_EXIT, this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["NOICE_BNT"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(10, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, helperText::Button::BUTTON_NOICE_EDITOR, this->IstateData->characterSize_game_big,
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
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x) / 2,
        static_cast<float>(this->IstateData->sWindow->getSize().y) / 2));
}

void MainMenu::initSounds()
{
    // link to volume manager
    for (size_t it = 0; it < this->IvolumeManager->getCategoryVolumesSize(); it++) {
        this->IstateData->volumeManager.push_back(this->IvolumeManager.get());
    }

    this->IsoundBuffer.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::sound_test));
    this->Isound.setBuffer(this->IsoundBuffer);
    this->Isound.setLoop(true);
    this->Isound.setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER)
        * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MUSIC) / 100);
}

MainMenu::MainMenu(StateData* statedata)
    : State(statedata)
{
    // logger
    Logger::log("MainMenu constructor", "MainMenu");
    this->initGUI();
    this->initRenderDefines();
    this->initKeybinds();
    this->initButtons();
    this->initSounds();
}

MainMenu::~MainMenu()
{
    Logger::log("MainMenu destructor", "MainMenu");

    // delete buttons
    if (!this->buttons.empty())
        for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
            delete it->second;
    this->buttons.clear();

    this->backgrond_shapes.clear();
    this->Isound.stop();
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
        this->debugMode = !this->debugMode;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash) && this->getKeytime())
        this->debugMode = !this->debugMode;
}

void MainMenu::updateButtons()
{
    if (!this->buttons.empty()) {
        for (auto& it : this->buttons)
            it.second->update(this->mousePosWindow);

        if (this->buttons["EXIT_BTN"]->isPressed() && this->getKeytime())
            this->endState();

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
    if (this->debugMode) {
        this->dString_Stream
            << "\nver:\t" << CMAKE_PROJECT_VERSION
            << "\nFPS delta:\t" << 1 / delta_time
            << "\nFPS Clock:\t" << FPS::getFPS()
            << "\nFPS limit:\t" << this->IstateData->gfxSettings->_struct.frameRateLimit
            << "\nDelta Time:\t" << delta_time
            << "\nResolution:\t" << this->IstateData->sWindow->getSize().x << " x " << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing:\t" << this->IstateData->sWindow->getSettings().antialiasingLevel
            << "\nvSync:\t" << this->IstateData->gfxSettings->_struct.verticalSync
            << "\nMouse Pos:\t" << this->mousePosWindow.x << " x " << this->mousePosWindow.y
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
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }

    // update GUI
    this->backgrond_shapes[0].rotate(delta_time);
    this->backgrond_shapes[1].rotate(-delta_time);
}

void MainMenu::updateSounds(const float& delta_time)
{

    if (this->Isound.getStatus() == sf::Sound::Status::Stopped || this->Isound.getStatus() == sf::Sound::Status::Paused) {
        this->Isound.play();
    }
    this->Isound.setVolume(this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MASTER)
        * this->IvolumeManager->getCategoryVolume(SoundCategory::vol_MUSIC) / 100);
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
    if (this->debugMode)
        this->renderTexture.draw(this->dText);

    this->renderTexture.setView(this->renderTexture.getDefaultView());

    this->renderTexture.display();

    target.draw(this->renderSprite);
}