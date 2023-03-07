#include "Process.hpp"

void Process::loadGameData() {
    std::ifstream ifs("gameconfig.cfg");
    if (ifs.is_open()) {}
    ifs.close();
}

void Process::saveGameData() {
    std::ofstream ofs("gameconfig.cfg");
    if (ofs.is_open())
    {
        ofs << this->noicedata.seed;
        ofs << this->noicedata.mapSize.x << this->noicedata.mapSize.y;
        ofs << this->noicedata.octaves;
        ofs << this->noicedata.persistence;
        ofs << this->noicedata.RenderWindow.x << this->noicedata.RenderWindow.y;
        ofs << this->noicedata.gridSize;

    }
    ofs.close();
}

void Process::initKeybinds() {
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["TAB"] = this->IsupportedKeys->at("Tab");
    this->Ikeybinds["KEY_A"] = this->IsupportedKeys->at("A");
    this->Ikeybinds["KEY_D"] = this->IsupportedKeys->at("D");
    this->Ikeybinds["KEY_S"] = this->IsupportedKeys->at("S");
    this->Ikeybinds["KEY_W"] = this->IsupportedKeys->at("W");
    this->Ikeybinds["KEY_C"] = this->IsupportedKeys->at("C");

}

void Process::initTileMap() {
    this->noicedata.gridSize = this->IstateData->grid_size;
    this->noicedata.octaves = 8;
    this->noicedata.seed = 1;
    this->noicedata.frequency = 8;
    this->noicedata.RenderWindow = sf::Vector2f(
        this->IstateData->gfxSettings->resolution.width,
        this->IstateData->gfxSettings->resolution.height);
    this->noicedata.mapSize = sf::Vector2u(620, 430);
    this->noicedata.persistence = 0.6f;

    this->myGN = new ProcessGenerationNoice(this->noicedata);
    this->mapTiles = new TileMap(this->noicedata, myGN);
}

void Process::initView() {
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));

    this->playerView.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));

    this->playerView.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));

    this->renderTexture.create(
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0,
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y));
}

void Process::initTabMenu() {
    this->tabmenu = new gui::TabMenu(this->IstateData->sWindow->getSize());

    this->tabmenu->addButton("TTT_BUTTON", new gui::Button(
        sf::Vector2f(this->IstateData->sWindow->getSize().x - 185, 115),
        sf::Vector2f(160, 90),
        this->IstateData->font, "ttt", 20,
        sf::Color::White,
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90)));

    this->tabmenu->addButton("REBUILD_BUTTON", new gui::Button(
        sf::Vector2f(this->IstateData->sWindow->getSize().x - 185, 25),
        sf::Vector2f(160, 90),
        this->IstateData->font, "reBuild", 20,
        sf::Color::White,
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90)));
}

void Process::initPlayer() {
    this->player = new Player();
}

void Process::initPauseMenu() {
    const sf::VideoMode& vm = this->IstateData->gfxSettings->resolution;
    this->pausemenu = new PauseMenu(this->IstateData->gfxSettings->resolution, this->IstateData->font);
    this->pausemenu->addButton("EXIT_BUTTON", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}


Process::Process(StateData* state_data):State(state_data) {
    this->initKeybinds();
    this->initView();
    this->initTileMap();
    this->initTabMenu();
    this->initPlayer();
    this->initPauseMenu();
    this->gameClock.restart();
}

Process::~Process() {
    delete this->myGN;
    delete this->mapTiles;
    delete this->tabmenu;
    delete this->pausemenu;
    delete this->player;
}

void Process::updateInput(const float& deltatime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("TAB"))) && this->getKeytime())
        this->tabmenu->toggleSwitch();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->Ipaused = !this->Ipaused;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_C"))) && this->getKeytime()) {}
}

void Process::updatePlayerInputs(const float& deltatime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_A"))))
        this->player->e_move(sf::Vector2f(-1.f, 0.f), deltatime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_D"))))
        this->player->e_move(sf::Vector2f(1.f, 0.f), deltatime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_S"))))
        this->player->e_move(sf::Vector2f(0.f, 1.f), deltatime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_W"))))
        this->player->e_move(sf::Vector2f(0.f, -1.f), deltatime);

    //this->player->e_jump(deltatime);
}

void Process::updateButtons() {
    if (this->tabmenu->isPressed("REBUILD_BUTTON") && this->getKeytime());
}

void Process::update(const float& deltatime) {
    this->updateMousePositions(&this->view);
    this->updateKeytime(deltatime);
    this->updateInput(deltatime);

    if (this->Ipaused) { //update pause
        this->pausemenu->update(this->mousePosWindow);
        if (this->pausemenu->isButtonPressed("EXIT_BUTTON") && this->getKeytime())
            this->endState();
    }
    else { //update game
        this->updatePlayerInputs(deltatime);
        this->updateButtons();
        if (this->tabmenu->isOpen())
            this->tabmenu->update(deltatime, this->mousePosWindow);

        this->player->e_update(this->mapTiles, deltatime);
    }

    if (this->debugMode) {//update debug information
        double fps = 1.0f / deltatime;
        this->dString_Stream
            << "FPS:\t" << fps << "\n"
            << "Time Elapsed: " << this->m_gamedata.timeInitElapsed << '\n'
            << "Player:\n"
            << "\tvelX: " << this->player->e_getVelocity().x << "\n"
            << "\tvelY: " << this->player->e_getVelocity().y << '\n'
            << "Position:\n"
            << "\tx: " << this->player->e_getPosition().x
            << "\ty: " << this->player->e_getPosition().y << '\n'
            << "\tgrid x: " << this->player->e_getGridPosition(this->IgridSize).x << '\n'
            << "\tgrid y: " << this->player->e_getGridPosition(this->IgridSize).y << '\n'
            << "Map Size: " << this->mapTiles->getMapSizeOnTiles().x << 'x' << this->mapTiles->getMapSizeOnTiles().y << '\n'
            << "Map Area Render:\t"
            << this->mapTiles->getRenderArea().fromX << ' '
            << this->mapTiles->getRenderArea().fromY << ' '
            << this->mapTiles->getRenderArea().toX << ' '
            << this->mapTiles->getRenderArea().toY << '\n'
            << "Pause:\t" << this->Ipaused;

        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void Process::render(sf::RenderWindow* target) {
    if (!target)
        target = this->Iwindow;
    // re CLEAR pre rendered texture
    this->renderTexture.clear();
    this->renderTexture.setView(this->playerView);

    // render scne in custom view
    this->mapTiles->render(&this->renderTexture, this->player->e_getGridPosition(this->IgridSize), this->debugMode);
    this->playerView.setCenter(this->player->e_getPosition());
    this->player->e_render(&this->renderTexture);

    // reset view
    this->renderTexture.setView(this->renderTexture.getDefaultView());

    //render other elements
    if (this->tabmenu->isOpen())
        this->tabmenu->render(&this->renderTexture);

    if (this->debugMode)
        this->renderTexture.draw(this->dText);

    if (this->Ipaused) //Pause menu render
        this->pausemenu->render(&this->renderTexture);

    //final render
    this->renderTexture.display();
    target->draw(this->renderSprite);
}