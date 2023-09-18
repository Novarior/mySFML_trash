#include "Core.h"

// build folders for app
/*
            -ROOT
            -Myapp.app
            -Config/
                -entitysdata.json
                -gameconfig.cfg
                -inventorydata.json
                -playerdata.json
                -Window.json
                -supported_keys.json
            -resourses/
                -fonts
                -sounds
                -sprites
                -textures

*/
void Core::initDirectories()
{
    // directory Config and resourses

    // make confing, resourses folder
    std::filesystem::create_directory("config");
    std::filesystem::create_directory("resourses");
    // print error if not created
    if (!std::filesystem::exists("config"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE CONFIG FOLDER" << std::endl;
    if (!std::filesystem::exists("resourses"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE resourses FOLDER" << std::endl;
    // make resourses , textures, sprites, sounds, fonts, folder
    std::filesystem::create_directory("resourses/textures");
    std::filesystem::create_directory("resourses/sprites");
    std::filesystem::create_directory("resourses/sounds");
    std::filesystem::create_directory("resourses/fonts");
    // print error if not created
    if (!std::filesystem::exists("resourses/textures"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE TEXTURES FOLDER" << std::endl;
    if (!std::filesystem::exists("resourses/sprites"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE SPRITES FOLDER" << std::endl;
    if (!std::filesystem::exists("resourses/sounds"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE SOUNDS FOLDER" << std::endl;
    if (!std::filesystem::exists("resourses/fonts"))
        std::cout << "ERROR::CORE::INITDIRECTORIES::FAILED TO CREATE FONTS FOLDER" << std::endl;
}

// initialisations root data and build first frame app
void Core::initVar()
{
    this->mWindow = NULL;
    if (!this->gfxSettings.loadFromFile("Config/window.json"))
        this->gfxSettings.saveToFile("Config/window.json");
}

void Core::initStateData()
{
    this->mStatedata.sWindow = this->mWindow;
    this->mStatedata.sStates = &this->mState;
    if (!this->mStatedata.font.loadFromFile(myConst::data_gameproces_font_path)) { }
    if (!this->mStatedata.debugFont.loadFromFile(myConst::data_debugfont_path)) { }
    this->mStatedata.supportedKeys = &this->supportedKeys;
    this->mStatedata.gfxSettings = &this->gfxSettings;
    this->mStatedata.grid_size = this->gfxSettings.gridSize;
    this->mStatedata.parser = this->parsJSON;
    this->mStatedata.characterSize_debug = mmath::calcCharSize(this->mWindow->getSize(), 150);
    this->mStatedata.characterSize_game_big = mmath::calcCharSize(this->mWindow->getSize(), 60);
    this->mStatedata.characterSize_game_medium = mmath::calcCharSize(this->mWindow->getSize(), 85);
    this->mStatedata.characterSize_game_small = mmath::calcCharSize(this->mWindow->getSize(), 100);
    this->mStatedata.reserGUI = false;
}

void Core::initKeyBinds()
{

    // init default keys
    this->supportedKeys["Escape"] = sf::Keyboard::Escape;
    this->supportedKeys["A"] = sf::Keyboard::A;
    this->supportedKeys["C"] = sf::Keyboard::C;
    this->supportedKeys["D"] = sf::Keyboard::D;
    this->supportedKeys["E"] = sf::Keyboard::E;
    this->supportedKeys["F"] = sf::Keyboard::F;
    this->supportedKeys["Q"] = sf::Keyboard::Q;
    this->supportedKeys["R"] = sf::Keyboard::R;
    this->supportedKeys["S"] = sf::Keyboard::S;
    this->supportedKeys["W"] = sf::Keyboard::W;
    this->supportedKeys["X"] = sf::Keyboard::X;
    this->supportedKeys["Z"] = sf::Keyboard::Z;
    this->supportedKeys["Space"] = sf::Keyboard::Space;
    this->supportedKeys["Tab"] = sf::Keyboard::Tab;
    this->supportedKeys["F1"] = sf::Keyboard::F1;
    this->supportedKeys["F2"] = sf::Keyboard::F2;
    this->supportedKeys["F3"] = sf::Keyboard::F3;
    // save default keys to file
    this->parsJSON->saveKeyBinds("Config/supported_keys.json", this->supportedKeys);
}

void Core::initState()
{
    this->mState.push(new MainMenu(&this->mStatedata));
}

void Core::initWindow()
{
    if (this->gfxSettings.fullscreen)
        this->mWindow = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen,
            this->gfxSettings.contextSettings);
    else
        this->mWindow = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);

    this->mWindow->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->mWindow->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
    this->mWindow->setKeyRepeatEnabled(false);
}

Core::Core()
{
    this->parsJSON = new mypars::parsJSON();
    this->initDirectories();
    this->initKeyBinds();
    this->initVar();
    this->initWindow();
    this->initStateData();
    this->initState();
}

Core::~Core()
{
    this->gfxSettings.saveToFile(myConst::config_window);
    delete this->parsJSON;

    while (!this->mState.empty()) {
        delete this->mState.top();
        this->mState.pop();
    }
    delete this->mWindow;
}

void Core::run()
{
    while (this->mWindow->isOpen()) {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}

void Core::update()
{
    // state update
    this->updateEventsWindow();

    if (!this->mState.empty()) {
        if (this->mWindow->hasFocus()) {
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

void Core::updateEventsWindow()
{
    while (this->mWindow->pollEvent(this->mEvents))
        if (this->mEvents.type == sf::Event::Closed)
            this->mWindow->close();
}

void Core::render()
{
    this->mWindow->clear();

    if (!this->mState.empty())
        this->mState.top()->render(*this->mWindow);

    this->mWindow->display();
}

void Core::updateDeltaTime()
{
    this->deltaTime = 0;
    this->deltaTime = this->deltaClock.restart().asSeconds();
}