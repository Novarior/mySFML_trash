#include "NoiceView.hpp"

void NoiceView::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["TAB_MENU"] = this->IsupportedKeys->at("Tab");
}

void NoiceView::initButton()
{
    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(), sf::Vector2f(250, 100),
        this->IstateData->font, "Exit", this->IstateData->characterSize_game_small,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));
}

void NoiceView::createStepByStep(sf::Vector2f pos)
{
    double writebuff = 0;
    double min = 10, max = 0;

    for (int x = pos.x * this->gridSizeX; x < (pos.x + 1) * this->gridSizeX; x++) {
        for (int y = pos.y * this->gridSizeY; y < (pos.y + 1) * this->gridSizeY; y++) {
            writebuff = myGN->getNoice(x, y);
            if (writebuff < min)
                min = writebuff;
            if (writebuff > max)
                max = writebuff;
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { // sea
                this->image.setPixel(x, y, sf::Color(0, 10 + writebuff * 0.6, 100 + writebuff * 1.9, 255));
                this->m_BlocksCounter.ocean++;
            } else if (writebuff < 66) { // sand
                this->image.setPixel(x, y, sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90 + writebuff * 0.1, 255));
                this->m_BlocksCounter.sand++;
            } else if (writebuff < 160) { // grass
                this->image.setPixel(x, y, sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255));
                this->m_BlocksCounter.grass++;
            } else if (writebuff < 165) { // ground
                this->image.setPixel(x, y, sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255));
                this->m_BlocksCounter.dirt++;
            } else if (writebuff < 175) { // cave
                this->image.setPixel(x, y, sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255));
                this->m_BlocksCounter.rock++;
            } else { // other
                this->image.setPixel(x, y, sf::Color(writebuff, writebuff, writebuff, 255));
                this->m_BlocksCounter.other++;
            }
        }
    }
    this->texture.update(this->image);
    this->shape.setTexture(&this->texture);
}

