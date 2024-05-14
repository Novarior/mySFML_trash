#include "EditorState.hpp"

void EditorState::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["TAB_MENU"] = this->IsupportedKeys->at("Tab");
    this->Ikeybinds["KEY_Q"] = this->IsupportedKeys->at("Q");
    this->Ikeybinds["KEY_W"] = this->IsupportedKeys->at("W");
    this->Ikeybinds["KEY_E"] = this->IsupportedKeys->at("E");
    this->Ikeybinds["KEY_R"] = this->IsupportedKeys->at("R");
    this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
}

void EditorState::initTabMenu()
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

void EditorState::initButtons()
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

void EditorState::initSelectors()
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
        this->IstateData->font, this->IstateData->characterSize_game_big, 0, 10, 0.1f, true, "Amplifire: ");

    std::vector<std::string> list = { "Linear", "Cosine", "Cubic", "Quintic", "Quartic", "Quadratic", "Hermite" };

    this->selector = new gui::Selector(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(28, this->IstateData->sWindow->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x, mmath::p2pX(7, this->IstateData->sWindow->getSize().y)),
        this->IstateData->font, this->IstateData->characterSize_game_big, list.data(), list.size(), 0);

    // set default value for static selector
    this->staticSelector["OCTAVES"]->setCurrentValue(this->m_NoiceViewer->getNoiceData().octaves);
    this->staticSelector["FREQUENCY"]->setCurrentValue(this->m_NoiceViewer->getNoiceData().frequency);
    this->staticSelector["AMPLIFIRE"]->setCurrentValue(this->m_NoiceViewer->getNoiceData().amplifire);
    this->staticSelector["PERSISTENCE"]->setCurrentValue(this->m_NoiceViewer->getNoiceData().persistence);
}

void EditorState::initNoice()
{

    if (ParserJson::loadNoiceData(this->m_noiceData)) { // init noise data
        this->m_noiceData.octaves = 8;
        std::srand(std::time(nullptr));
        this->m_noiceData.seed = std::rand();
        this->m_noiceData.frequency = 8;
        this->m_noiceData.amplifire = 1;
        this->m_noiceData.persistence = 0.6f;
    }
    this->m_noiceData.gridSize = this->IstateData->grid_size;
    this->m_noiceData.RenderWindowX = this->IstateData->gfxSettings->_struct.resolution.width;
    this->m_noiceData.RenderWindowY = this->IstateData->gfxSettings->_struct.resolution.height;
    this->m_noiceData.mapSizeX = this->IstateData->gfxSettings->_struct.resolution.width;
    this->m_noiceData.mapSizeY = this->IstateData->gfxSettings->_struct.resolution.height;
    this->m_noiceData.smoothMode = 0;

    // init data for noice viewer
    this->m_NoiceViewer = new NoiceViewer(this->m_noiceData);
    this->m_NoiceViewer->generateNoice();
}

void EditorState::initDebugText()
{ // init debug text
    this->dText.setFont(this->IstateData->debugFont);
    this->dText.setCharacterSize(this->IstateData->characterSize_debug);
    this->dText.setPosition(sf::Vector2f(0, 0));
    this->dText.setFillColor(sf::Color::White);
    this->dText.setOutlineColor(sf::Color::Black);
    this->dText.setOutlineThickness(2.f);
}

EditorState::EditorState(StateData* statedata)
    : State(statedata)
{
    // init logger
    Logger::log("Start initilization EditorState", "EditorState::EditorState()");
    // init keybinds
    this->initKeybinds();
    this->initTabMenu();
    this->initButtons();
    this->initNoice();
    this->initSelectors();
    this->initDebugText();

    // init LSystem
    this->myLS = new LSystem();
    this->myLS->setRule('d', "qd");
    this->myLS->setRule('s', "d[-qqs]+qqs");
    this->myLS->setOffsetPos(sf::Vector2f(this->IstateData->sWindow->getSize().x / 2, this->IstateData->sWindow->getSize().y * 0.70));
    this->myLS->generate();

    Logger::log("End initilization EditorState", "EditorState::EditorState()");
}

EditorState::~EditorState()
{
    Logger::log("Start destruction EditorState", "EditorState::~EditorState()");

    ParserJson::saveNoiceData(this->m_NoiceViewer->getNoiceData());

    for (auto& it : this->buttons)
        delete it.second;

    for (auto& it : this->staticSelector)
        delete it.second;

    delete this->selector;

    delete this->myLS;
}

sf::IntRect EditorState::findNonTransparentRect(const sf::Image& image)
{
    // this function find non transparent pixels
    // and return IntRect without this pixels
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

void EditorState::saveTreeAsImage(sf::RenderWindow& window)
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

    // create name for image file
    // add time to name for unique name
    std::stringstream ss;
    ss << myConst::f_Trees << "tree" << std::to_string(std::time(nullptr)) << ".png";

    // save image
    simg.saveToFile(ss.str());
}

void EditorState::updateInput(const float& delta_time)
{
    // if pressed key ESC then end state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->endState();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->debugMode = !this->debugMode;

    // switch tab menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("TAB_MENU"))) && this->getKeytime())
        this->showTabmenu = !this->showTabmenu;

    // update currentViewGenerator in a range from 0 to 2
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_Q"))) && this->getKeytime())
        this->m_NoiceViewer->swithNoiceModel();

    // switch noice model
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_W"))) && this->getKeytime())
        this->m_NoiceViewer->swithColorMode();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_E"))) && this->getKeytime()) {
        if (this->current_View_Generator < 2)
            this->current_View_Generator++;
        else
            this->current_View_Generator = 0;
    }
    // switch noice smooth mode (fast mode)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_R"))) && this->getKeytime())
        this->m_noiceData.fastMode = !this->m_noiceData.fastMode;
}

