#include "Core.h"

//initialisations root data and build first frame app
void Core::initVar() {
    this->mWindow = NULL;
    srand(std::time(NULL));
    if (!this->gfxSettings.loadFromFile("Config.json"))
        this->gfxSettings.saveToFile("Config.json");
}

void Core::initStateData() {
    this->mStatedata.sWindow = this->mWindow;
    this->mStatedata.sStates = &this->mState;
    if (!this->mStatedata.font.loadFromFile(data_gameproces_font_path)) {}
    if (!this->mStatedata.debugFont.loadFromFile(data_gameproces_font_path)) {}
    this->mStatedata.supportedKeys = &this->supportedKeys;
    this->mStatedata.gfxSettings = &this->gfxSettings;
    this->mStatedata.grid_size = this->gfxSettings.gridSize;
    this->mStatedata.parser = this->parsJSON;
}

void Core::initKeyBinds() {
    //load supported keys from JSON file to map supportedKeys, check if file exist, create if not
    if (!this->parsJSON->loadKeyBinds("Config/supported_keys.json", this->supportedKeys)) {
        //print error
        std::cout << "ERROR::CORE::INITKEYBINDS::FAILED TO LOAD SUPPORTED KEYS FROM JSON FILE" << std::endl;
        //init default keys "W A S D SPACE ESC E Q R F TAB"
        this->supportedKeys["Escape"] = sf::Keyboard::Escape;
        this->supportedKeys["A"] = sf::Keyboard::A;
        this->supportedKeys["D"] = sf::Keyboard::D;
        this->supportedKeys["S"] = sf::Keyboard::S;
        this->supportedKeys["W"] = sf::Keyboard::W;
        this->supportedKeys["Space"] = sf::Keyboard::Space;
        this->supportedKeys["E"] = sf::Keyboard::E;
        this->supportedKeys["Q"] = sf::Keyboard::Q;
        this->supportedKeys["R"] = sf::Keyboard::R;
        this->supportedKeys["F"] = sf::Keyboard::F;
        this->supportedKeys["Tab"] = sf::Keyboard::Tab;
        //save default keys to file
        this->parsJSON->saveKeyBinds("Config/supported_keys.json", this->supportedKeys);
    }
    //else do nothing
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
    this->parsJSON = new mypars::parsJSON();

    this->initKeyBinds();
    this->initVar();
    this->initWindow();
    this->initStateData();
    this->initState();
}

Core::~Core() {
    this->gfxSettings.saveToFile("Config.json");
    delete this->parsJSON;

    while (!this->mState.empty()) {
        delete this->mState.top();
        this->mState.pop();
    }
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