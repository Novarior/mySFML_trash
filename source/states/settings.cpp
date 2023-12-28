#include "settings.hpp"

void SettingsState::initVariables()
{
    // init variables
    // init video modes like all supported modes
    _video_modes = sf::VideoMode::getFullscreenModes();
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
    this->Ikeybinds["KEY_BACK_PAGE"] = this->IsupportedKeys->at("Q");
    this->Ikeybinds["KEY_FORWARD_PAGE"] = this->IsupportedKeys->at("E");
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
    //=====================================   BUTTONS    ==================================================
    //=====================================================================================================

    // exit gui button
    _pageButtons["BACK_BTN"] = std::make_unique<gui::Button>(sf::Vector2f(window_size.x - 120, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Back", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 0, 0, 200), sf::Color(255, 0, 0, 250), sf::Color(255, 0, 0, 50), 0);
    // apply gui button
    // set "apply" button position litle bit left from "back" button
    _pageButtons["APPLY_BTN"] = std::make_unique<gui::Button>(sf::Vector2f(window_size.x - 240, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Apply", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(0, 255, 0, 200), sf::Color(0, 255, 0, 250), sf::Color(0, 255, 0, 50), 1);

    //=====================================================================================================
    //=====================================   PAGE BUTTONS    =============================================
    //=====================================================================================================

    // init page buttons
    // five buttons for five pages in one row
    // have to be in the same order as settingPage enum

    _pageButtons["PGB_AUDIO"] = std::make_unique<gui::Button>(
        sf::Vector2f(mmath::p2pX(5, window_size.x), mmath::p2pY(5, window_size.y)),
        sf::Vector2f(mmath::p2pX(10, window_size.x), mmath::p2pY(5, window_size.y)),
        this->IstateData->font, "Audio", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), 0);

    _pageButtons["PGB_GRAPHICS"] = std::make_unique<gui::Button>(
        sf::Vector2f(mmath::p2pX(15, window_size.x), mmath::p2pY(5, window_size.y)),
        sf::Vector2f(mmath::p2pX(10, window_size.x), mmath::p2pY(5, window_size.y)),
        this->IstateData->font, "Graphics", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), 0);

    _pageButtons["PGB_CONTROLS"] = std::make_unique<gui::Button>(
        sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pY(5, window_size.y)),
        sf::Vector2f(mmath::p2pX(10, window_size.x), mmath::p2pY(5, window_size.y)),
        this->IstateData->font, "Controls", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), 0);

    _pageButtons["PGB_ECT"] = std::make_unique<gui::Button>(
        sf::Vector2f(mmath::p2pX(35, window_size.x), mmath::p2pY(5, window_size.y)),
        sf::Vector2f(mmath::p2pX(10, window_size.x), mmath::p2pY(5, window_size.y)),
        this->IstateData->font, "Ect", this->IstateData->characterSize_game_medium,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), 0);

    //=====================================================================================================
    //=====================================   RESOLUTION    ===============================================
    //=====================================================================================================

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    for (auto& i : _video_modes)
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
        _text_shapes.push_back(sf::RectangleShape());
        _text_shapes[i].setFillColor(sf::Color::Transparent);
        _text_shapes[i].setOutlineColor(sf::Color::Transparent);
        _text_shapes[i].setOutlineThickness(-1);
        _text_shapes[i].setPosition(sf::Vector2f(
            mmath::p2pX(5, window_size.x),
            mmath::p2pX(5 + (i * 5), window_size.y) + mmath::p2pX(5, window_size.y)));
        _text_shapes[i].setSize(sf::Vector2f(mmath::p2pX(20, window_size.x), mmath::p2pX(5, window_size.y)));
    }

    // init text for settings
    for (int x = 0; x < 5; x++)
        _settings_list.push_back(sf::Text());

    _settings_list[0].setString("Resolution");
    _settings_list[1].setString("Fullscreen");
    _settings_list[2].setString("Vsync");
    _settings_list[3].setString("Antialiasing");
    _settings_list[4].setString("Framerate limit");

    for (int x = 0; x < 5; x++) {
        _settings_list[x].setFillColor(sf::Color::White);
        _settings_list[x].setFont(this->font);
        _settings_list[x].setCharacterSize(this->IstateData->characterSize_game_medium);
        _settings_list[x].setPosition(sf::Vector2f(
            _text_shapes[x].getPosition().x + (_text_shapes[x].getGlobalBounds().width / 2) - (_settings_list[x].getGlobalBounds().width / 2),
            _text_shapes[x].getPosition().y + (_text_shapes[x].getGlobalBounds().height / 2) - (_settings_list[x].getGlobalBounds().height / 2)));
    }

    //=====================================================================================================
    //=====================================   KEY BINDS    ================================================
    //=====================================================================================================

    // init text of the keybinds

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

        _keybindText.push_back(text);
        _keybindBackground.push_back(rectangle); // Add the rectangle to the vector
        i++;
    }

    //=====================================================================================================
    //=====================================   AUDIO SETTINGS    ===========================================
    //=====================================================================================================

    _myTest["SLIDER_TEST"] = std::make_unique<gui::SliderInt>(
        sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(15, window_size.y)),
        sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
        font, 20, 0, 100, 1);
}