void EditorState::updateDebugText(const float& delta_time)
{
    // collect all data for debug text and update it
    double fps = 1.0f / delta_time;
    this->dString_Stream
        << "FPS:\t" << fps
        << "\nCurent view generator:\t" << this->current_View_Generator
        << "\nCurent noice view mode:\t" << this->m_NoiceViewer->getNoiceModelName() << ":\t" << this->m_NoiceViewer->getNoiceModel()
        << "\nCurent noice color mode:\t" << this->m_NoiceViewer->getColorModeName() << ":\t" << this->m_NoiceViewer->getColorMode();
    if (this->m_NoiceViewer->getNoiceModel() == noiceType::PERLIN_NOICE_V2)
        this->dString_Stream
            << "\nCurent noice smooth mode:\t" << this->m_NoiceViewer->getNoiceSmouthName() << ":\t" << this->m_NoiceViewer->getNoiceData().smoothMode
            << "\nSeed:\t" << this->m_NoiceViewer->getNoiceData().seed
            << "\nFastMode" << this->m_NoiceViewer->getNoiceData().fastMode;
    this->dString_Stream
        << "\nTree Data:"
        << "\n\tTreeSize:\t" << this->myLS->getSizeTree()
        << "\nPause:\t" << this->Ipaused;

    // update debug text
    this->dText.setString(this->dString_Stream.str());
    // clear string stream
    this->dString_Stream.str("");
}

void EditorState::updateButtons(const float& delta_time)
{
    for (auto& it : this->buttons)
        it.second->update(this->mousePosWindow);

    for (auto& it : this->staticSelector)
        it.second->update(delta_time, this->mousePosWindow);

    this->selector->update(delta_time, this->mousePosWindow);

    // update buttons using switch case for each button
    switch (this->current_View_Generator) {
    case 0: // noice case
        if (this->staticSelector["OCTAVES"]->isValueChanged()) {
            this->m_noiceData.octaves = this->staticSelector["OCTAVES"]->getCurrentValue();
            this->staticSelector["OCTAVES"]->closeChangeValue();
        }
        if (this->staticSelector["FREQUENCY"]->isValueChanged()) {
            this->m_noiceData.frequency = this->staticSelector["FREQUENCY"]->getCurrentValue();
            this->staticSelector["FREQUENCY"]->closeChangeValue();
        }
        if (this->staticSelector["PERSISTENCE"]->isValueChanged()) {
            this->m_noiceData.persistence = this->staticSelector["PERSISTENCE"]->getCurrentValue();
            this->staticSelector["PERSISTENCE"]->closeChangeValue();
        }
        if (this->staticSelector["AMPLIFIRE"]->isValueChanged()) {
            this->m_noiceData.amplifire = this->staticSelector["AMPLIFIRE"]->getCurrentValue();
            this->staticSelector["AMPLIFIRE"]->closeChangeValue();
        }
        if (this->buttons["G_NOICE"]->isPressed()) {
            this->m_NoiceViewer->generateNoice();
        }
        if (this->buttons["SAVE_GENDATA"]->isPressed()) {
            ParserJson::saveNoiceData(this->m_noiceData);
        }
        if (this->buttons["LOAD_GENDATA"]->isPressed()) {
            ParserJson::loadNoiceData(this->m_noiceData);
            this->staticSelector["OCTAVES"]->setCurrentValue(this->m_noiceData.octaves);
            this->staticSelector["FREQUENCY"]->setCurrentValue(this->m_noiceData.frequency);
            this->staticSelector["AMPLIFIRE"]->setCurrentValue(this->m_noiceData.amplifire);
            this->staticSelector["PERSISTENCE"]->setCurrentValue(this->m_noiceData.persistence);
            this->selector->setActiveElement(this->m_noiceData.smoothMode);
        }
        this->m_NoiceViewer->setNoiceData(this->m_noiceData);
        break;
    case 1: // tree case
        if (this->buttons["G_TREE"]->isPressed()) {
            this->myLS->generate();
            this->saveTreeAsImage(*this->IstateData->sWindow);
        }
        break;
    default: // default case
        break;
    }
    this->selector->update(delta_time, this->mousePosWindow);
    this->m_noiceData.smoothMode = this->selector->getActiveElementID();
}

void EditorState::updateSounds(const float& delta_time)
{
}

void EditorState::update(const float& delta_time)
{
    // update keytime for next function used it for keypress delay
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateMousePositions();
    // if tab menu is open then update buttons
    if (this->showTabmenu)
        this->updateButtons(delta_time);

    // update debug text
    if (this->debugMode)
        this->updateDebugText(delta_time);
}

void EditorState::renderTabMenu(sf::RenderTarget& target)
{
    target.draw(this->tabShape);

    for (auto& it : this->staticSelector)
        it.second->render(target);

    for (auto& it : this->buttons)
        it.second->render(target);

    this->selector->render(target);
}

void EditorState::render(sf::RenderWindow& target)
{
    // layer 0 - noice render and tree render
    switch (this->current_View_Generator) {
    case 0: // call noice render
        if (this->m_NoiceViewer != nullptr)
            this->m_NoiceViewer->render(target);
        break;
    case 1: // call tree render
        if (this->myLS != nullptr)
            this->myLS->render(target);
        break;
    default:
        break;
    }
    // layer 1 - tab menu render
    if (this->showTabmenu)
        this->renderTabMenu(target);

    // layer 2 - debug text render
    // render debug text
    if (this->debugMode)
        target.draw(this->dText);
}
