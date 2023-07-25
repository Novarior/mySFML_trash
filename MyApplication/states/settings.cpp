#include "settings.hpp"

void SettingsState::initVariables() {
    this->Iparser = this->IstateData->parser;
    this->modes = sf::VideoMode::getFullscreenModes();
}
void SettingsState::initBackground() {
    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)));
    //darkest blue color
    this->background.setFillColor(sf::Color(3, 3, 30, 100));

}
void SettingsState::initFonts() {
    this->font = this->IstateData->font;
}
void SettingsState::initKeybinds(){

}
void SettingsState::initGui() {
}
void SettingsState::resetGui() {
}


SettingsState::SettingsState(StateData* state_data):State(state_data){
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initGui();
    this->initKeybinds();
}

SettingsState::~SettingsState() {
    
}

//Functions
void SettingsState::updateInput(const float& dt) {

}
void SettingsState::updateGui(const float& dt) {

}
void SettingsState::update(const float& dt) {

}
void SettingsState::renderGui(sf::RenderTarget& target) {

}
void SettingsState::render(sf::RenderTarget& target) {

}