#include "settings.hpp"

void SettingsState::initVariables()
{
    // init variables
    // init video modes like all supported modes
    _video_modes = sf::VideoMode::getFullscreenModes();
    // init framerates list
    _gfxResource["GFX_FPS"] = std::vector<int> { 30, 60, 90, 120 };
    _gfxResource["GFX_ALL"] = std::vector<int> { 0, 2, 4, 8, 16 };
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

    // init page background
    _pageBackground.setSize(sf::Vector2f( // size of page background
        mmath::p2pX(60, this->Iwindow->getSize().x),
        mmath::p2pY(60, this->Iwindow->getSize().y)));
    _pageBackground.setPosition(sf::Vector2f( // position of page background
        mmath::p2pX(20, this->Iwindow->getSize().x),
        mmath::p2pY(20, this->Iwindow->getSize().y)));
    _pageBackground.setFillColor(sf::Color(140, 140, 140, 140));

    sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(16, window_size.x), mmath::p2pY(5, window_size.y));

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
    //=======================================   TEXT    ===================================================
    //=====================================================================================================

    // init shapes for textbox
    std::vector<std::string> settingsNames = { "Resolution", "Fullscreen", "Vsync", "Antialiasing", "Framerate limit" };

    for (int i = 0; i < 5; i++) {
        sf::RectangleShape shape;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Transparent);
        shape.setOutlineThickness(-1);
        shape.setPosition(sf::Vector2f(
            _pageBackground.getPosition().x,
            _pageBackground.getPosition().y + mmath::p2pX(5, window_size.y) + i * mmath::p2pX(5, window_size.y)));
        shape.setSize(sf::Vector2f(mmath::p2pX(20, window_size.x), mmath::p2pX(5, window_size.y)));
        sf::Text text;
        text.setString(settingsNames[i]);
        text.setFillColor(sf::Color::White);
        text.setFont(this->font);
        text.setCharacterSize(this->IstateData->characterSize_game_medium);
        text.setPosition(sf::Vector2f(
            shape.getPosition().x + (shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2),
            shape.getPosition().y + (shape.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2)));

        _graphic_list.push_back(std::make_pair(text, shape));
    }

    //=====================================================================================================
    //=====================================   RESOLUTION    ===============================================
    //=====================================================================================================

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    int index = 0;
    for (auto& i : _video_modes) {
        modes_str.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
        if (i.width == this->IstateData->gfxSettings->_struct.resolution.width
            && i.height == this->IstateData->gfxSettings->_struct.resolution.height)
            index = modes_str.size() - 1;
    }

    // init selector with video modes
    _selectors["SELEC_VMODE"] = std::make_unique<gui::Selector>(
        sf::Vector2f(_pageBackground.getPosition().x + mmath::p2pX(15, window_size.x), _pageBackground.getPosition().y + mmath::p2pX(5, window_size.y)),
        button_size, font, this->IstateData->characterSize_game_medium, modes_str.data(), modes_str.size(), index);

    //=====================================================================================================
    //===================================   FULLSCREEN    =================================================
    //=====================================================================================================

    // init fullscreen list
    std::vector<std::string> fullscreen_list;
    fullscreen_list.push_back("Windowed");
    fullscreen_list.push_back("Fullscreen");

    // check current fullscreen and set it to selector like active element
    unsigned fs = 0;
    for (; fs < fullscreen_list.size(); fs++)
        if (fullscreen_list[fs] == (this->IstateData->gfxSettings->_struct.fullscreen ? "Fullscreen" : "Windowed"))
            break;

    // init selector fullscreen
    _selectors["SELEC_FULLSCREEN"] = std::make_unique<gui::Selector>(
        sf::Vector2f(_pageBackground.getPosition().x + mmath::p2pX(15, window_size.x), _pageBackground.getPosition().y + mmath::p2pX(10, window_size.y)),
        button_size, font, this->IstateData->characterSize_game_medium, fullscreen_list.data(), fullscreen_list.size(), fs);

    //=====================================================================================================
    //=======================================   VSYNC    ==================================================
    //=====================================================================================================

    // init vsync list
    std::vector<std::string> vsync_list;
    vsync_list.push_back("OFF");
    vsync_list.push_back("ON");

    // check current vsync and set it to selector like active element
    unsigned vs = 0;
    for (; vs < vsync_list.size(); vs++)
        if (vsync_list[vs] == (this->IstateData->gfxSettings->_struct.verticalSync ? "ON" : "OFF"))
            break;

    // init selector vsync
    _selectors["SELEC_VSYNC"] = std::make_unique<gui::Selector>(
        sf::Vector2f(_pageBackground.getPosition().x + mmath::p2pX(15, window_size.x), _pageBackground.getPosition().y + mmath::p2pX(15, window_size.y)),
        button_size, font, this->IstateData->characterSize_game_medium, vsync_list.data(), vsync_list.size(), vs);

    //=====================================================================================================
    //===================================   ANTIALIASING     ==============================================
    //=====================================================================================================

    // init antialiasing list
    std::vector<std::string> antialiasing_list = { "OFF", "x2", "x4", "x8", "x16" };

    std::string currentAA = "x" + std::to_string(this->IstateData->gfxSettings->_struct.contextSettings.antialiasingLevel);
    auto aalit = std::find(antialiasing_list.begin(), antialiasing_list.end(), currentAA);
    unsigned AAS = (aalit != antialiasing_list.end()) ? std::distance(antialiasing_list.begin(), aalit) : 0;

    // init selector antialiasing
    _selectors["SELEC_AAL"] = std::make_unique<gui::Selector>(
        sf::Vector2f(_pageBackground.getPosition().x + mmath::p2pX(15, window_size.x), _pageBackground.getPosition().y + mmath::p2pX(20, window_size.y)),
        button_size, font, this->IstateData->characterSize_game_medium, antialiasing_list.data(), antialiasing_list.size(), AAS);

    //=====================================================================================================
    //=========================================   FPS    ==================================================
    //=====================================================================================================

    std::vector<std::string> fps_limits;
    std::transform(_gfxResource["GFX_FPS"].begin(), _gfxResource["GFX_FPS"].end(), std::back_inserter(fps_limits),
        [](const auto& x) { return std::to_string(x); });

    std::string currentFPS = std::to_string(this->IstateData->gfxSettings->_struct.frameRateLimit);
    auto fpsit = std::find(fps_limits.begin(), fps_limits.end(), currentFPS);
    int fpls = (fpsit != fps_limits.end()) ? std::distance(fps_limits.begin(), fpsit) : 0;

    _selectors["SELEC_FPS"] = std::make_unique<gui::Selector>(
        sf::Vector2f(_pageBackground.getPosition().x + mmath::p2pX(15, window_size.x), _pageBackground.getPosition().y + mmath::p2pX(25, window_size.y)),
        button_size, font, this->IstateData->characterSize_game_medium, fps_limits.data(), fps_limits.size(), fpls);

    //=====================================================================================================
    //=====================================   KEY BINDS    ================================================
    //=====================================================================================================

    // init text of the keybinds

    sf::Text text;
    text.setFont(this->IstateData->font);
    text.setCharacterSize(24);

    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(200, 200, 200, 150));

    int i = 0;
    float i2 = i;
    for (const auto& keybind : *this->IstateData->supportedKeys) {
        text.setString(keybind.first + ": " + std::to_string(keybind.second));

        float posX = mmath::p2pX(12.f * (i % 3), window_size.x);
        float posY = mmath::p2pY(40.f, window_size.y) + mmath::p2pY(3.f * (i2 / 3), window_size.y);
        text.setPosition(posX, posY);

        rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
        rectangle.setPosition(text.getPosition());

        _keybindText.push_back(text);
        _keybindBackground.push_back(rectangle);
        i++;
        i2 = i;
    }

    //=====================================================================================================
    //=====================================   AUDIO SETTINGS    ===========================================
    //=====================================================================================================

    {

        _sound_SliderMap[SoundCategory::vol_MASTER] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(15, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_MASTER), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_SFX] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(20, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_SFX), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_MUSIC] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(25, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_MUSIC), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_AMBIENT] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(30, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_AMBIENT), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_PLAYER] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(35, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_PLAYER), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_ENTITY] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(40, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_ENTITY), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_UI] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(45, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_UI), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_DIALOGUE] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(50, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_DIALOGUE), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_FOLEY] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(55, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_FOLEY), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_WEAPON] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(60, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pX(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_WEAPON), 0, 100, 1);

        _sound_SliderMap[SoundCategory::vol_ENVIRONMENT] = std::make_unique<gui::SliderInt>(
            sf::Vector2f(mmath::p2pX(30, window_size.x), mmath::p2pX(65, window_size.y)),
            sf::Vector2f(mmath::p2pX(25, window_size.x), mmath::p2pY(5, window_size.y)),
            font, this->IvolumeManager.get()->getCategoryVolume(SoundCategory::vol_ENVIRONMENT), 0, 100, 1);
    }
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

    _keybindBackground.clear();
    _keybindBackground.clear();
    _sound_SliderMap.clear();
    _graphic_list.clear();
    _pageButtons.clear();
    _keybindText.clear();
    _pageButtons.clear();
    _video_modes.clear();
    _gfxResource.clear();
    _keybindText.clear();
    _selectors.clear();

    // init variables
    this->initVariables();

    // init fonts
    this->IstateData->gfxSettings->saveToFile(sAppFunctions::getDocumentsAppFolder());

    this->reCaclulateCharacterSize();

    this->initGui();
}

