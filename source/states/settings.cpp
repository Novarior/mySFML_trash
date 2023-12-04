#include "settings.hpp"

void SettingsState::initVariables()
{
    // init variables
    // init parser for some reason
    this->Iparser = this->IstateData->parser;
    // init video modes like all supported modes
    this->video_modes = sf::VideoMode::getFullscreenModes();
    // init framerates list
    this->framerates_list.push_back(30);
    this->framerates_list.push_back(60);
    this->framerates_list.push_back(90);
    this->framerates_list.push_back(120);
    // init antialiasing list
    this->antialiasing_list.push_back(0);
    this->antialiasing_list.push_back(2);
    this->antialiasing_list.push_back(4);
    this->antialiasing_list.push_back(8);
    this->antialiasing_list.push_back(16);
    // init vsync list
    this->vsync_list.push_back(0);
    this->vsync_list.push_back(1);
    // init fullcreen list
    this->fullscreen_list.push_back(0);
    this->fullscreen_list.push_back(1);
}

void SettingsState::initFonts()
{
    this->font = this->IstateData->font;
}

void SettingsState::initKeybinds()
{
    // init key escape like defoult back button
    this->Ikeybinds["KEY_BACK"] = this->IsupportedKeys->at("Escape");
}

void SettingsState::initGui()
{
    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->Iwindow->getSize().x),
        static_cast<float>(this->Iwindow->getSize().y)));
    // darkest blue color
    this->background.setFillColor(sf::Color(3, 3, 30, 100));
    //=====================================================================================================
    // exit gui button
    this->buttons["BACK_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 120, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Back", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 0, 0, 200), sf::Color(255, 0, 0, 250), sf::Color(255, 0, 0, 50), 0);
    // apply gui button
    // set "apply" button position litle bit left from "back" button
    this->buttons["APPLY_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 240, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Apply", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(0, 255, 0, 200), sf::Color(0, 255, 0, 250), sf::Color(0, 255, 0, 50), 1);

    //=====================================================================================================
    //=====================================   RESOLUTION    ===============================================
    //=====================================================================================================

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    for (auto& i : this->video_modes) {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }

    // chek current resolution and set it to selector like active element
    int id = 0;
    for (int i = 0; i < modes_str.size(); i++)
        if (modes_str[i] == std::to_string(this->IstateData->gfxSettings->resolution.width) + 'x' + std::to_string(this->IstateData->gfxSettings->resolution.height)) {
            id = i;
            break;
        }

    // init selector with video modes
    this->selector_resolutions = new gui::Selector(
        sf::Vector2f(mmath::p2pX(30, this->Iwindow->getSize().x), mmath::p2pX(10, this->Iwindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)),
        font, this->IstateData->characterSize_game_medium, modes_str.data(), modes_str.size(), id);

    //=====================================================================================================
    //=========================================   FPS    ==================================================
    //=====================================================================================================

    // int vector with fps limit
    std::vector<std::string> fps_limits;
    for (auto& x : this->framerates_list)
        fps_limits.push_back(std::to_string(x));

    // check current fps limit and set it to selector like active element
    int fpls = 0;
    for (int i = 0; i < fps_limits.size(); i++)
        if (fps_limits[i] == std::to_string(this->IstateData->gfxSettings->frameRateLimit)) {
            fpls = i;
            break;
        }

    // init selector resolution
    this->selector_framerates = new gui::Selector(
        sf::Vector2f(mmath::p2pX(30, this->Iwindow->getSize().x), mmath::p2pX(30, this->Iwindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)),
        font, this->IstateData->characterSize_game_medium, fps_limits.data(), fps_limits.size(), fpls);

    //=====================================================================================================
    //===================================   ANTIALIASING     ==============================================
    //=====================================================================================================

    // init antialiasing list
    std::vector<std::string> antialiasing_list;
    antialiasing_list.push_back("OFF");
    antialiasing_list.push_back("x2");
    antialiasing_list.push_back("x4");
    antialiasing_list.push_back("x8");
    antialiasing_list.push_back("x16");

    // check current antialiasing and set it to selector like active element
    unsigned AAS = 0;
    for (int i = 0; i < antialiasing_list.size(); i++)
        if (antialiasing_list[i] == "x" + std::to_string(this->IstateData->gfxSettings->contextSettings.antialiasingLevel)) {
            AAS = i;
            break;
        }

    // init selector antialiasing
    this->selector_antialiasing = new gui::Selector(
        sf::Vector2f(mmath::p2pX(30, this->Iwindow->getSize().x), mmath::p2pX(25, this->Iwindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)),
        font, this->IstateData->characterSize_game_medium, antialiasing_list.data(), antialiasing_list.size(), AAS);

    //=====================================================================================================
    //=======================================   VSYNC    ==================================================
    //=====================================================================================================

    // init vsync list
    std::vector<std::string> vsync_list;
    vsync_list.push_back("OFF");
    vsync_list.push_back("ON");

    // check current vsync and set it to selector like active element
    unsigned vs = 0;
    for (int i = 0; i < vsync_list.size(); i++)
        if (vsync_list[i] == (this->IstateData->gfxSettings->verticalSync ? "ON" : "OFF")) {
            vs = i;
            break;
        }

    // init selector vsync
    this->selector_vsync = new gui::Selector(
        sf::Vector2f(mmath::p2pX(30, this->Iwindow->getSize().x), mmath::p2pX(20, this->Iwindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)),
        font, this->IstateData->characterSize_game_medium, vsync_list.data(), vsync_list.size(), vs);

    //=====================================================================================================
    //===================================   FULLSCREEN    =================================================
    //=====================================================================================================

    // init fullscreen list
    std::vector<std::string> fullscreen_list;
    fullscreen_list.push_back("Windowed");
    fullscreen_list.push_back("Fullscreen");

    // check current fullscreen and set it to selector like active element
    unsigned fs = 0;
    for (int i = 0; i < fullscreen_list.size(); i++)
        if (fullscreen_list[i] == (this->IstateData->gfxSettings->fullscreen ? "Fullscreen" : "Windowed")) {
            fs = i;
            break;
        }

    // init selector fullscreen
    this->selector_fullscreen = new gui::Selector(
        sf::Vector2f(mmath::p2pX(30, this->Iwindow->getSize().x), mmath::p2pX(15, this->Iwindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)),
        font, this->IstateData->characterSize_game_medium, fullscreen_list.data(), fullscreen_list.size(), fs);

    //=====================================================================================================
    //=======================================   TEXT    ===================================================
    //=====================================================================================================

    // init shapes for textbox
    for (int i = 0; i < 5; i++) {
        this->text_shapes.push_back(sf::RectangleShape());
        this->text_shapes[i].setFillColor(sf::Color::Transparent);
        this->text_shapes[i].setOutlineColor(sf::Color::Transparent);
        this->text_shapes[i].setOutlineThickness(-1);
        this->text_shapes[i].setPosition(sf::Vector2f(
            mmath::p2pX(5, this->Iwindow->getSize().x),
            mmath::p2pX(5 + (i * 5), this->Iwindow->getSize().y) + mmath::p2pX(5, this->Iwindow->getSize().y)));
        this->text_shapes[i].setSize(sf::Vector2f(mmath::p2pX(20, this->Iwindow->getSize().x), mmath::p2pX(5, this->Iwindow->getSize().y)));
    }

    // init text for settings
    for (int x = 0; x < 5; x++)
        this->settings_list.push_back(sf::Text());

    this->settings_list[0].setString("Resolution");
    this->settings_list[1].setString("Fullscreen");
    this->settings_list[2].setString("Vsync");
    this->settings_list[3].setString("Antialiasing");
    this->settings_list[4].setString("Framerate limit");

    for (int x = 0; x < 5; x++) {
        this->settings_list[x].setFillColor(sf::Color::White);
        this->settings_list[x].setFont(this->font);
        this->settings_list[x].setCharacterSize(this->IstateData->characterSize_game_medium);
        this->settings_list[x].setPosition(sf::Vector2f(
            this->text_shapes[x].getPosition().x + (this->text_shapes[x].getGlobalBounds().width / 2) - (this->settings_list[x].getGlobalBounds().width / 2),
            this->text_shapes[x].getPosition().y + (this->text_shapes[x].getGlobalBounds().height / 2) - (this->settings_list[x].getGlobalBounds().height / 2)));
    }
}

