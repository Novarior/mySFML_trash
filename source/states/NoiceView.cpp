#include "NoiceView.hpp"

void NoiceView::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["TAB_MENU"] = this->IsupportedKeys->at("Tab");
}

void NoiceView::createStepByStep(sf::Vector2f pos)
{
    double writebuff = 0;
    double writebuff_biome = 0;

    for (int x = pos.x * this->generateArea.x; x < (pos.x + 1) * this->generateArea.x; x++) {
        for (int y = pos.y * this->generateArea.y; y < (pos.y + 1) * this->generateArea.y; y++) {
            //  writebuff = myGN->getNoice(x, y);
            writebuff = mySN->noise(x * 0.005, y * 0.005);
            //  writebuff_biome = myGN_biome->getNoice(x, y);
            int normalized_value = static_cast<int>((writebuff - -1.f) / (1.f - -1.f) * 255);
            this->image.setPixel(x, y, sf::Color(normalized_value, normalized_value, normalized_value, 255));

            /* Default
            if (writebuff_biome < 55) { // sea biome
                if (writebuff < 45) { // deep ocean
                    this->image.setPixel(x, y, sf::Color(0, 10 + writebuff * 0.6, 100 + writebuff * 1.5, 255));
                    this->m_BlocksCounter.deep_ocean++;
                } else if (writebuff < 66) { // ocean
                    this->image.setPixel(x, y, sf::Color(0, 20 + writebuff * 0.7, 100 + writebuff * 1.7, 255));
                    this->m_BlocksCounter.ocean++;
                } else if (writebuff < 66) { //  sand
                    this->image.setPixel(x, y, sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90 + writebuff * 0.1, 255));
                    this->m_BlocksCounter.sand++;
                } else if (writebuff < 66) { // sea sand
                    this->image.setPixel(x, y, sf::Color(150 + writebuff * 1.5, 140 + writebuff * 1.6, 120 + writebuff * 0.1, 255));
                    this->m_BlocksCounter.seasand++;
                } else if (writebuff < 210) { // desert
                    this->image.setPixel(x, y, sf::Color(255 - writebuff * 0.2, 255 - writebuff * 0.4, 150 - writebuff * 0.1, 255));
                    this->m_BlocksCounter.beath++;
                } else { // lava
                    this->image.setPixel(x, y, sf::Color(255, 80 + writebuff * 0.3, 0, 255));
                    this->m_BlocksCounter.lava++;
                }
            } else if (writebuff_biome < 160) { // Grassland
                if (writebuff < 160) { // grass
                    this->image.setPixel(x, y, sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255));
                    this->m_BlocksCounter.grass++;
                } else if (writebuff < 165) { // ground
                    this->image.setPixel(x, y, sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255));
                    this->m_BlocksCounter.dirt++;
                } else if (writebuff < 175) { // cave
                    this->image.setPixel(x, y, sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255));
                    this->m_BlocksCounter.rock++;
                }
            } else if (writebuff_biome < 200) { // mountains
                if (writebuff < 180) { // mountain
                    this->image.setPixel(x, y, sf::Color(120 - writebuff * 0.2, 100 + writebuff * 0.2, 120 - writebuff * 0.2, 255));
                    this->m_BlocksCounter.mountain++;
                } else if (writebuff < 200) { // snow
                    this->image.setPixel(x, y, sf::Color(255 - writebuff * 0.4, 255 - writebuff * 0.4, 255 - writebuff * 0.4, 255));
                    this->m_BlocksCounter.snow++;
                }
            }

            */
        }
        this->texture.update(this->image);
        this->shape.setTexture(&this->texture);
    }
}

void NoiceView::initTabMenu()
{ // tab menu
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
}