void SettingsState::initPageLayout()
{
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
    , page(settingPage::GRAPHICS)
    , pageName("GRAPHICS")
{ // init variables
    this->initPageLayout();
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

    // clear keybind background
    _keybindBackground.clear();

    // clear video modes
    _video_modes.clear();

    // clear gfx resource
    _gfxResource.clear();

    // clear myTest
    _sound_SliderMap.clear();

    // clear text
    _graphic_list.clear();
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
    for (auto& it : _sound_SliderMap)
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
            << "Ver: " << CMAKE_PROJECT_VERSION << "\nFPS:\t" << 1 / delta_time
            << "\nPage: " << pageName << " " << static_cast<int>(this->page)
            << "\nSliders: "
            << "\n\tMASTER: " + std::to_string(_sound_SliderMap[SoundCategory::vol_MASTER].get()->getValue())
            << "\n\tSFX: " + std::to_string(_sound_SliderMap[SoundCategory::vol_SFX].get()->getValue())
            << "\n\tMUSIC: " + std::to_string(_sound_SliderMap[SoundCategory::vol_MUSIC].get()->getValue())
            << "\n\tAMBIENT: " + std::to_string(_sound_SliderMap[SoundCategory::vol_AMBIENT].get()->getValue())
            << "\n\tPLAYER: " + std::to_string(_sound_SliderMap[SoundCategory::vol_PLAYER].get()->getValue())
            << "\n\tENTITY: " + std::to_string(_sound_SliderMap[SoundCategory::vol_ENTITY].get()->getValue())
            << "\n\tUI: " + std::to_string(_sound_SliderMap[SoundCategory::vol_UI].get()->getValue())
            << "\n\tDIALOGUE: " + std::to_string(_sound_SliderMap[SoundCategory::vol_DIALOGUE].get()->getValue())
            << "\n\tFOLEY: " + std::to_string(_sound_SliderMap[SoundCategory::vol_FOLEY].get()->getValue())
            << "\n\tWEAPON: " + std::to_string(_sound_SliderMap[SoundCategory::vol_WEAPON].get()->getValue())
            << "\n\tENVIRONMENT: " + std::to_string(_sound_SliderMap[SoundCategory::vol_ENVIRONMENT].get()->getValue())
            << "\nVideo modes: " << _video_modes.size()
            << "\nVideo mode: "
            << std::to_string(this->IstateData->gfxSettings->_struct.resolution.width)
            << std::to_string(this->IstateData->gfxSettings->_struct.resolution.height)
            << "\nFramerate limit: " + std::to_string(this->IstateData->gfxSettings->_struct.frameRateLimit)
            << "\nResolution: " << this->IstateData->sWindow->getSize().x << "x" << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing: " << this->IstateData->gfxSettings->_struct.contextSettings.antialiasingLevel
            << "\nvSync: " << this->IstateData->gfxSettings->_struct.verticalSync
            << "\nFullscreen: " << this->IstateData->gfxSettings->_struct.fullscreen
            << "\nSize of state: " << sizeof(*this) << " bytes"
            << "\nkeytime: " << this->Ikeytime
            << "\nMouse pos: " << this->mousePosWindow.x << " " << this->mousePosWindow.y
            << "\narrays info:"
            << "\n\tvideo_modes: " << _video_modes.size()
            << "\n\tgfxResource: " << _gfxResource.size()
            << "\n\tkeybindText: " << _keybindText.size()
            << "\n\tkeybindBackground: " << _keybindBackground.size()
            << "\n\tpageButtons: " << _pageButtons.size()
            << "\n\tkeybindText: " << _keybindText.size()
            << "\n\tselectors: " << _selectors.size()
            << "\n\tgraphic_list: " << _graphic_list.size()
            << "\n\tsound_SliderMap: " << _sound_SliderMap.size();

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
        for (auto& it : _graphic_list)
            target.draw(it.first);
        // draw selector
        for (auto& it : _selectors)
            it.second->render(target);
        break;
    case settingPage::CONTROLS:
        // draw _text_shapes

        // draw shapes for keybinds like background layer
        // FIXME: fix layering of keybinds
        for (auto& it : _keybindBackground)
            target.draw(it);

        for (const auto& text : _keybindText)
            target.draw(text);
        break;
    case settingPage::AUDIO:
        // TODO add content
        // draw _sound_SliderMap
        for (auto& it : _sound_SliderMap)
            it.second->render(target);

        break;
    case settingPage::ECT:
        // TODO add content
        break;
    default:
        break;
    }
}
void SettingsState::renderPageLayout(sf::RenderTarget& target) // Render page layout
{
    // render page layout
    target.draw(_pageBackground);
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);

    this->renderPageLayout(target);
    this->renderGui(target);

    if (this->debugMode)
        target.draw(this->dText);
}