#include "MainMenu.hpp"

void MainMenu::initRenderDefines()
{
    this->renderTexture.create(
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y);
    this->renderTexture.setSmooth(true);

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0,
        this->IstateData->sWindow->getSize().x,
        this->IstateData->sWindow->getSize().y));

    this->view.setSize(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x),
        static_cast<float>(this->IstateData->sWindow->getSize().y)));

    this->view.setCenter(sf::Vector2f(
        static_cast<float>(this->IstateData->sWindow->getSize().x / 2),
        static_cast<float>(this->IstateData->sWindow->getSize().y / 2)));
}

void MainMenu::initKeybinds()
{
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
}

void MainMenu::initBackground()
{

    sf::Texture tx;
    for (int i = 0; i < 3; i++) {
        this->background_textures.push_back(sf::Texture());
    }
    tx.loadFromFile(myConst::texture_background_mainmenu_lay_3);
    tx.setSmooth(true);
    this->background_textures[0] = tx;
    tx.loadFromFile(myConst::texture_background_mainmenu_lay_2);
    tx.setSmooth(true);
    this->background_textures[1] = tx;
    tx.loadFromFile(myConst::texture_background_mainmenu_lay_1);
    tx.setSmooth(true);
    this->background_textures[2] = tx;

    // init background shapes
    for (size_t i = 0; i < 3; i++) {
        this->backgrond_shapes.push_back(sf::RectangleShape());

        this->backgrond_shapes[i].setSize(sf::Vector2f(this->background_textures[i].getSize()));
        this->backgrond_shapes[i].setTexture(&this->background_textures[i], true);

        this->backgrond_shapes[i].setOrigin(sf::Vector2f(
            this->backgrond_shapes[i].getSize().x / 2,
            this->backgrond_shapes[i].getSize().y / 2));

        this->backgrond_shapes[i].setPosition(sf::Vector2f(
            this->IstateData->sWindow->getSize().x / 2 - (this->backgrond_shapes[i].getSize().x / 2) + this->backgrond_shapes[i].getOrigin().x,
            this->IstateData->sWindow->getSize().y / 2 - (this->backgrond_shapes[i].getSize().y / 2) + this->backgrond_shapes[i].getOrigin().y));
    }
    this->backgrond_shapes[0].scale(sf::Vector2f(2.f, 2.f));
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

void MainMenu::initGUI()
{
    this->initBackground();
    this->initButtons();
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
    this->initButtons();
    this->initStartProcces();
}

MainMenu::~MainMenu()
{
    // delete buttons
    if (!this->buttons.empty())
        for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
            delete it->second;
    this->buttons.clear();

    for (auto it = this->backgrond_shapes.begin(); it != this->backgrond_shapes.end(); ++it)
        this->backgrond_shapes.erase(it);
    this->backgrond_shapes.clear();
}

void MainMenu::update(const float& delta_time)
{
    this->updateKeytime(delta_time);

    this->updateGUI(delta_time);

    if (!this->isstatred) {
        this->updateMousePositions(&this->view);
        this->updateInput(delta_time);
        this->updateButtons();
    } else
        this->updateStartProcces();
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

void MainMenu::updateGUI(const float& delta_time)
{
    // update debug text
    if (this->debugMode) {
        this->dString_Stream
            << "\nver:\t" << CMAKE_PROJECT_VERSION
            << "\nFPS:\t" << 1 / delta_time
            << "\nFPS limit:\t" << this->IstateData->gfxSettings->frameRateLimit
            << "\nDelta Time:\t" << delta_time
            << "\nResolution:\t" << this->IstateData->sWindow->getSize().x << " x " << this->IstateData->sWindow->getSize().y
            << "\nAntialiasing:\t" << this->IstateData->sWindow->getSettings().antialiasingLevel
            << "\nvSync:\t" << this->IstateData->gfxSettings->verticalSync
            << "\nMouse Pos:\t" << this->mousePosWindow.x << " x " << this->mousePosWindow.y;
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }

    // update GUI
    this->backgrond_shapes[0].rotate(delta_time);
    this->backgrond_shapes[1].rotate(-delta_time);
}
void MainMenu::render(sf::RenderWindow& target)
{
    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    // render background
    // renderTexture.draw(this->background);
    // render background shapes
    for (auto& it : this->backgrond_shapes)
        renderTexture.draw(it);
    // render GUI
    if (!this->buttons.empty())
        for (auto& it : this->buttons)
            it.second->render(renderTexture);
    // fadeout fx
    if (this->isstatred)
        renderTexture.draw(this->fadeShape);

    // // debug shapes
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