void SettingsState::resetGui()
{
    // reser to new resolution and save it to file
    // reset gui
    myGFXStruct gfx = this->IstateData->gfxSettings->getgfxsettings();

    gfx.resolution = _video_modes[_selectors["SELEC_VMODE"]->getActiveElementID()];
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

    this->IstateData->reserGUI = true;

    // delete selector
    _selectors.clear();

    // clear page buttons
    _pageButtons.clear();

    this->IstateData->gfxSettings->saveToFile(sAppFunctions::getDocumentsAppFolder());

    this->reCaclulateCharacterSize();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
    , page(settingPage::GRAPHICS)
    , pageName("GRAPHICS")
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

    // delete selector
    _selectors.clear();

    // clear page buttons
    _pageButtons.clear();

    // clear keybinds
    _keybindText.clear();

    // clear text shapes
    _text_shapes.clear();

    // clear keybind background
    _keybindBackground.clear();

    // clear settings list
    _settings_list.clear();

    // clear video modes

    _video_modes.clear();

    // clear gfx resource
    _gfxResource.clear();

    // clear myTest
    _myTest.clear();
}

// Functions
void SettingsState::updateInput(const float& delta_time)
{
    // if escape is pressed, end state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_BACK"))) && this->getKeytime())
        this->endState();
    // if slash is pressed, swith debug mode
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->debugMode = !this->debugMode;

    // if key Q is pressed, swith page to left (back)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_BACK_PAGE"))) && this->getKeytime())
        this->page = static_cast<settingPage>((static_cast<int>(this->page) - 1 + static_cast<int>(settingPage::PAGE_COUNT)) % static_cast<int>(settingPage::PAGE_COUNT));

    // if key E is pressed, swith page to right (forward)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_FORWARD_PAGE"))) && this->getKeytime())
        this->page = static_cast<settingPage>((static_cast<int>(this->page) + 1) % static_cast<int>(settingPage::PAGE_COUNT));
}

void SettingsState::updateAudioPage(const float& delta_time) // Update audio page
{
    for (auto& it : _myTest)
        it.second->update(this->mousePosView);
}

void SettingsState::updateGraphicsPage(const float& delta_time) // Update graphics page
{
    // update selector
    for (auto& it : _selectors)
        it.second->update(delta_time, this->mousePosWindow);
}

void SettingsState::updateControlsPage(const float& delta_time) // Update controls page
{
}

void SettingsState::updateEctPage(const float& delta_time) // Update ect page
{
}

void SettingsState::updateGui(const float& delta_time)
{
    switch (page) {
    case settingPage::AUDIO:
        this->updateAudioPage(delta_time);
        break;
    case settingPage::GRAPHICS:
        this->updateGraphicsPage(delta_time);
        break;
    case settingPage::CONTROLS:
        this->updateControlsPage(delta_time);
        break;
    case settingPage::ECT:
        this->updateEctPage(delta_time);
        break;
    default:
        break;
    }

    // update page buttons
    for (auto& it : _pageButtons)
        it.second->update(this->mousePosWindow);

    // update current page when page button is pressed
    if (_pageButtons["PGB_GRAPHICS"]->isPressed() && this->getKeytime())
        this->page = settingPage::GRAPHICS;
    if (_pageButtons["PGB_CONTROLS"]->isPressed() && this->getKeytime())
        this->page = settingPage::CONTROLS;
    if (_pageButtons["PGB_AUDIO"]->isPressed() && this->getKeytime())
        this->page = settingPage::AUDIO;
    if (_pageButtons["PGB_ECT"]->isPressed() && this->getKeytime())
        this->page = settingPage::ECT;

    if (_pageButtons["BACK_BTN"]->isPressed() && this->getKeytime())
        this->endState();
    // apply settings
    if (_pageButtons["APPLY_BTN"]->isPressed() && this->getKeytime())
        this->resetGui();

    // update pageName
    std::map<settingPage, std::string> pageNames = {
        { settingPage::GRAPHICS, "GRAPHICS" },
        { settingPage::CONTROLS, "CONTROLS" },
        { settingPage::AUDIO, "AUDIO" },
        { settingPage::ECT, "ECT" }
    };

    pageName = pageNames.count(page) ? pageNames[page] : "ERR";

    if (this->debugMode) {
        this->dString_Stream
            << "Ver: " << CMAKE_PROJECT_VERSION
            << "\nFPS:\t" << 1 / delta_time
            << "\nPage: " << pageName << " " << static_cast<int>(this->page)
            << "\nSlider: " << _myTest["SLIDER_TEST"]->getValue()
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
    // render gui elements on some page
    //

    // render page buttons
    for (auto& it : _pageButtons)
        it.second->render(target);

    switch (this->page) {
    case settingPage::GRAPHICS:
        // draw text
        for (auto& t : _settings_list)
            target.draw(t);
        // draw selector
        for (auto& it : _selectors)
            it.second->render(target);
        break;
    case settingPage::CONTROLS:
        // draw _text_shapes
        for (auto& ts : _text_shapes)
            target.draw(ts);
        // draw shapes for keybinds like background layer
        // FIXME: fix layering of keybinds
        for (auto& it : _keybindBackground)
            target.draw(it);

        for (const auto& text : _keybindText)
            target.draw(text);
        break;
    case settingPage::AUDIO:
        // TODO add content
        // draw _myTest
        for (auto& it : _myTest)
            it.second->render(target);

        break;
    case settingPage::ECT:
        // TODO add content
        break;
    default:
        break;
    }
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);
    this->renderGui(target);

    if (this->debugMode)
        target.draw(this->dText);
}