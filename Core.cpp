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
    if (!this->mStatedata.font.loadFromFile("/Users/dmitrijsusenko/Desktop/try/Resourses/Fonts/PlayfairDisplay-Black.ttf")) {}
    if (!this->mStatedata.debugFont.loadFromFile("/Users/dmitrijsusenko/Desktop/try/Resourses/Fonts/Muli-Regular.ttf")) {}
    this->mStatedata.supportedKeys = &this->supportedKeys;
    this->mStatedata.gfxSettings = &this->gfxSettings;
    this->mStatedata.grid_size = this->gfxSettings.gridSize;
}

void Core::initKeyBinds() {
    this->supportedKeys["A"] = 0;
    this->supportedKeys["C"] = 2;
    this->supportedKeys["D"] = 3;
    this->supportedKeys["L"] = 11;
    this->supportedKeys["S"] = 18;
    this->supportedKeys["W"] = 22;
    this->supportedKeys["X"] = 23;
    this->supportedKeys["Z"] = 25;
    this->supportedKeys["Escape"] = 36;
    this->supportedKeys["Tab"] = 60;
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

const bool Core::run() {
    while (this->mWindow->isOpen()) {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
    return true;
}

void Core::update() {
    this->updateEventsWindow();
    if (!this->mState.empty()) {
        if (this->mWindow->hasFocus()) {
            this->mState.top()->update(this->deltaTime);
            if (this->mState.top()->getQuit()) {
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
        this->mState.top()->render(this->mWindow);

    this->mWindow->display();
}

void Core::updateDeltaTime() {
    this->deltaTime = this->deltaClock.restart().asSeconds();
}