#include "PauseMenu.hpp"

PauseMenu::PauseMenu(sf::VideoMode vm, sf::Font& font)
    : font(font)
{
    // logger
    Logger::log("PauseMenu constructor", "PauseMenu");
    // Init background
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    this->background.setFillColor(sf::Color(30, 30, 30, 100));

    // Init container
    this->container.setSize(sf::Vector2f(
        static_cast<float>(vm.width) / 2.5f,
        static_cast<float>(vm.height) - mmath::p2pY(9.3f, vm)));

    this->container.setFillColor(sf::Color(30, 30, 30, 180));
    this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, 30.f);

    // Init text
    this->menuText.setFont(this->font);
    this->menuText.setFillColor(sf::Color(200, 200, 200, 255));
    this->menuText.setCharacterSize(mmath::calcCharSize(vm));
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + mmath::p2pY(4.f, vm));
}


PauseMenu::~PauseMenu()
{
    // logger
    Logger::log("PauseMenu destructor", "PauseMenu");

    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
    return this->buttons;
}

// Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(std::string key, float y, float width, float height, unsigned char_size, std::string text)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new gui::Button(
        sf::Vector2f(x, y), sf::Vector2f(width, height),
        this->font, text, 60,
        sf::Color(170, 170, 170, 200), sf::Color(250, 250, 250, 250), sf::Color(120, 120, 120, 150),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
    for (auto& i : this->buttons) {
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(this->background);
    target.draw(this->container);

    for (auto& i : this->buttons) {
        i.second->render(target);
    }
    target.draw(this->menuText);
}