#include "Process.hpp"

const bool Process::loadGameData()
{

    // load game config
    std::ifstream ifs("config/gameconfig.cfg");
    if (ifs.is_open()) {
        sf::Vector2f playerBuffPos;

        ifs >> this->noicedata.seed;
        ifs >> this->noicedata.octaves;
        ifs >> this->noicedata.gridSize;
        ifs >> this->noicedata.frequency;
        ifs >> this->noicedata.mapSizeX >> this->noicedata.mapSizeY;
        ifs >> this->noicedata.RenderWindowX >> this->noicedata.RenderWindowY;

        ifs >> this->noicedata.persistence;
    } else
        return false;
    ifs.close();

    // load player
    std::ifstream ifs1("config/playerdata.cfg");
    if (ifs1.is_open()) {
        // buffer for player position and attributes
        sf::Vector2f playerBuffPos;
        Atri buffer;
        // load player position to buffer
        ifs1 >> playerBuffPos.x >> playerBuffPos.y;
        // load player attributes to buffer
        ifs1 >> buffer.health >> buffer.max_health >> buffer.experience >> buffer.experience_for_level >> buffer.level >> buffer.some_points;
        // set player position
        this->player->e_setPosition(playerBuffPos);
        // set attributes to player
        this->player->getAttributes()->setAttributes(buffer);
    } else
        printf("ERROR::PLAYERDATA.CFG::COULD_NOT_LOAD\n");
    ifs1.close();

    return true;
}

const bool Process::saveGameData()
{
    // save game config
    std::ofstream ofs("config/gameconfig.cfg");
    if (ofs.is_open()) {
        ofs << this->noicedata.seed << '\n';
        ofs << this->noicedata.octaves << '\n';
        ofs << this->noicedata.gridSize << '\n';
        ofs << this->noicedata.frequency << '\n';
        ofs << this->noicedata.mapSizeX << ' ' << this->noicedata.mapSizeY << '\n';
        ofs << this->noicedata.RenderWindowX << ' ' << this->noicedata.RenderWindowY << '\n';
        ofs << this->noicedata.persistence << '\n';
    } else {
        printf("ERROR::GAMECONFIG.CFG::COULD_NOT_SAVE\n");
        ofs.close();
        return false;
    }
    ofs.close();

    // save player to JSON file
    if (!this->Iparser->savePlayer("config/playerdata.json", this->player))
        printf("ERROR::PLAYERDATA.JSON::COULD_NOT_SAVE\n");
    // save inventory to JSON file
    if (!this->Iparser->saveInventory("config/inventorydata.json", this->t_inventory))
        printf("ERROR::INVENTORYDATA.JSON::COULD_NOT_SAVE\n");
    // save entitys pos and other data
    if (!this->Iparser->saveEntitys("config/entitysdata.json", this->entitys))
        printf("ERROR::ENTITYSDATA.JSON::COULD_NOT_SAVE\n");

    return true;
}

