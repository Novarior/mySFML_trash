#include "settings.hpp"

void SettingsState::initVariables()
{
    // init variables
    // init parser for some reason
    this->Iparser = this->IstateData->parser;
    // init video modes like all supported modes
    this->video_modes = sf::VideoMode::getFullscreenModes();
    // init framerates list
    this->framerates_list.push_back(30);
    this->framerates_list.push_back(60);
    this->framerates_list.push_back(90);
    this->framerates_list.push_back(120);
}

void SettingsState::initFonts()
{
    this->font = this->IstateData->font;
}

void SettingsState::initKeybinds()
{
    // init key escape like defoult back button
    this->Ikeybinds["KEY_BACK"] = this->IsupportedKeys->at("Escape");
}

void SettingsState::initGui()
{
    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->Iwindow->getSize().x),
        static_cast<float>(this->Iwindow->getSize().y)));
    // darkest blue color
    this->background.setFillColor(sf::Color(3, 3, 30, 100));

    // exit gui button
    this->buttons["BACK_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 120, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Back", this->IstateData->characterSize_game,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 0, 0, 200), sf::Color(255, 0, 0, 250), sf::Color(255, 0, 0, 50), 0);
    // apply gui button
    // set "apply" button position litle bit left from "back" button
    this->buttons["APPLY_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 240, 0.f),
        sf::Vector2f(120.f, 50.f), this->IstateData->font, "Apply", this->IstateData->characterSize_game,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(0, 255, 0, 200), sf::Color(0, 255, 0, 250), sf::Color(0, 255, 0, 50), 1);

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    for (auto& i : this->video_modes) {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
        mmath::p2pX(2.5, this->Iwindow->getSize().x), // pos screen/5/2/4
        mmath::p2pX(33, this->Iwindow->getSize().y), // pos
        mmath::p2pX(15, this->Iwindow->getSize().x), // size
        mmath::p2pX(6, this->Iwindow->getSize().y), // size
        font, this->IstateData->characterSize_game, modes_str.data(), modes_str.size());

    // int drop down list with fps limit
    std::vector<std::string> fps_limits;
    for (auto& x : this->framerates_list)
        fps_limits.push_back(std::to_string(x));

    this->dropDownLists["FPS_LIMIT"] = new gui::DropDownList(
        mmath::p2pX(82.5, this->Iwindow->getSize().x),
        mmath::p2pX(33, this->Iwindow->getSize().y),
        mmath::p2pX(15, this->Iwindow->getSize().x),
        mmath::p2pX(6, this->Iwindow->getSize().y),
        font, this->IstateData->characterSize_game, fps_limits.data(), fps_limits.size());

    // init shapes for textbox
    for (int i = 0; i < 5; i++) {
        this->text_shapes.push_back(sf::RectangleShape());
        this->text_shapes[i].setFillColor(sf::Color::Transparent);
        this->text_shapes[i].setOutlineColor(sf::Color::White);
        this->text_shapes[i].setOutlineThickness(-1);
        this->text_shapes[i].setPosition(sf::Vector2f(
            mmath::p2pX(20 * i, this->Iwindow->getSize().x),
            mmath::p2pX(33, this->Iwindow->getSize().y) - mmath::p2pX(5, this->Iwindow->getSize().y)));
        this->text_shapes[i].setSize(sf::Vector2f(
            mmath::p2pX(20, this->Iwindow->getSize().x),
            mmath::p2pX(5, this->Iwindow->getSize().y)));
    }

    // init text for settings
    for (int x = 0; x < 5; x++) {
        this->settings_list.push_back(sf::Text());
    }

    this->settings_list[0].setString("Resolution");
    this->settings_list[1].setString("Fullscreen");
    this->settings_list[2].setString("Vsync");
    this->settings_list[3].setString("Antialiasing");
    this->settings_list[4].setString("Framerate limit");

    for (int x = 0; x < 5; x++) {
        this->settings_list[x].setFillColor(sf::Color::White);
        this->settings_list[x].setFont(this->font);
        this->settings_list[x].setCharacterSize(this->IstateData->characterSize_game);
        this->settings_list[x].setPosition(sf::Vector2f(
            this->text_shapes[x].getPosition().x + (this->text_shapes[x].getGlobalBounds().width / 2) - (this->settings_list[x].getGlobalBounds().width / 2),
            this->text_shapes[x].getPosition().y + (this->text_shapes[x].getGlobalBounds().height / 2) - (this->settings_list[x].getGlobalBounds().height / 2)));
    }
}

void SettingsState::resetGui()
{
    // reser to new resolution and save it to file
    this->IstateData->gfxSettings->saveToFile(myConst::config_window);
    // reset gui
    this->IstateData->gfxSettings->resolution = this->video_modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
    this->IstateData->gfxSettings->frameRateLimit = this->framerates_list[this->dropDownLists["FPS_LIMIT"]->getActiveElementId()];
    this->Iwindow->create(this->IstateData->gfxSettings->resolution, this->IstateData->gfxSettings->title, sf::Style::Titlebar | sf::Style::Close);
    this->Iwindow->setFramerateLimit(this->framerates_list[this->dropDownLists["FPS_LIMIT"]->getActiveElementId()]);

    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();

    // clear drop down lists with video modes
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
        delete it2->second;
    this->dropDownLists.clear();

    // clear drop down list with fps limit
    auto it3 = this->dropDownLists.begin();
    for (it3 = this->dropDownLists.begin(); it3 != this->dropDownLists.end(); ++it3)
        delete it3->second;
    this->dropDownLists.clear();

    this->reCaclulateCharacterSize();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initGui();
    this->initKeybinds();
}

SettingsState::~SettingsState()
{
    // clear buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;
    this->buttons.clear();

    // clear drop down lists
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
        delete it2->second;
    this->dropDownLists.clear();
}

// Functions
void SettingsState::updateInput(const float& delta_time)
{
    // update esc key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("KEY_BACK"))) && this->getKeytime())
        this->endState();
}

void SettingsState::updateGui(const float& delta_time)
{
    // update all gui in the state and handle functionality
    for (auto& it : this->buttons)
        it.second->update(this->mousePosWindow);
    // update drop down list and handle functionality
    for (auto& it : this->dropDownLists)
        it.second->update(this->mousePosWindow, delta_time);
    // quit the game
    if (this->buttons["BACK_BTN"]->isPressed() && this->getKeytime())
        this->endState();
    // apply settings
    if (this->buttons["APPLY_BTN"]->isPressed() && this->getKeytime())
        this->resetGui();

    if (this->debugMode) {
        this->dString_Stream
            << "Ver: " << versionApp
            << "\nFPS:\t" << 1 / delta_time
            << "\nResolution: " << this->IstateData->sWindow->getSize().x << "x" << this->IstateData->sWindow->getSize().y
            << "\nSize of state: " << sizeof(*this) << " bytes"
            << "\nkeytime: " << this->Ikeytime
            << "\nMouse pos: " << this->mousePosWindow.x << " " << this->mousePosWindow.y;
        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
}

void SettingsState::update(const float& delta_time)
{
    this->updateMousePositions();
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateGui(delta_time);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
    // render all gui in the state
    for (auto& bt : this->buttons)
        bt.second->render(target);
    // render drop down list
    for (auto& dl : this->dropDownLists)
        dl.second->render(target);
    // draw text
    for (auto& t : this->settings_list)
        target.draw(t);

    // debug
    // draw this->text_shapes
    for (auto& ts : this->text_shapes)
        target.draw(ts);
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);
    this->renderGui(target);

    target.draw(this->dText);
}