void NoiceView::initButtons()
{ // init buttons
    this->buttons["G_NOICE"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(90, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Gen Noice", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color::Black, sf::Color::Black, sf::Color::Black);

    this->buttons["G_TREE"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x + this->tabShape.getSize().x / 2, this->tabShape.getPosition().y + mmath::p2pX(90, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Gen Tree", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color::Black, sf::Color::Black, sf::Color::Black);

    this->buttons["SAVE_GENDATA"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(80, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Save", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color::Black, sf::Color::Black, sf::Color::Black);

    this->buttons["LOAD_GENDATA"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x + this->tabShape.getSize().x / 2, this->tabShape.getPosition().y + mmath::p2pX(80, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, "Load", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90),
        sf::Color::Black, sf::Color::Black, sf::Color::Black);
}

void NoiceView::initSelectors()
{ // init static selector in tab menu
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
}

void NoiceView::initNoice()
{
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
    this->myGN_biome = new ProcessGenerationNoice(this->noicedata);
    this->myGN_biome->setSeed(this->myGN_biome->getSeed() + 1.f);
    this->isGeneratorClosed = false;

    this->generateArea.x = this->noicedata.RenderWindowX / this->numThreads;
    this->generateArea.y = this->noicedata.RenderWindowY / this->numThreads;

    this->closeGrid = sf::Vector2f();
}

void NoiceView::initDebugText()
{ // init debug text
    this->dText.setFont(this->IstateData->debugFont);
    this->dText.setCharacterSize(this->IstateData->characterSize_debug);
    this->dText.setPosition(sf::Vector2f(0, 0));
    this->dText.setFillColor(sf::Color::White);
    this->dText.setOutlineColor(sf::Color::Black);
    this->dText.setOutlineThickness(2.f);
}

NoiceView::NoiceView(StateData* statedata)
    : State(statedata)
{
    this->initKeybinds();
    this->initTabMenu();
    this->initButtons();
    this->initNoice();
    this->initSelectors();
    this->initDebugText();

    // init simple noise
    this->mySN = new SimplexNoise();
    // init LSystem
    this->myLS = new LSystem();
    this->myLS->setRule('d', "qd");
    this->myLS->setRule('s', "d[-qqs]+qqs");
    this->myLS->setOffsetPos(sf::Vector2f(this->IstateData->sWindow->getSize().x / 2, this->IstateData->sWindow->getSize().y * 0.70));
    this->myLS->generate();
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
    delete this->mySN;
    delete this->myLS;

    this->freeThreads();
}

void NoiceView::freeThreads()
{
    for (std::thread& thread : this->threads)
        if (thread.joinable())
            thread.join();
}

sf::IntRect NoiceView::findNonTransparentRect(const sf::Image& image)
{
    sf::Vector2u size = image.getSize();
    sf::IntRect mrect(size.x, size.y, 0, 0);

    for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y = 0; y < size.y; y++)
            if (image.getPixel(x, y) != sf::Color::Transparent) {
                if (x < mrect.left)
                    mrect.left = x;
                if (y < mrect.top)
                    mrect.top = y;
                if (x > mrect.width)
                    mrect.width = x;
                if (y > mrect.height)
                    mrect.height = y;
            }

    return mrect;
}

void NoiceView::saveTreeAsImage(sf::RenderWindow& window)
{
    // create texture with window size
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);

    // get array shape
    std::vector<sf::RectangleShape> shapes;
    shapes.insert(shapes.end(), this->myLS->internalArray(), this->myLS->internalArray() + this->myLS->getSizeArray());

    // Очищаем окно и рисуем все фигуры на текстуре
    window.clear(sf::Color::Transparent);
    for (auto& it : shapes)
        window.draw(it);

    // update
    texture.update(window);

    // get snapshoot
    sf::Image image = texture.copyToImage();

    // find Transparent pixels
    sf::IntRect mrect = findNonTransparentRect(image);

    // create newe image on mrect base
    sf::Image simg;
    simg.create(mrect.width - mrect.left, mrect.height - mrect.top);

    // copy pixels from original image
    for (int x = mrect.left; x < mrect.width; x++)
        for (int y = mrect.top; y < mrect.height; y++)
            simg.setPixel(x - mrect.left, y - mrect.top, image.getPixel(x, y));

    std::stringstream ss;
    ss << myConst::f_Trees << "tree" << std::to_string(std::time(nullptr)) << ".png";
    // Сохраняем изображение
    simg.saveToFile(ss.str());
}

void NoiceView::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->endState();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("TAB_MENU"))) && this->getKeytime())
        this->showTabmenu = !this->showTabmenu;
}

void NoiceView::updateDebugText(const float& delta_time)
{
    double fps = 1.0f / delta_time;
    this->dString_Stream
        << "FPS:\t" << fps
        << "\nBlock counter:"
        << "\n\tdeep ocean: " << this->m_BlocksCounter.deep_ocean
        << "\n\tocean: " << this->m_BlocksCounter.ocean
        << "\n\tbeath: " << this->m_BlocksCounter.beath
        << "\n\tseasand: " << this->m_BlocksCounter.seasand
        << "\n\tsand: " << this->m_BlocksCounter.sand
        << "\n\tgrass: " << this->m_BlocksCounter.grass
        << "\n\tdirt: " << this->m_BlocksCounter.dirt
        << "\n\trock: " << this->m_BlocksCounter.rock
        << "\n\tmountain: " << this->m_BlocksCounter.mountain
        << "\n\tsnow: " << this->m_BlocksCounter.snow
        << "\n\tdesert: " << this->m_BlocksCounter.seasand
        << "\n\tforest: " << this->m_BlocksCounter.forest
        << "\n\tlava: " << this->m_BlocksCounter.lava
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
        << "\n\tGenerateAreaX:\t" << this->generateArea.x
        << "\n\tGenerateAreaY:\t" << this->generateArea.y
        << "\n\tSmoothMode:\t" << this->selector->getActiveElement() << ": " << this->selector->getActiveElementID()
        << "\nTree Data:"
        << "\n\tTreeSize:\t" << this->myLS->getSizeTree()
        << "\nPause:\t" << this->Ipaused;

    this->dText.setString(this->dString_Stream.str());
    this->dString_Stream.str("");
}

void NoiceView::updateButtons(const float& delta_time)
{
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
    if (this->buttons["G_NOICE"]->isPressed()) {
        this->myGN->setNoiceData(this->noicedata);
        this->isGeneratorClosed = false;
        this->closeGrid = sf::Vector2f();
        this->m_BlocksCounter = { 0, 0, 0, 0, 0, 0, 0 };
    }
    if (this->buttons["G_TREE"]->isPressed()) {
        this->myLS->generate();
        this->saveTreeAsImage(*this->IstateData->sWindow);
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

void NoiceView::update(const float& delta_time)
{
    this->freeThreads();
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateMousePositions();
    if (this->showTabmenu)
        this->updateButtons(delta_time);
    this->myLS->update(delta_time);

    if (this->isGeneratorClosed == false) {
        for (int i = 0; i < this->numThreads; ++i) {
            int startX = i * this->generateArea.x;
            int endX = (i + 1) * this->generateArea.y;

            for (int j = 0; j < this->numThreads; ++j) {
                int startY = j * this->generateArea.x;
                int endY = (j + 1) * this->generateArea.x;

                // Создаем поток и передаем ему функцию fillImage
                this->threads.emplace_back(&NoiceView::createStepByStep, this, (sf::Vector2f(i, j)));
            }
        }
        this->isGeneratorClosed = true;
    }

    if (this->debugMode)
        this->updateDebugText(delta_time);
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

    if (this->myLS != nullptr)
        this->myLS->render(target);

    if (this->debugMode)
        target.draw(this->dText);

    if (this->showTabmenu)
        this->renderTabMenu(target);
}