void SettingsState::resetGui()
{
    // reser to new resolution and save it to file
    // reset gui
    this->IstateData->gfxSettings->resolution = this->video_modes[this->selector_resolutions->getActiveElementID()];
    this->IstateData->gfxSettings->frameRateLimit = this->framerates_list[this->selector_framerates->getActiveElementID()];
    this->IstateData->gfxSettings->contextSettings.antialiasingLevel = this->antialiasing_list[this->selector_antialiasing->getActiveElementID()];
    this->IstateData->gfxSettings->fullscreen = this->fullscreen_list[this->selector_fullscreen->getActiveElementID()];
    this->IstateData->gfxSettings->verticalSync = this->vsync_list[this->selector_vsync->getActiveElementID()];

    // reset window
    if (this->IstateData->gfxSettings->fullscreen)
        this->Iwindow->create(this->IstateData->gfxSettings->resolution, this->IstateData->gfxSettings->title, sf::Style::Fullscreen, this->IstateData->gfxSettings->contextSettings);
    else
        this->Iwindow->create(this->IstateData->gfxSettings->resolution, this->IstateData->gfxSettings->title, sf::Style::Titlebar | sf::Style::Close, this->IstateData->gfxSettings->contextSettings);
    this->Iwindow->setFramerateLimit(this->framerates_list[this->selector_framerates->getActiveElementID()]);

    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();
    this->IstateData->reserGUI = true;

    // delete selector
    delete this->selector_vsync;
    delete this->selector_framerates;
    delete this->selector_fullscreen;
    delete this->selector_resolutions;
    delete this->selector_antialiasing;

    this->IstateData->gfxSettings->saveToFile(get_app_dir());

    this->reCaclulateCharacterSize();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initGui();
    this->initKeybinds();
}

