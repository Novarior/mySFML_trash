#include "settings.hpp"

void SettingsState::initVariables()
{
    // init variables
    // init video modes like all supported modes
    this->video_modes = sf::VideoMode::getFullscreenModes();
    // init framerates list
    _gfxResource["GFX_FPS"] = std::vector<int> { 30, 60, 90, 120 };
    _gfxResource["GFX_AAL"] = std::vector<int> { 0, 2, 4, 8, 16 };
    _gfxResource["GFX_VSYNC"] = std::vector<int> { 0, 1 };
    _gfxResource["GFX_FULLSCREEN"] = std::vector<int> { 0, 1 };
}

void SettingsState::initFonts()
{
    this->font = this->IstateData->font;
}

void SettingsState::initKeybinds()
{
    // init key escape like defoult back button
    this->Ikeybinds["KEY_BACK"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
}

void SettingsState::initGui()
{
    //
    sf::Vector2u window_size = this->Iwindow->getSize();

    // init background
    this->background.setSize(sf::Vector2f(window_size.x, window_size.y));
    // darkest blue color
    this->background.setFillColor(sf::Color(3, 3, 30, 100));
    //=====================================================================================================
    // exit gui button
    this->buttons["BACK_BTN"] = new gui::Button(sf::Vector2f(window_size.x - 120, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Back", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 0, 0, 200), sf::Color(255, 0, 0, 250), sf::Color(255, 0, 0, 50), 0);
    // apply gui button
    // set "apply" button position litle bit left from "back" button
    this->buttons["APPLY_BTN"] = new gui::Button(sf::Vector2f(window_size.x - 240, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Apply", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(0, 255, 0, 200), sf::Color(0, 255, 0, 250), sf::Color(0, 255, 0, 50), 1);

    //=====================================================================================================
    //=====================================   RESOLUTION    ===============================================
    //=====================================================================================================

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    for (auto& i : this->video_modes)
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

    // chek current resolution and set it to selector like active element
    int id = 0;
    for (int i = 0; i < modes_str.size(); i++)
        if (modes_str[i] == std::to_string(this->IstateData->gfxSettings->_struct.resolution.width) + 'x' + std::to_string(this->IstateData->gfxSettings->_struct.resolution.height)) {
            id = i;
            break;
        }

    // init selector with video modes
    _selectors["SELEC_VMODE"] = std::make_unique<gui::Selector>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(10, window_size.y)),
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pX(5, window_size.y)),
        font, this->IstateData->characterSize_game_medium, modes_str.data(), modes_str.size(), id);

    //=====================================================================================================
    //=========================================   FPS    ==================================================
    //=====================================================================================================

    // int vector with fps limit
    std::vector<std::string> fps_limits;
    for (auto& x : _gfxResource["GFX_FPS"])
        fps_limits.push_back(std::to_string(x));

    // check current fps limit and set it to selector like active element
    int fpls = 0;
    for (int i = 0; i < fps_limits.size(); i++)
        if (fps_limits[i] == std::to_string(this->IstateData->gfxSettings->_struct.frameRateLimit)) {
            fpls = i;
            break;
        }

    // init selector resolution
    _selectors["SELEC_FPS"] = std::make_unique<gui::Selector>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(30, window_size.y)),
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pX(5, window_size.y)),
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
        if (antialiasing_list[i] == "x" + std::to_string(this->IstateData->gfxSettings->_struct.contextSettings.antialiasingLevel)) {
            AAS = i;
            break;
        }

    // init selector antialiasing
    _selectors["SELEC_AAL"] = std::make_unique<gui::Selector>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(25, window_size.y)),
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pX(5, window_size.y)),
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
        if (vsync_list[i] == (this->IstateData->gfxSettings->_struct.verticalSync ? "ON" : "OFF")) {
            vs = i;
            break;
        }

    // init selector vsync
    _selectors["SELEC_VSYNC"] = std::make_unique<gui::Selector>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(20, window_size.y)),
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pX(5, window_size.y)),
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
        if (fullscreen_list[i] == (this->IstateData->gfxSettings->_struct.fullscreen ? "Fullscreen" : "Windowed")) {
            fs = i;
            break;
        }

    // init selector fullscreen
    _selectors["SELEC_FULLSCREEN"] = std::make_unique<gui::Selector>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(15, window_size.y)),
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pX(5, window_size.y)),
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
            mmath::p2pX(5, window_size.x),
            mmath::p2pX(5 + (i * 5), window_size.y) + mmath::p2pX(5, window_size.y)));
        this->text_shapes[i].setSize(sf::Vector2f(mmath::p2pX(20, window_size.x), mmath::p2pX(5, window_size.y)));
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

    //=====================================================================================================
    //=====================================   KEY BINDS    ================================================
    //=====================================================================================================

    // init keybinds text
    sf::Text text;
    text.setFont(this->IstateData->font); // Set the font you want to use
    text.setCharacterSize(24); // Set the font size

    sf::RectangleShape rectangle; // Create a rectangle for background
    rectangle.setFillColor(sf::Color(200, 200, 200, 150)); // Set the rectangle color to semi-transparent black

    int i = 0;
    for (const auto& keybind : *this->IstateData->supportedKeys) {
        text.setString(keybind.first + ": " + std::to_string(keybind.second));
        text.setPosition(
            mmath::p2pX(12.f * (i % 3), window_size.x),
            mmath::p2pY(40.f, window_size.y) + mmath::p2pY(3 * (i / 3), window_size.y)); // Position the text in a grid

        rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height)); // Set the rectangle size to match the text
        rectangle.setPosition(text.getPosition()); // Position the rectangle at the same position as the text

        this->keybindText.push_back(text);
        this->keybindBackground.push_back(rectangle); // Add the rectangle to the vector
        i++;
    }
}

