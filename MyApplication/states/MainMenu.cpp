#include "MainMenu.hpp"

void MainMenu::initRenderDefines() {
    this->renderTexture.create(
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0,
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y));
}

void MainMenu::initKeybinds() {
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
}

void MainMenu::initView() {
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));
}

void MainMenu::initBackground() {
    this->background.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
    this->background.setFillColor(sf::Color(0, 0, 30));
    this->background.setPosition(sf::Vector2f());
}

void MainMenu::initButtons() {
    int offsetX = this->IstateData->sWindow->getSize().x;
    int offsetY = this->IstateData->sWindow->getSize().y;

    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(offsetX - 275, offsetY - 125), sf::Vector2f(250, 100),
        this->IstateData->font, "Exit", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["START_BTN"] = new gui::Button(
        sf::Vector2f(offsetX - 275, offsetY - 225), sf::Vector2f(250, 100),
        this->IstateData->font, "Play", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["PERLIN"] = new gui::Button(
        sf::Vector2f(offsetX - 275, offsetY - 325), sf::Vector2f(250, 100),
        this->IstateData->font, "Noice", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["CONT_BTN"] = new gui::Button(
        sf::Vector2f(offsetX - 275, offsetY - 425), sf::Vector2f(250, 100),
        this->IstateData->font, "Continue", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));

    this->buttons["SETTINGS_BTN"] = new gui::Button(
        sf::Vector2f(offsetX - 275, offsetY - 525), sf::Vector2f(250, 100),
        this->IstateData->font, "Settings", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));
}

void MainMenu::initBlocks() {
    BlocksGenData bgd;
    bgd.amplifire = 500;
    bgd.countPhantomBlocks = 255;
    bgd.offset = sf::Vector2f(
        this->IstateData->sWindow->getSize().x / 2,
        this->IstateData->sWindow->getSize().y / 2);
    bgd.windowSize = this->IstateData->sWindow->getSize();
    bgd.pos = sf::Vector2f();
    bgd.frequency = 2.5f;

    this->rotationCyrcleShape = new RotarionCircle(bgd);
    sf::CircleShape shape;
    shape.setFillColor(sf::Color::White);
    shape.setRadius(20.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(0.f);
    this->rotationCyrcleShape->setShape(shape);
}

void MainMenu::initStartProcces() {
    this->fadeShape.setFillColor(sf::Color(0, 0, 0, 0));
    this->fadeShape.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
}

void MainMenu::updateStartProcces() {
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

void MainMenu::resetView() {
    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));
}

MainMenu::MainMenu(StateData* statedata) :State(statedata) {
    this->initRenderDefines();
    this->initKeybinds();
    this->initView();
    this->initBackground();
    this->initButtons();
    this->initBlocks();
    this->initStartProcces();
}

MainMenu::~MainMenu() {
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;

    this->buttons.clear();
    delete this->rotationCyrcleShape;
}

void MainMenu::update(const float& delta_time) {
    this->updateKeytime(delta_time);

    if (!this->isstatred) {
        this->updateMousePositions(&this->view);
        this->updateInput(delta_time);
        this->updateButtons();
    }
    else
        this->updateStartProcces();

    this->rotationCyrcleShape->update(delta_time);

    if (this->debugMode)
    {
        this->dString_Stream
            << "FPS:\t" << 1 / delta_time
            << "\nVersion: " << versionApp
            << "\nOS: " << OperationSystem;
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void MainMenu::updateInput(const float& delta_time) {

}

void MainMenu::updateButtons() {
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

void MainMenu::render(sf::RenderWindow& target) {
    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    renderTexture.draw(this->background);

    this->rotationCyrcleShape->render(renderTexture);

    for (auto& it : this->buttons)
        it.second->render(renderTexture);

    this->renderTexture.setView(this->renderTexture.getDefaultView());

    if (this->isstatred)
        renderTexture.draw(this->fadeShape);

    if (this->debugMode)
        this->renderTexture.draw(this->dText);

    this->renderTexture.display();
    target.draw(this->renderSprite);
}