SettingsState::~SettingsState()
{
    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();

    // delete selector
    delete this->selector_vsync;
    delete this->selector_framerates;
    delete this->selector_fullscreen;
    delete this->selector_resolutions;
    delete this->selector_antialiasing;
}

// Functions
void SettingsState::updateInput(const float& delta_time)
{
    // update esc key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_BACK"))) && this->getKeytime())
        this->endState();
}

void SettingsState::updateGui(const float& delta_time)
{
    // update all gui in the state and handle functionality
    for (auto& it : this->buttons)
        it.second->update(this->mousePosWindow);
    // quit the game
    if (this->buttons["BACK_BTN"]->isPressed() && this->getKeytime())
        this->endState();
    // apply settings
    if (this->buttons["APPLY_BTN"]->isPressed() && this->getKeytime())
        this->resetGui();
    // update selector
    this->selector_vsync->update(delta_time, this->mousePosWindow);
    this->selector_framerates->update(delta_time, this->mousePosWindow);
    this->selector_fullscreen->update(delta_time, this->mousePosWindow);
    this->selector_resolutions->update(delta_time, this->mousePosWindow);
    this->selector_antialiasing->update(delta_time, this->mousePosWindow);

    if (this->debugMode) {
        this->dString_Stream
            << "Ver: " << CMAKE_PROJECT_VERSION
            << "\nFPS:\t" << 1 / delta_time
            << "\nResolution: " << this->IstateData->sWindow->getSize().x << "x" << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing: " << this->IstateData->gfxSettings->contextSettings.antialiasingLevel
            << "\nvSync: " << this->IstateData->gfxSettings->verticalSync
            << "\nFullscreen: " << this->IstateData->gfxSettings->fullscreen
            << "\nSize of state: " << sizeof(*this) << " bytes"
            << "\nkeytime: " << this->Ikeytime
            << "\nMouse pos: " << this->mousePosWindow.x << " " << this->mousePosWindow.y;
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void SettingsState::update(const float& delta_time)
{
    this->updateMousePositions();
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateGui(delta_time);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
    // render all gui in the state
    for (auto& bt : this->buttons)
        bt.second->render(target);
    // draw text
    for (auto& t : this->settings_list)
        target.draw(t);
    // draw selector
    this->selector_resolutions->render(target);
    this->selector_framerates->render(target);
    this->selector_antialiasing->render(target);
    this->selector_vsync->render(target);
    this->selector_fullscreen->render(target);
    // debug
    // draw this->text_shapes
    for (auto& ts : this->text_shapes)
        target.draw(ts);
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);
    this->renderGui(target);

    target.draw(this->dText);
}