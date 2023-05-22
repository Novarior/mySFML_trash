#include "Core.h"

//initialisations root data and build first frame app
void Core::initVar() {
    this->mWindow = NULL;
    srand(std::time(NULL));
    this->gfxSettings.loadFromFile("Config.cfg");
}

void Core::initStateData() {
    this->mStatedata.sWindow = this->mWindow;
    this->mStatedata.sStates = &this->mState;
    if (!this->mStatedata.font.loadFromFile(data_gameproces_font_path)) {}
    if (!this->mStatedata.debugFont.loadFromFile(data_gameproces_font_path)) {}
    this->mStatedata.supportedKeys = &this->supportedKeys;
    this->mStatedata.gfxSettings = &this->gfxSettings;
    this->mStatedata.grid_size = this->gfxSettings.gridSize;
}

void Core::initKeyBinds() {
    //load supported keys from file to map
    std::ifstream ifs("Config/supported_keys.ini");
    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
}

void Core::initState() {
    this->mState.push(new MainMenu(&this->mStatedata));
}

void Core::initWindow() {
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

}

Core::Core() {
    this->initKeyBinds();
    this->initVar();
    this->initWindow();
    this->initStateData();
    this->initState();
}

Core::~Core() {
    delete this->mWindow;
}

void Core::run() {
    while (this->mWindow->isOpen()) {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}

void Core::update() {
    this->updateEventsWindow();
    if (!this->mState.empty())
    {
        if (this->mWindow->hasFocus())
        {
            this->mState.top()->update(this->deltaTime);
            if (this->mState.top()->getQuit())
            {
                this->mState.top()->endState();
                delete this->mState.top();
                this->mState.pop();
            }
        }
    }
    //Application end
    else {
        this->mWindow->close();
    }
}

void Core::updateEventsWindow() {
    while (this->mWindow->pollEvent(this->mEvents))
        if (this->mEvents.type == sf::Event::Closed)
            this->mWindow->close();

}

void Core::render() {
    this->mWindow->clear();

    if (!this->mState.empty())
        this->mState.top()->render(*this->mWindow);

    this->mWindow->display();
}

void Core::updateDeltaTime() {
    this->deltaTime = 0;
    this->deltaTime = this->deltaClock.restart().asSeconds();
}