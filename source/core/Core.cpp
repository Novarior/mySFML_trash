#include "Core.h"
#include "../locTexts/helperText.hpp"
#include "LOGGER.hpp"
#include "myConst.h"

#if __APPLE__
void Core::initDirectories()
{ // check if app directory exists
    if (ApplicationsFunctions::checkAppDirectoryExists())
        Logger::logStatic("App directory not exists, Create...", "Core::initDirectories()");
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
    this->mStatedata.sd_Window = this->mWindow;
    this->mStatedata.sd_States = &this->mState;
    if (!this->mStatedata.sd_font.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_gameproces_font_path_3))) {
        Logger::logStatic("ERROR::GAMEPROCES::COULD NOT LOAD TO FILE: " + std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_gameproces_font_path_3), "Core::initStateData()");
    }
    if (!this->mStatedata.sd_debugFont.loadFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_debugfont_path))) {
        Logger::logStatic("ERROR::DEBUG::COULD NOT LOAD TO FILE: " + std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_debugfont_path), "Core::initStateData()");
    }
    this->mStatedata.sd_supportedKeys = &this->supportedKeys;
    this->mStatedata.sd_gfxSettings = &this->gfxSettings;
    this->mStatedata.sd_gridSize = this->gfxSettings._struct.gridSize;
    this->mStatedata.sd_characterSize_debug = mmath::calcCharSize(this->mWindow->getSize(), 150);
    this->mStatedata.sd_characterSize_game_big = mmath::calcCharSize(this->mWindow->getSize(), 60);
    this->mStatedata.sd_characterSize_game_medium = mmath::calcCharSize(this->mWindow->getSize(), 85);
    this->mStatedata.sd_characterSize_game_small = mmath::calcCharSize(this->mWindow->getSize(), 100);
    this->mStatedata.reserGUI = false;
    this->mStatedata.sd_Event = &this->mEvents;

    this->mStatedata.sd_volumeManager = std::shared_ptr<VolumeManager>(new VolumeManager());

#if __MDEBUG__ == 1
    // logger moment

    // check if window is not null
    if (!this->mStatedata.sd_Window)
        Logger::logStatic("ERROR::WINDOW::NOT INITED", "Core::initStateData()", logType::ERROR);

    // check if states is not empty or null idk
    if (!this->mStatedata.sd_States->empty())
        Logger::logStatic("ERROR::STATES::NOT INITED", "Core::initStateData()", logType::ERROR);

#endif
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
    supportedKeys["1"] = sf::Keyboard::Scancode::Num1;
    supportedKeys["2"] = sf::Keyboard::Scancode::Num2;
    supportedKeys["3"] = sf::Keyboard::Scancode::Num3;
    supportedKeys["4"] = sf::Keyboard::Scancode::Num4;
    supportedKeys["5"] = sf::Keyboard::Scancode::Num5;
    supportedKeys["6"] = sf::Keyboard::Scancode::Num6;
    supportedKeys["7"] = sf::Keyboard::Scancode::Num7;
    supportedKeys["8"] = sf::Keyboard::Scancode::Num8;
    supportedKeys["9"] = sf::Keyboard::Scancode::Num9;
    supportedKeys["0"] = sf::Keyboard::Scancode::Num0;
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

#if __MDEBUG__ == 1
    // logger moment with key binds
    Logger::logStatic("Key binds inited", "Core::initKeyBinds()");

    // log all keys
    for (auto& i : supportedKeys)
        Logger::logStatic("Key: " + i.first + " Value: " + std::to_string(i.second), "Core::initKeyBinds()");

#endif
}

void Core::initState()
{
    this->mState.push(new MainMenu(&this->mStatedata));

#if __MDEBUG__ == 1
    // logger moment with states
    Logger::logStatic("State inited", "Core::initState()");
    Logger::logStatic("State size: " + std::to_string(this->mState.size()), "Core::initState()");
#endif
}

void Core::initLocations()
{
    helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);

    // debuggg
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

#if __MDEBUG__ == 1
    Logger::logStatic("Core Inited", "Core::Core()");
#endif
}

Core::~Core()
{
    this->gfxSettings.saveToFile();

    while (!this->mState.empty()) {
        delete this->mState.top();
        this->mState.pop();
    }
    delete this->mWindow;

#if __MDEBUG__ == 1
    // logger moment
    Logger::logStatic("Core Delete...", "Core::~Core()");

    if (this->mState.empty())
        Logger::logStatic("State is empty", "Core::~Core()");
    else
        Logger::logStatic("State is not empty... mem leaked", "Core::~Core()");

    if (this->mWindow == NULL)
        Logger::logStatic("Window is not null", "Core::~Core()");
    else
        Logger::logStatic("Window is null... mem leaked", "Core::~Core()");

    Logger::logStatic("Core Deleted", "Core::~Core()");
#endif
}

void Core::run()
{
    Logger::logStatic("Start main loop", "Core::run()");

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