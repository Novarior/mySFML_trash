#include "Core.h"
#include "LOGGER.hpp"
#include "locTexts/helperText.hpp"
#include "myConst.h"
#include <nl_types.h>

#if __APPLE__
void Core::initDirectories()
{ // check if app directory exists
    if (ApplicationsFunctions::checkAppDirectoryExists())
        Logger::log("App directory not exists, Create...", "Core::initDirectories()");
}
#endif

// initialisations root data and build first frame app
void Core::initVar()
{
    this->mWindow = NULL;

    if (!this->gfxSettings.loadFromFile())
        this->gfxSettings.saveToFile();
}

void Core::initStateData()
{
    this->mStatedata.sWindow = this->mWindow;
    this->mStatedata.sStates = &this->mState;
    if (!this->mStatedata.font.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::data_gameproces_font_path_3))) {
        Logger::log("ERROR::GAMEPROCES::COULD NOT LOAD TO FILE: " + std::string(ApplicationsFunctions::get_resources_dir() + myConst::data_gameproces_font_path_3), "Core::initStateData()");
    }
    if (!this->mStatedata.debugFont.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::data_debugfont_path))) {
        Logger::log("ERROR::DEBUG::COULD NOT LOAD TO FILE: " + std::string(ApplicationsFunctions::get_resources_dir() + myConst::data_debugfont_path), "Core::initStateData()");
    }
    this->mStatedata.supportedKeys = &this->supportedKeys;
    this->mStatedata.gfxSettings = &this->gfxSettings;
    this->mStatedata.grid_size = this->gfxSettings._struct.gridSize;
    this->mStatedata.characterSize_debug = mmath::calcCharSize(this->mWindow->getSize(), 150);
    this->mStatedata.characterSize_game_big = mmath::calcCharSize(this->mWindow->getSize(), 60);
    this->mStatedata.characterSize_game_medium = mmath::calcCharSize(this->mWindow->getSize(), 85);
    this->mStatedata.characterSize_game_small = mmath::calcCharSize(this->mWindow->getSize(), 100);
    this->mStatedata.reserGUI = false;
    this->mStatedata.sEvent = &this->mEvents;
}

void Core::initKeyBinds()
{ // init default keys
    supportedKeys["Escape"] = sf::Keyboard::Scancode::Escape;
    supportedKeys["A"] = sf::Keyboard::Scancode::A;
    supportedKeys["C"] = sf::Keyboard::Scancode::C;
    supportedKeys["D"] = sf::Keyboard::Scancode::D;
    supportedKeys["E"] = sf::Keyboard::Scancode::E;
    supportedKeys["F"] = sf::Keyboard::Scancode::F;
    supportedKeys["Q"] = sf::Keyboard::Scancode::Q;
    supportedKeys["R"] = sf::Keyboard::Scancode::R;
    supportedKeys["S"] = sf::Keyboard::Scancode::S;
    supportedKeys["W"] = sf::Keyboard::Scancode::W;
    supportedKeys["X"] = sf::Keyboard::Scancode::X;
    supportedKeys["Z"] = sf::Keyboard::Scancode::Z;
    supportedKeys["Space"] = sf::Keyboard::Scancode::Space;
    supportedKeys["Enter"] = sf::Keyboard::Scancode::Enter;
    supportedKeys["BackSpace"] = sf::Keyboard::Scancode::Backspace;
    supportedKeys["Slash"] = sf::Keyboard::Scancode::Slash;
    supportedKeys["Tab"] = sf::Keyboard::Scancode::Tab;
    supportedKeys["F1"] = sf::Keyboard::Scancode::F1;
    supportedKeys["F2"] = sf::Keyboard::Scancode::F2;
    supportedKeys["F3"] = sf::Keyboard::Scancode::F3;
    // save default keys to file
    ParserJson::saveKeyBinds(this->supportedKeys);
}

void Core::initState()
{
    this->mState.push(new MainMenu(&this->mStatedata));
}

void Core::initLocations()
{
    helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);
}

void Core::initWindow()
{
    mWindow = new sf::RenderWindow(
        gfxSettings._struct.resolution,
        gfxSettings._struct.title,
        sf::Style::Titlebar | sf::Style::Close,
        gfxSettings._struct.contextSettings);

    if (gfxSettings._struct.fullscreen && mWindow->isOpen()) {

        gfxSettings._struct._winResolutions = mWindow->getSize();
        mWindow->create(
            sf::VideoMode(gfxSettings._struct._winResolutions.x, gfxSettings._struct._winResolutions.y),
            gfxSettings._struct.title, sf::Style::Fullscreen, gfxSettings._struct.contextSettings);
    }

    mWindow->setFramerateLimit(gfxSettings._struct.frameRateLimit);
    mWindow->setVerticalSyncEnabled(gfxSettings._struct.verticalSync);
    mWindow->setKeyRepeatEnabled(false);
}

Core::Core()
{
    this->initDirectories();
    this->initKeyBinds();
    this->initVar();
    this->initWindow();
    this->initStateData();
    this->initLocations();
    this->initState();

    FPS::reset();
    Logger::log("Core Inited", "Core::Core()");
}

Core::~Core()
{
    this->gfxSettings.saveToFile();

    while (!this->mState.empty()) {
        delete this->mState.top();
        this->mState.pop();
    }
    delete this->mWindow;
}

void Core::run()
{
    Logger::log("Start main loop", "Core::run()");

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
    while (this->mWindow->pollEvent(this->mEvents)) {
        if (this->mEvents.type == sf::Event::Closed)
            this->mWindow->close();

        if (this->mEvents.type == sf::Event::KeyPressed)
            if (this->mEvents.key.scancode)
                return;
    }
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
    FPS::update();
}