NoiceView::NoiceView(StateData* statedata, bool quick)
    : State(statedata)
{
    this->initKeybinds();

    if (!this->Iparser->loadNoiceData(myConst::config_noicedata, this->noicedata)) { // init noise data
        this->noicedata.octaves = 8;
        this->noicedata.seed = std::rand();
        this->noicedata.frequency = 8;
        this->noicedata.amplifire = 1;
        this->noicedata.persistence = 0.6f;
    }
    this->noicedata.gridSize = this->IstateData->grid_size;
    this->noicedata.RenderWindowX = this->IstateData->gfxSettings->resolution.width;
    this->noicedata.RenderWindowY = this->IstateData->gfxSettings->resolution.height;
    this->noicedata.mapSizeX = this->IstateData->gfxSettings->resolution.width;
    this->noicedata.mapSizeY = this->IstateData->gfxSettings->resolution.height;
    this->noicedata.smoothMode = 0;
    // init noice generator
    this->image.create(this->noicedata.RenderWindowX, this->noicedata.RenderWindowY);
    this->shape.setSize(sf::Vector2f(this->noicedata.RenderWindowX, this->noicedata.RenderWindowY));
    this->texture.create(this->noicedata.RenderWindowX, this->noicedata.RenderWindowY);
    this->myGN = new ProcessGenerationNoice(this->noicedata);
    this->isGeneratorClosed = false;
    this->gridSizeX = this->noicedata.RenderWindowX / 10;
    this->gridSizeY = this->noicedata.RenderWindowY / 10;
    this->closeGrid = sf::Vector2f();

    // tab menu
    this->tabShape.setPosition(sf::Vector2f(
        mmath::p2pX(70, this->IstateData->sWindow->getSize().x), 0));
    this->tabShape.setSize(sf::Vector2f(
        mmath::p2pX(30, this->IstateData->sWindow->getSize().x),
        this->IstateData->sWindow->getSize().y));
    // half transparent gray
    this->tabShape.setFillColor(sf::Color(150, 150, 150, 200));
    this->tabShape.setOutlineThickness(5.f);
    this->tabShape.setOutlineColor(sf::Color(100, 100, 100, 192));
    this->showTabmenu = false;

    // init static selector in tab menu
    this->staticSelector["OCTAVES"] = new gui::StaticSelector(
        sf::Vector2f(this->tabShape.getPosition()),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, 0, 10, 1.f, true, "Octaves: ");

    this->staticSelector["FREQUENCY"] = new gui::StaticSelector(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, 0, 10, 0.1f, true, "Frequency: ");

    this->staticSelector["PERSISTENCE"] = new gui::StaticSelector(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(14, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, 0, 5, 0.1f, true, "Persistence: ");

    this->staticSelector["AMPLIFIRE"] = new gui::StaticSelector(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(21, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, 0, 3, 0.1f, true, "Amplifire: ");
    // init buttons
    this->buttons["GENERATE"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(90, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Generate", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["SAVE_GENDATA"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(80, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Save", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["LOAD_GENDATA"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x + this->tabShape.getSize().x / 2, this->tabShape.getPosition().y + mmath::p2pX(80, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Load", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    // linear interpolation = 0
    // cosine interpolation  = 1
    // cubic interpolation = 2
    // quintic interpolation = 3
    // quartic interpolation = 4
    // quadratic interpolation = 5
    // hermite interpolation = 6

    std::vector<std::string> list = { "Linear", "Cosine", "Cubic", "Quintic", "Quartic", "Quadratic", "Hermite" };

    this->selector = new gui::Selector(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(28, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, list.data(), list.size(), 0);

    // set default value for static selector
    this->staticSelector["OCTAVES"]->setCurrentValue(this->noicedata.octaves);
    this->staticSelector["FREQUENCY"]->setCurrentValue(this->noicedata.frequency);
    this->staticSelector["AMPLIFIRE"]->setCurrentValue(this->noicedata.amplifire);
    this->staticSelector["PERSISTENCE"]->setCurrentValue(this->noicedata.persistence);

    // init debug text
    this->dText.setFont(this->IstateData->debugFont);
    this->dText.setCharacterSize(this->IstateData->characterSize_debug);
    this->dText.setPosition(sf::Vector2f(0, 0));
    this->dText.setFillColor(sf::Color::White);
    this->dText.setOutlineColor(sf::Color::Black);
    this->dText.setOutlineThickness(1.f);
}

NoiceView::~NoiceView()
{
    this->Iparser->saveNoiceData(myConst::config_noicedata, this->noicedata);
    delete this->myGN;
    for (auto& it : this->buttons)
        delete it.second;

    for (auto& it : this->staticSelector)
        delete it.second;

    delete this->selector;
}

void NoiceView::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->endState();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("TAB_MENU"))) && this->getKeytime())
        this->showTabmenu = !this->showTabmenu;
}

void NoiceView::update(const float& delta_time)
{
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateMousePositions();

    if (this->showTabmenu) {
        for (auto& it : this->buttons)
            it.second->update(this->mousePosWindow);

        for (auto& it : this->staticSelector)
            it.second->update(delta_time, this->mousePosWindow);

        this->selector->update(delta_time, this->mousePosWindow);

        if (this->staticSelector["OCTAVES"]->isValueChanged()) {
            this->noicedata.octaves = this->staticSelector["OCTAVES"]->getCurrentValue();
            this->staticSelector["OCTAVES"]->closeChangeValue();
        }
        if (this->staticSelector["FREQUENCY"]->isValueChanged()) {
            this->noicedata.frequency = this->staticSelector["FREQUENCY"]->getCurrentValue();
            this->staticSelector["FREQUENCY"]->closeChangeValue();
        }
        if (this->staticSelector["PERSISTENCE"]->isValueChanged()) {
            this->noicedata.persistence = this->staticSelector["PERSISTENCE"]->getCurrentValue();
            this->staticSelector["PERSISTENCE"]->closeChangeValue();
        }
        if (this->staticSelector["AMPLIFIRE"]->isValueChanged()) {
            this->noicedata.amplifire = this->staticSelector["AMPLIFIRE"]->getCurrentValue();
            this->staticSelector["AMPLIFIRE"]->closeChangeValue();
        }
        if (this->buttons["GENERATE"]->isPressed()) {
            this->myGN->setNoiceData(this->noicedata);
            this->isGeneratorClosed = false;
            this->closeGrid = sf::Vector2f();
            this->m_BlocksCounter = { 0, 0, 0, 0, 0, 0, 0 };
        }
        if (this->buttons["SAVE_GENDATA"]->isPressed()) {
            this->Iparser->saveNoiceData(myConst::config_noicedata, this->noicedata);
        }
        if (this->buttons["LOAD_GENDATA"]->isPressed()) {
            this->Iparser->loadNoiceData(myConst::config_noicedata, this->noicedata);
            this->staticSelector["OCTAVES"]->setCurrentValue(this->noicedata.octaves);
            this->staticSelector["FREQUENCY"]->setCurrentValue(this->noicedata.frequency);
            this->staticSelector["AMPLIFIRE"]->setCurrentValue(this->noicedata.amplifire);
            this->staticSelector["PERSISTENCE"]->setCurrentValue(this->noicedata.persistence);
            this->selector->setActiveElement(this->noicedata.smoothMode);
        }
        this->selector->update(delta_time, this->mousePosWindow);

        this->noicedata.smoothMode = this->selector->getActiveElementID();
    }

    if (!this->isGeneratorClosed) {
        this->createStepByStep(this->closeGrid);
        if (this->closeGrid.x == 9) {
            this->closeGrid.x = 0;
            this->closeGrid.y += 1;
        } else
            this->closeGrid.x += 1;

        if (this->closeGrid.y == 10)
            this->isGeneratorClosed = true;
    }

    if (this->debugMode) { // update debug information
        double fps = 1.0f / delta_time;
        this->dString_Stream
            << "FPS:\t" << fps
            << "\nBlock counter:"
            << "\n\tgrass: " << this->m_BlocksCounter.grass
            << "\n\tdirt: " << this->m_BlocksCounter.dirt
            << "\n\tmud: " << this->m_BlocksCounter.mud
            << "\n\tocean: " << this->m_BlocksCounter.ocean
            << "\n\trock: " << this->m_BlocksCounter.rock
            << "\n\tsand: " << this->m_BlocksCounter.sand
            << "\n\tother " << this->m_BlocksCounter.other
            << "\nGenerator data:"
            << "\n\tGenerator closed:\t" << this->isGeneratorClosed
            << "\n\tSeed:\t" << this->noicedata.seed
            << "\n\tOctaves:\t" << this->noicedata.octaves
            << "\n\tFrequency:\t" << this->noicedata.frequency
            << "\n\tAmplifire:\t" << this->noicedata.amplifire
            << "\n\tPersistence:\t" << this->noicedata.persistence
            << "\n\tNoiceSizeBYWindowX:\t" << this->noicedata.RenderWindowX
            << "\n\tNoiceSizeBYWindowY:\t" << this->noicedata.RenderWindowY
            << "\n\tNoiceSizeMapX:\t" << this->noicedata.mapSizeX
            << "\n\tNoiceSizeMapY:\t" << this->noicedata.mapSizeY
            << "\n\tGridSizeX:\t" << this->gridSizeX
            << "\n\tGridSizeY:\t" << this->gridSizeY
            << "\n\tSmoothMode:\t" << this->selector->getActiveElement() << ": " << this->selector->getActiveElementID()
            << "\nPause:\t" << this->Ipaused;

        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void NoiceView::renderTabMenu(sf::RenderTarget& target)
{
    target.draw(this->tabShape);

    for (auto& it : this->staticSelector)
        it.second->render(target);

    for (auto& it : this->buttons)
        it.second->render(target);

    this->selector->render(target);
}

void NoiceView::render(sf::RenderWindow& target)
{
    target.draw(this->shape);

    if (this->debugMode)
        target.draw(this->dText);

    if (this->showTabmenu)
        this->renderTabMenu(target);
}