// init data who dont use loaded dates
void Process::initKeybinds()
{
    this->Ikeybinds["KEY_CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["KEY_TAB"] = this->IsupportedKeys->at("Tab");
    this->Ikeybinds["KEY_A"] = this->IsupportedKeys->at("A");
    this->Ikeybinds["KEY_D"] = this->IsupportedKeys->at("D");
    this->Ikeybinds["KEY_S"] = this->IsupportedKeys->at("S");
    this->Ikeybinds["KEY_W"] = this->IsupportedKeys->at("W");

    // debug moment
    // std::cout<<"sizeof keybinds: "<<this->Ikeybinds.size()<<'\n';
}

void Process::initPauseMenu()
{
    const sf::VideoMode& vm = this->IstateData->gfxSettings->resolution;
    this->pausemenu = new PauseMenu(this->IstateData->gfxSettings->resolution, this->IstateData->font);
    this->pausemenu->addButton("EXIT_BUTTON", mmath::p2pY(74.f, vm), mmath::p2pX(13.f, vm), mmath::p2pY(6.f, vm), mmath::calcCharSize(vm), "Quit");
}

void Process::initTileMap()
{
    this->myGN = new ProcessGenerationNoice(this->noicedata);
    this->mapTiles = new TileMap(this->noicedata, myGN);
}

void Process::initView()
{
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

void Process::initPlayer()
{
    this->player = new Player(sf::Vector2f(100, 100));

    this->t_inventory = new Inventory(sf::Vector2f(this->IstateData->sWindow->getSize()), 32.0f, this->IstateData->font, this->IstateData->characterSize_game_big);

    // init player HP bar on top right on screen math position using mmath::p2pX/X
    this->playerBar["HP_BAR"] = new gui::ProgressBar(
        sf::Vector2f(mmath::p2pX(75, this->IstateData->sWindow->getSize().x), mmath::p2pX(3, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(20, this->IstateData->sWindow->getSize().x), mmath::p2pX(3, this->IstateData->sWindow->getSize().y)),
        sf::Color::Red, this->IstateData->characterSize_game_small, this->IstateData->font);
    this->playerBar["MP_BAR"] = new gui::ProgressBar(
        sf::Vector2f(mmath::p2pX(75, this->IstateData->sWindow->getSize().x), mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(mmath::p2pX(20, this->IstateData->sWindow->getSize().x), mmath::p2pX(3, this->IstateData->sWindow->getSize().y)),
        sf::Color::Blue, this->IstateData->characterSize_game_small, this->IstateData->font);
}

// Defauld Init Data
void Process::initTileMapData()
{
    this->noicedata.seed = std::time(nullptr);
    this->noicedata.gridSize = this->IstateData->grid_size;
    this->noicedata.octaves = 8;
    this->noicedata.frequency = 8;
    this->noicedata.RenderWindowX = this->IstateData->gfxSettings->resolution.width;
    this->noicedata.RenderWindowY = this->IstateData->gfxSettings->resolution.height;
    this->noicedata.mapSizeX = 620;
    this->noicedata.mapSizeY = 430;
    this->noicedata.persistence = 0.6f;
}

void Process::initEntitys()
{
    float posx = 0;
    float posy = 0;

    for (size_t i = 0; i < 32; i++) {
        // call function to get random position
        posx = rand() % 1000;
        posy = rand() % 1000;
        this->entitys.push_back(new Slime(posx, posy, *this->player));
    }
}

Process::Process(StateData* state_data, const bool defaultLoad)
    : State(state_data)
{
    // init Parser
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
    this->initEntitys();
}

Process::~Process()
{
    this->saveGameData();

    delete this->myGN;
    delete this->mapTiles;
    delete this->pausemenu;
    delete this->player;
    delete this->t_inventory;

    // clear bar
    for (auto& it : this->playerBar)
        delete it.second;

    // clear vector entitys
    for (size_t i = 0; i < this->entitys.size(); i++) {
        delete this->entitys[i];
    }
}

void Process::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_TAB"))) && this->getKeytime())
        this->t_inventory->toggleSwitch();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_CLOSE"))) && this->getKeytime())
        this->Ipaused = !this->Ipaused;
}

void Process::updatePlayerInputs(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_A"))))
        this->player->e_move(-1.f, 0.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_D"))))
        this->player->e_move(1.f, 0.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_S"))))
        this->player->e_move(0.f, 1.f, delta_time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_W"))))
        this->player->e_move(0.f, -1.f, delta_time);
}

void Process::updateTileMap(const float& delta_time)
{ // update tilemap
    this->mapTiles->updateRenderArea(this->player->e_getGridPositionInt(this->IgridSize));
    this->mapTiles->update(this->player, delta_time);

    // update entitys collision
    for (size_t i = 0; i < this->entitys.size(); i++)
        this->mapTiles->update(this->entitys[i], delta_time);
}

void Process::updateEntitys(const float& delta_time)
{ // update entitys
    for (size_t i = 0; i < this->entitys.size(); i++)
        this->entitys[i]->e_update(delta_time);
}

void Process::update(const float& delta_time)
{
    this->updateMousePositions(&this->view);
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);

    if (this->Ipaused) { // update pause
        this->pausemenu->update(this->mousePosWindow);

        if (this->pausemenu->isButtonPressed("EXIT_BUTTON") && this->getKeytime())
            this->endState();
    } else { // update game
        this->updateEntitys(delta_time);
        this->updatePlayerInputs(delta_time);
        this->updateTileMap(delta_time);
        this->player->e_update(delta_time);
        this->playerBar["HP_BAR"]->update(this->player->getAttributes()->getAttributes()->health, this->player->getAttributes()->getAttributes()->max_health);
        this->playerBar["MP_BAR"]->update(this->player->getAttributes()->getAttributes()->mana, this->player->getAttributes()->getAttributes()->max_mana);

        if (this->t_inventory->getIsOpened() && !this->Ipaused) // inventory  menu update
            this->t_inventory->update(this->mousePosWindow);
    }

    if (this->debugMode) { // update debug information
        double fps = 1.0f / delta_time;
        this->dString_Stream
            << "FPS:\t" << fps
            << "\nResolution: " << this->Iwindow->getSize().x << " x " << this->Iwindow->getSize().y
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
            << "Pause:\t" << this->Ipaused
            << "\nMemory Usage: "
            // get memory usage enemys on bytes
            << "\n\tPlayer: " << sizeof(*this->player) << " = " << sizeof(Player) << " bytes"
            << "\n\tEntitys: " << this->entitys.size() << " x " << sizeof(Entity) << " = " << this->entitys.size() * sizeof(Entity) << " bytes"
            << "\n\tTotal Entitys: " << Entity::count_entitys
            << "\n\tTileMap: " << sizeof(*this->mapTiles) << " bytes"
            << "\n\tPauseMenu: " << sizeof(*this->pausemenu) << " bytes"
            << "\n\tInventory: " << sizeof(*this->t_inventory) << " bytes"
            << "\n\tTotal usage: " << sizeof(*this->player) + (this->entitys.size() * sizeof(Entity)) + sizeof(this->mapTiles) + sizeof(*this->pausemenu) + sizeof(*this->t_inventory) << " bytes";

        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

// sub render functions
void Process::renderGUI(sf::RenderTarget& target)
{

    // render player bars
    for (auto& it : this->playerBar)
        it.second->render(target);

    if (this->debugMode) // debuging text render
        target.draw(this->dText);

    if (this->Ipaused) // Pause menu render
        this->pausemenu->render(target);

    if (this->t_inventory->getIsOpened() && !this->Ipaused) // inventory  menu render
        this->t_inventory->render(target);
}

void Process::renderTileMap(sf::RenderTarget& target)
{
    this->mapTiles->render(&target);
}

void Process::renderEntities(sf::RenderTarget& target)
{
    for (auto* enemy : this->entitys)
        ;
    // enemy->e_render(target, this->debugMode);
}

void Process::renderPlayer(sf::RenderTarget& target)
{
    this->player->e_render(target);
    this->playerView.setCenter(this->player->e_getPosition());
}
// main render function
void Process::render(sf::RenderWindow& target)
{
    // CLEAR pre rendered texture
    this->renderTexture.clear();
    this->renderTexture.setView(this->playerView);
    // render scne in custom view
    this->renderTileMap(this->renderTexture);
    this->renderEntities(this->renderTexture);
    this->renderPlayer(this->renderTexture);
    // reset view
    this->renderTexture.setView(this->renderTexture.getDefaultView());
    // render GUI elements
    this->renderGUI(this->renderTexture);
    // final render
    this->renderTexture.display();
    target.draw(this->renderSprite);
}