void SettingsState::resetGui()
{
    // reser to new resolution and save it to file
    // reset gui
    myGFXStruct gfx = this->IstateData->gfxSettings->getgfxsettings();
    
    gfx.resolution = this->video_modes[_selectors["SELEC_VMODE"]->getActiveElementID()];
    gfx.frameRateLimit = _gfxResource["GFX_FPS"][_selectors["SELEC_FPS"].get()->getActiveElementID()];
    gfx.contextSettings.antialiasingLevel = _gfxResource["GFX_ALL"][_selectors["SELEC_AAL"].get()->getActiveElementID()];
    gfx.fullscreen = _gfxResource["GFX_FULLSCREEN"][_selectors["SELEC_FULLSCREEN"]->getActiveElementID()];
    gfx.verticalSync = _gfxResource["GFX_VSYNC"][_selectors["SELEC_VSYNC"].get()->getActiveElementID()];

    this->IstateData->gfxSettings->setgfxsettings(gfx);


    // reset window
    if (gfx.fullscreen)
        this->Iwindow->create(gfx.resolution, gfx.title, sf::Style::Fullscreen, gfx.contextSettings);
    else
        this->Iwindow->create(gfx.resolution, gfx.title, sf::Style::Titlebar | sf::Style::Close, gfx.contextSettings);
    this->Iwindow->setFramerateLimit(gfx.frameRateLimit);

    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();
    this->IstateData->reserGUI = true;

    // delete selector
    _selectors.clear();

    this->IstateData->gfxSettings->saveToFile(sAppFunctions::getDocumentsAppFolder());

    this->reCaclulateCharacterSize();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{ // init variables
    this->initVariables();
    this->initFonts();
    this->initGui();
    this->initKeybinds();
    Logger::log("End initilization settings state", "SettingsState::SettingsState()", logType::INFO);
}

SettingsState::~SettingsState()
{
    Logger::log("SettingsState destructor", "SettingsState::~SettingsState()", logType::INFO);
    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();

    // delete selector
    _selectors.clear();
}

// Functions
void SettingsState::updateInput(const float& delta_time)
{
    // update esc key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_BACK"))) && this->getKeytime())
        this->endState();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->debugMode = !this->debugMode;
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

    for (auto& it : _selectors)
        it.second->update(delta_time, this->mousePosWindow);

    if (this->debugMode) {
        this->dString_Stream
            << "Ver: " << CMAKE_PROJECT_VERSION
            << "\nFPS:\t" << 1 / delta_time
            << "\nResolution: " << this->IstateData->sWindow->getSize().x << "x" << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing: " << this->IstateData->gfxSettings->_struct.contextSettings.antialiasingLevel
            << "\nvSync: " << this->IstateData->gfxSettings->_struct.verticalSync
            << "\nFullscreen: " << this->IstateData->gfxSettings->_struct.fullscreen
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
    for (auto& it : _selectors)
        it.second->render(target);
    // draw this->text_shapes
    for (auto& ts : this->text_shapes)
        target.draw(ts);

    for (auto& it : this->keybindBackground)
        target.draw(it);

    for (const auto& text : this->keybindText)
        target.draw(text);
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);
    this->renderGui(target);

    target.draw(this->dText);
}