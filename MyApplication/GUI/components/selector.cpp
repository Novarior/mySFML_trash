#include "selector.hpp"
namespace gui {
Selector::Selector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, std::string list[], unsigned nrOfElements)
    : keytime(0.f)
    , keytimeMax(1.f)
    , activeElement(0)
{
    this->box.setPosition(pos);
    this->box.setSize(size);
    this->box.setFillColor(sf::Color::Transparent);
    this->box.setOutlineColor(sf::Color::White);
    this->box.setOutlineThickness(-2.f);

    this->buttons["left"] = new gui::Button(
        sf::Vector2f(this->box.getPosition().x - (size.x / 3.f), pos.y),
        sf::Vector2f(size.x / 3.f, size.y),
        font, "<", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

    this->buttons["right"] = new gui::Button(
        sf::Vector2f(this->box.getPosition().x + this->box.getSize().x, pos.y),
        sf::Vector2f(size.x / 3.f, size.y),
        font, ">", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
}

Selector::~Selector()
{
}

unsigned Selector::getActiveElementID() const
{
    return 0;
}

void Selector::update(const float& delta_time, const sf::Vector2i& mousePos)
{
    for (auto& it : this->buttons)
        it.second->update(mousePos);

    this->updateKeyTime(delta_time);

    if (this->buttons["left"]->isPressed() && this->getKeytime()) {
        if (this->activeElement > 0)
            activeElement--;
        else
            activeElement = this->list.size() - 1;
    } else if (this->buttons["right"]->isPressed() && this->getKeytime()) {
        if (this->activeElement < this->list.size() - 1)
            activeElement = 0;
        else
            activeElement++;
    }
}

void Selector::updateKeyTime(const float& delta_time)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += delta_time;
}

const bool Selector::getKeytime()
{
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void Selector::render(sf::RenderTarget& target)
{
    target.draw(this->box);

    for (auto& it : this->buttons)
        it.second->render(target);
}
}