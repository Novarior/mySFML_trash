#include "MainMenu.hpp"

void MainMenu::initRenderDefines()
{
    this->renderTexture.create(
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0,
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y));
}

void MainMenu::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
}

void MainMenu::initView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));
}

void MainMenu::initBackground()
{
    this->background.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
    this->background.setFillColor(sf::Color(0, 0, 30));
    this->background.setPosition(sf::Vector2f());
}

void MainMenu::initButtons()
{
    int offsetX = mmath::p2pX(5, this->Iwindow->getSize().x);
    int offsetY = mmath::p2pX(5, this->Iwindow->getSize().y);

    this->buttons["CONT_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(60, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, "Continue", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["START_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(70, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, "Play", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["SETTINGS_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(80, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, "Settings", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(90, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, "Exit", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["PERLIN"] = new gui::Button(
        sf::Vector2f(mmath::p2pX(85, this->Iwindow->getSize().x) - offsetX, mmath::p2pX(10, this->Iwindow->getSize().y) - offsetY), // pos
        sf::Vector2f(mmath::p2pX(15, this->Iwindow->getSize().x), mmath::p2pX(7, this->Iwindow->getSize().y)), // size
        this->IstateData->font, "Noice", this->IstateData->characterSize_game_big,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));
}

void MainMenu::initBlocks()
{
    BlocksGenData bgd;
    bgd.amplifire = 500;
    bgd.countPhantomBlocks = 255;
    bgd.offset = sf::Vector2f(
        this->IstateData->sWindow->getSize().x / 2,
        this->IstateData->sWindow->getSize().y / 2);
    bgd.windowSize = this->IstateData->sWindow->getSize();
    bgd.pos = sf::Vector2f();
    bgd.frequency = 1.5f;

    this->rotationCyrcleShape = new RotarionCircle(bgd);
    sf::CircleShape shape;
    shape.setFillColor(sf::Color::White);
    shape.setRadius(20.f);
    shape.setOutlineColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.f);
    this->rotationCyrcleShape->setShape(shape);
}

void MainMenu::initGUI()
{
    // debug moment

    int offsetX = mmath::p2pX(5, this->Iwindow->getSize().x);
    int offsetY = mmath::p2pX(5, this->Iwindow->getSize().y);

    for (int i = 0; i < 5; i++) {
        this->debug_shapes.push_back(sf::RectangleShape());
        this->debug_shapes[i].setPosition(sf::Vector2f(
            mmath::p2pX(15, this->Iwindow->getSize().x) - offsetX,
            mmath::p2pX(90 - (i * 10), this->Iwindow->getSize().y) - offsetY));
        this->debug_shapes[i].setSize(sf::Vector2f(
            mmath::p2pX(15, this->Iwindow->getSize().x),
            mmath::p2pX(7, this->Iwindow->getSize().y)));
        this->debug_shapes[i].setFillColor(sf::Color::Transparent);
        this->debug_shapes[i].setOutlineColor(sf::Color::White);
        this->debug_shapes[i].setOutlineThickness(-1);
    }
}

void MainMenu::resetGUI()
{
}

void MainMenu::initStartProcces()
{
    this->fadeShape.setFillColor(sf::Color(0, 0, 0, 0));
    this->fadeShape.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
}

void MainMenu::updateStartProcces()
{
    sf::Color buff = this->fadeShape.getFillColor();

    if (buff.a < 255)
        buff.a += 1;
    else {
        this->Istates->push(new Process(this->IstateData, false));

        this->isstatred = false;
        this->resetView();

        buff = sf::Color(0, 0, 0, 0);
    }
    this->fadeShape.setFillColor(buff);

    sf::Vector2f vSize = this->view.getSize();
    vSize -= sf::Vector2f(1, 1);
    this->view.setSize(vSize);
}

void MainMenu::resetView()
{
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));
}

MainMenu::MainMenu(StateData* statedata)
    : State(statedata)
{
    this->initGUI();
    this->initRenderDefines();
    this->initKeybinds();
    this->initView();
    this->initBackground();
    this->initButtons();
    this->initBlocks();
    this->initStartProcces();
}

MainMenu::~MainMenu()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;

    this->buttons.clear();
    delete this->rotationCyrcleShape;
}

void MainMenu::update(const float& delta_time)
{
    this->updateKeytime(delta_time);

    if (!this->isstatred) {
        this->updateMousePositions(&this->view);
        this->updateInput(delta_time);
        this->updateButtons();
    } else
        this->updateStartProcces();

    this->rotationCyrcleShape->update(delta_time);

    if (this->debugMode) {
        this->dString_Stream
            << "\nver:\t" << CMAKE_PROJECT_VERSION
            << "\nFPS:\t" << 1 / delta_time
            << "\nFPS limit:\t" << this->IstateData->gfxSettings->frameRateLimit
            << "\nDelta Time:\t" << delta_time
            << "\nResolution:\t" << this->IstateData->sWindow->getSize().x << " x " << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing:\t" << this->IstateData->gfxSettings->contextSettings.antialiasingLevel
            << "\nvSync:\t" << this->IstateData->gfxSettings->verticalSync;
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void MainMenu::updateInput(const float& delta_time)
{
}

void MainMenu::updateButtons()
{
    if (!this->buttons.empty()) {
        for (auto& it : this->buttons)
            it.second->update(this->mousePosWindow);

        if (this->buttons["EXIT_BTN"]->isPressed() && this->getKeytime())
            this->endState();

        if (this->buttons["START_BTN"]->isPressed() && this->getKeytime())
            this->Istates->push(new Process(this->IstateData, false));

        if (this->buttons["CONT_BTN"]->isPressed() && this->getKeytime()) {
            this->Istates->push(new Process(this->IstateData, true));
            this->resetView();
        }
        if (this->buttons["SETTINGS_BTN"]->isPressed() && this->getKeytime())
            this->Istates->push(new SettingsState(this->IstateData));

        if (this->buttons["PERLIN"]->isPressed() && this->getKeytime())
            this->Istates->push(new NoiceView(this->IstateData, false));
    }
}

void MainMenu::render(sf::RenderWindow& target)
{
    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    // render background
    renderTexture.draw(this->background);
    // render circle
    this->rotationCyrcleShape->render(renderTexture);
    // render GUI
    if (!this->buttons.empty())
        for (auto& it : this->buttons)
            it.second->render(renderTexture);
    // fadeout fx
    if (this->isstatred)
        renderTexture.draw(this->fadeShape);

    // debug
    // debug shapes
    // if (!this->debug_shapes.empty())
    //     for (auto& it : this->debug_shapes)
    //         this->renderTexture.draw(it);
    // debug text
    if (this->debugMode)
        this->renderTexture.draw(this->dText);

    this->renderTexture.setView(this->renderTexture.getDefaultView());

    this->renderTexture.display();
    target.draw(this->renderSprite);
}