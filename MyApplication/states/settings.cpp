#include "settings.hpp"

void SettingsState::initVariables()
{
    this->Iparser = this->IstateData->parser;
    this->video_modes = sf::VideoMode::getFullscreenModes();
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
    this->buttons["BACK_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 120, 0.f), sf::Vector2f(120.f, 50.f), this->IstateData->font, "Back", 30,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(255, 0, 0, 200), sf::Color(255, 0, 0, 250), sf::Color(255, 0, 0, 50), 0);
    // apply gui button
    // set "apply" button position litle bit left from "back" button
    this->buttons["APPLY_BTN"] = new gui::Button(sf::Vector2f(this->Iwindow->getSize().x - 240, 0.f), sf::Vector2f(120.f, 50.f), this->IstateData->font, "Apply", 30,
        sf::Color(100, 100, 100, 200), sf::Color(180, 180, 180, 250), sf::Color(60, 60, 60, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
        sf::Color(0, 255, 0, 200), sf::Color(0, 255, 0, 250), sf::Color(0, 255, 0, 50), 1);

    // init dropdown list with video modes
    std::vector<std::string> modes_str;
    for (auto& i : this->video_modes) {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(400, 300, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::resetGui()
{
    // reser to new resolution and save it to file
    this->IstateData->gfxSettings->saveToFile(myConst::config_window);
    // reset gui
    this->IstateData->gfxSettings->resolution = this->video_modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
    this->Iwindow->create(this->IstateData->gfxSettings->resolution, this->IstateData->gfxSettings->title, sf::Style::Default);

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
}

void SettingsState::update(const float& delta_time)
{
    this->updateMousePositions();
    this->updateInput(delta_time);
    this->updateGui(delta_time);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
    // render all gui in the state
    for (auto& it : this->buttons)
        it.second->render(target);
    // render drop down list
    for (auto& it : this->dropDownLists)
        it.second->render(target);
}

void SettingsState::render(sf::RenderWindow& target)
{
    target.draw(this->background);
    this->renderGui(target);
}