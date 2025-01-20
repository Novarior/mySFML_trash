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
    if (!this->mStatedata.sd_font.openFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_gameproces_font_path_3))) {
        Logger::logStatic("ERROR::GAMEPROCES::COULD NOT LOAD TO FILE: " + std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_gameproces_font_path_3), "Core::initStateData()");
    }
    if (!this->mStatedata.sd_debugFont.openFromFile(std::string(ApplicationsFunctions::get_resources_dir() + myConst::fonts::data_debugfont_path))) {
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
    supportedKeys["Escape"] = static_cast<int>(sf::Keyboard::Scancode::Escape);
    supportedKeys["A"] = static_cast<int>(sf::Keyboard::Scancode::A);
    supportedKeys["C"] = static_cast<int>(sf::Keyboard::Scancode::C);
    supportedKeys["D"] = static_cast<int>(sf::Keyboard::Scancode::D);
    supportedKeys["E"] = static_cast<int>(sf::Keyboard::Scancode::E);
    supportedKeys["F"] = static_cast<int>(sf::Keyboard::Scancode::F);
    supportedKeys["Q"] = static_cast<int>(sf::Keyboard::Scancode::Q);
    supportedKeys["R"] = static_cast<int>(sf::Keyboard::Scancode::R);
    supportedKeys["S"] = static_cast<int>(sf::Keyboard::Scancode::S);
    supportedKeys["W"] = static_cast<int>(sf::Keyboard::Scancode::W);
    supportedKeys["X"] = static_cast<int>(sf::Keyboard::Scancode::X);
    supportedKeys["Z"] = static_cast<int>(sf::Keyboard::Scancode::Z);
    supportedKeys["1"] = static_cast<int>(sf::Keyboard::Scancode::Num1);
    supportedKeys["2"] = static_cast<int>(sf::Keyboard::Scancode::Num2);
    supportedKeys["3"] = static_cast<int>(sf::Keyboard::Scancode::Num3);
    supportedKeys["4"] = static_cast<int>(sf::Keyboard::Scancode::Num4);
    supportedKeys["5"] = static_cast<int>(sf::Keyboard::Scancode::Num5);
    supportedKeys["6"] = static_cast<int>(sf::Keyboard::Scancode::Num6);
    supportedKeys["7"] = static_cast<int>(sf::Keyboard::Scancode::Num7);
    supportedKeys["8"] = static_cast<int>(sf::Keyboard::Scancode::Num8);
    supportedKeys["9"] = static_cast<int>(sf::Keyboard::Scancode::Num9);
    supportedKeys["0"] = static_cast<int>(sf::Keyboard::Scancode::Num0);
    supportedKeys["Space"] = static_cast<int>(sf::Keyboard::Scancode::Space);
    supportedKeys["Enter"] = static_cast<int>(sf::Keyboard::Scancode::Enter);
    supportedKeys["BackSpace"] = static_cast<int>(sf::Keyboard::Scancode::Backspace);
    supportedKeys["Slash"] = static_cast<int>(sf::Keyboard::Scancode::Slash);
    supportedKeys["Tab"] = static_cast<int>(sf::Keyboard::Scancode::Tab);
    supportedKeys["F1"] = static_cast<int>(sf::Keyboard::Scancode::F1);
    supportedKeys["F2"] = static_cast<int>(sf::Keyboard::Scancode::F2);
    supportedKeys["F3"] = static_cast<int>(sf::Keyboard::Scancode::F3);
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
    mWindow = std::make_shared<sf::RenderWindow>(sf::RenderWindow(
        gfxSettings._struct.resolution,
        gfxSettings._struct.title,
        sf::State::Windowed));

    if (gfxSettings._struct.fullscreen && mWindow->isOpen()) {

        gfxSettings._struct._winResolutions = mWindow->getSize();
        mWindow->create(
            sf::VideoMode({ gfxSettings._struct._winResolutions.x, gfxSettings._struct._winResolutions.y }),
            gfxSettings._struct.title, sf::State::Fullscreen, gfxSettings._struct.contextSettings);
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
    mWindow.get()->close();
    mWindow.reset();

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
    while (const std::optional event = mWindow.get()->pollEvent()) {
        if (event->is<sf::Event::Closed>())
            this->mWindow->close();
    }
}

void Core::render()
{
    this->mWindow->clear();

    if (!this->mState.empty())
        this->mState.top()->render(*this->mWindow.get());

    this->mWindow->display();
}

void Core::updateDeltaTime()
{
    this->deltaTime = 0;
    this->deltaTime = this->deltaClock.restart().asSeconds();
    FPS::update();
}