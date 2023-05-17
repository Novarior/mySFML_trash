#include "Process.hpp"

const bool Process::loadGameData() {
    std::ifstream ifs("gameconfig.cfg");
    if (ifs.is_open()) {
        sf::Vector2f playerBuffPos;

        ifs >> this->noicedata.seed;
        ifs >> this->noicedata.octaves;
        ifs >> this->noicedata.gridSize;
        ifs >> this->noicedata.frequency;
        ifs >> this->noicedata.mapSizeX >> this->noicedata.mapSizeY;
        ifs >> this->noicedata.RenderWindowX >> this->noicedata.RenderWindowY;

        ifs >> this->noicedata.persistence;
        ifs >> playerBuffPos.x >> playerBuffPos.y;

        this->m_gamedata.currentPlayerPos = playerBuffPos;
    }
    else
        return false;

    ifs.close();
    return true;
}

const bool Process::saveGameData() {

    std::ofstream ofs("gameconfig.cfg");
    if (ofs.is_open()) {
        ofs << this->noicedata.seed << '\n';
        ofs << this->noicedata.octaves << '\n';
        ofs << this->noicedata.gridSize << '\n';
        ofs << this->noicedata.frequency << '\n';
        ofs << this->noicedata.mapSizeX << ' ' << this->noicedata.mapSizeY << '\n';
        ofs << this->noicedata.RenderWindowX << ' ' << this->noicedata.RenderWindowY << '\n';
        ofs << this->noicedata.persistence << '\n';
        ofs << this->player->e_getPosition().x << ' ' << this->player->e_getPosition().y << '\n';
    }
    else
        return false;
    ofs.close();
    return true;
}

//init data who dont use loaded dates
void Process::initKeybinds() {
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["TAB"] = this->IsupportedKeys->at("Tab");
    this->Ikeybinds["KEY_A"] = this->IsupportedKeys->at("A");
    this->Ikeybinds["KEY_D"] = this->IsupportedKeys->at("D");
    this->Ikeybinds["KEY_S"] = this->IsupportedKeys->at("S");
    this->Ikeybinds["KEY_W"] = this->IsupportedKeys->at("W");
    this->Ikeybinds["KEY_C"] = this->IsupportedKeys->at("C");
}

void Process::initPauseMenu() {
    const sf::VideoMode& vm = this->IstateData->gfxSettings->resolution;
    this->pausemenu = new PauseMenu(this->IstateData->gfxSettings->resolution, this->IstateData->font);
    this->pausemenu->addButton("EXIT_BUTTON", mmath::p2pY(74.f, vm), mmath::p2pX(13.f, vm), mmath::p2pY(6.f, vm), mmath::calcCharSize(vm), "Quit");
}

void Process::initTileMap() {
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

void Process::initPlayer() {
    if (!this->playerTextureSHIT.loadFromFile(texture_GRASS))
    {
    }
    this->player = new Player(100, 100, this->playerTextureSHIT);

    this->t_inventory = new Inventory(sf::Vector2f(this->IstateData->sWindow->getSize()), 32.0f, this->IstateData->font, 40);
}

//Defauld Init Data
void Process::initTileMapData()
{
    this->noicedata.seed = 1;
    this->noicedata.gridSize = this->IstateData->grid_size;
    this->noicedata.octaves = 8;
    this->noicedata.frequency = 8;
    this->noicedata.RenderWindowX = this->IstateData->gfxSettings->resolution.width;
    this->noicedata.RenderWindowY = this->IstateData->gfxSettings->resolution.height;
    this->noicedata.mapSizeX = 620;
    this->noicedata.mapSizeY = 430;
    this->noicedata.persistence = 0.6f;
}

Process::Process(StateData* state_data, const bool defaultLoad) :State(state_data) {
    if (defaultLoad) {
        if (this->loadGameData())
            this->loaded = true;
        else
            this->loaded = false;
    }

    this->initKeybinds();
    this->initView();
    this->initPauseMenu();

    this->initTileMapData();
    this->initTileMap();
    this->initPlayer();
}

Process::~Process() {
    this->saveGameData();

    delete this->myGN;
    delete this->mapTiles;

    delete this->pausemenu;
    delete this->player;
    delete this->t_inventory;
}

void Process::updateInput(const float& delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("TAB"))) && this->getKeytime()) {}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->Ipaused = !this->Ipaused;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_C"))) && this->getKeytime()) {}
}

void Process::updatePlayerInputs(const float& delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_A"))))
        this->player->e_move(-1.f, 0.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_D"))))
        this->player->e_move(1.f, 0.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_S"))))
        this->player->e_move(0.f, 1.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_W"))))
        this->player->e_move(0.f, -1.f, delta_time);
}

void Process::updateTileMap(const float& delta_time) {
    this->mapTiles->updateWorldBoundsCollision(this->player);
    this->mapTiles->updateTileCollision(this->player, delta_time);
    this->mapTiles->update(this->player, delta_time);
}

void Process::update(const float& delta_time) {
    this->updateMousePositions(&this->view);
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);

    if (this->Ipaused) { //update pause
        this->pausemenu->update(this->mousePosWindow);

        if (this->pausemenu->isButtonPressed("EXIT_BUTTON") && this->getKeytime())
            this->endState();
    }
    else { //update game
        this->updatePlayerInputs(delta_time);
        this->updateTileMap(delta_time);
        this->player->e_update(delta_time, this->mousePosView, this->playerView);

    }

    if (this->debugMode) {//update debug information
        double fps = 1.0f / delta_time;
        this->dString_Stream
            << "FPS:\t" << fps
            << "\nResolution:\t" << this->Iwindow->getSize().x << " x " << this->Iwindow->getSize().y
            << "\nPlayer:"
            << "\nComponents: "
            << "\n\tvelX: " << this->player->e_getVelocity().x
            << "\n\tvelY: " << this->player->e_getVelocity().y
            << "\nPosition:"
            << "\n\tx: " << this->player->e_getPosition().x
            << "\n\ty: " << this->player->e_getPosition().y
            << "\n\tSecected Cell ID: " << this->t_inventory->getCurrentCellID(this->mousePosWindow)
            << "\n\tgrid x: " << this->player->e_getGridPositionFloat(this->IgridSize).x
            << "\n\tgrid y: " << this->player->e_getGridPositionFloat(this->IgridSize).y
            << "\nMap Size: " << this->mapTiles->getMapSizeOnTiles().x << 'x' << this->mapTiles->getMapSizeOnTiles().y
            << "\nMap Area Render: "
            << this->mapTiles->getRenderArea().fromX << ' '
            << this->mapTiles->getRenderArea().fromY << ' '
            << this->mapTiles->getRenderArea().toX << ' '
            << this->mapTiles->getRenderArea().toY << '\n'
            << "Pause:\t" << this->Ipaused;

        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void Process::render(sf::RenderWindow& target) {

    //CLEAR pre rendered texture
    this->renderTexture.clear();
    this->renderTexture.setView(this->playerView);

    // render scne in custom view
    this->mapTiles->render(&this->renderTexture, this->player->e_getGridPositionInt(this->IgridSize), this->debugMode);
    this->playerView.setCenter(this->player->e_getPosition());
    this->player->e_render(this->renderTexture, true);

    // reset view
    this->renderTexture.setView(this->renderTexture.getDefaultView());

    //render other elements
    if (this->debugMode)
        this->renderTexture.draw(this->dText);

    if (this->Ipaused) //Pause menu render
        this->pausemenu->render(this->renderTexture);

    //final render
    this->renderTexture.display();
    target.draw(this->renderSprite);
}