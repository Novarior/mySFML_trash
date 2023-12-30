#include "Core.h"

void Core::initDirectories()
{ // check if app directory exists
    if (!sAppFunctions::checkAppDirectoryExists(myConst::app_name)) {
        std::cout << "App directory does not exist" << std::endl;
        std::cout << "Creating app directory" << std::endl;
        sAppFunctions::createAppDirectories(myConst::app_name);
    } else {
        std::cout << "App directory exists" << std::endl;
    }
}

// initialisations root data and build first frame app
void Core::initVar()
{
    this->mWindow = NULL;

    if (!this->gfxSettings.loadFromFile(sAppFunctions::getDocumentsAppFolder()))
        this->gfxSettings.saveToFile(sAppFunctions::getDocumentsAppFolder());
}

void Core::initStateData()
{
    this->mStatedata.sWindow = this->mWindow;
    this->mStatedata.sStates = &this->mState;
    if (!this->mStatedata.font.loadFromFile(std::string(sAppFunctions::get_resources_dir() + myConst::data_gameproces_font_path))) { }
    if (!this->mStatedata.debugFont.loadFromFile(std::string(sAppFunctions::get_resources_dir() + myConst::data_debugfont_path))) { }
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
    this->supportedKeys["Escape"] = sf::Keyboard::Scancode::Escape;
    this->supportedKeys["A"] = sf::Keyboard::Scancode::A;
    this->supportedKeys["C"] = sf::Keyboard::Scancode::C;
    this->supportedKeys["D"] = sf::Keyboard::Scancode::D;
    this->supportedKeys["E"] = sf::Keyboard::Scancode::E;
    this->supportedKeys["F"] = sf::Keyboard::Scancode::F;
    this->supportedKeys["Q"] = sf::Keyboard::Scancode::Q;
    this->supportedKeys["R"] = sf::Keyboard::Scancode::R;
    this->supportedKeys["S"] = sf::Keyboard::Scancode::S;
    this->supportedKeys["W"] = sf::Keyboard::Scancode::W;
    this->supportedKeys["X"] = sf::Keyboard::Scancode::X;
    this->supportedKeys["Z"] = sf::Keyboard::Scancode::Z;
    this->supportedKeys["Space"] = sf::Keyboard::Scancode::Space;
    this->supportedKeys["Enter"] = sf::Keyboard::Scancode::Enter;
    this->supportedKeys["BackSpace"] = sf::Keyboard::Scancode::Backspace;
    this->supportedKeys["Slash"] = sf::Keyboard::Scancode::Slash;
    this->supportedKeys["Tab"] = sf::Keyboard::Scancode::Tab;
    this->supportedKeys["F1"] = sf::Keyboard::Scancode::F1;
    this->supportedKeys["F2"] = sf::Keyboard::Scancode::F2;
    this->supportedKeys["F3"] = sf::Keyboard::Scancode::F3;
    // save default keys to file
    ParserJson::saveKeyBinds(this->supportedKeys);
}

void Core::initState()
{
    this->mState.push(new MainMenu(&this->mStatedata));
}

void Core::initWindow()
{
    if (this->gfxSettings._struct.fullscreen)
        this->mWindow = new sf::RenderWindow(
            this->gfxSettings._struct.resolution,
            this->gfxSettings._struct.title,
            sf::Style::Default,
            this->gfxSettings._struct.contextSettings);
    else
        this->mWindow = new sf::RenderWindow(
            this->gfxSettings._struct.resolution,
            this->gfxSettings._struct.title,
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings._struct.contextSettings);

    if (gfxSettings.getgfxsettings().fullscreen)
        mWindow->create(this->gfxSettings._struct.resolution, this->gfxSettings._struct.title, sf::Style::Fullscreen, this->gfxSettings._struct.contextSettings);

    this->mWindow->setFramerateLimit(this->gfxSettings._struct.frameRateLimit);
    this->mWindow->setVerticalSyncEnabled(this->gfxSettings._struct.verticalSync);
    this->mWindow->setKeyRepeatEnabled(false);
}

Core::Core()
{
    this->initDirectories();
    this->initKeyBinds();
    this->initVar();
    this->initWindow();
    this->initStateData();
    this->initState();

    FPS::reset();
    Logger::log("Core Inited", "Core::Core()");
}

Core::~Core()
{
    this->gfxSettings.saveToFile(sAppFunctions::getDocumentsAppFolder());

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