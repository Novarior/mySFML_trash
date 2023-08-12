#include "selector.hpp"
namespace gui {
Selector::Selector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned int character_size, 
std::string list[], unsigned nrOfElements, unsigned default_active_element)
    : keytime(0.f)
    , keytimeMax(0.3f)
{
    // init box
    this->box.setPosition(pos);
    this->box.setSize(size);
    this->box.setFillColor(sf::Color::Transparent);
    this->box.setOutlineColor(sf::Color::Transparent);
    this->box.setOutlineThickness(-2.f);

    // init buttons
    this->buttons["left"] = new gui::Button(
        sf::Vector2f(this->box.getPosition().x - (size.x / 5.f), pos.y),
        sf::Vector2f(size.x / 5, size.y),
        font, "- ", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

    this->buttons["right"] = new gui::Button(
        sf::Vector2f(this->box.getPosition().x + this->box.getSize().x, pos.y),
        sf::Vector2f(size.x / 6.f, size.y),
        font, "+", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

    // init text
    this->text.setFont(font);
    this->text.setString(list[0]);
    this->text.setPosition(
        this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(character_size);

    // init list
    for (size_t i = 0; i < nrOfElements; i++)
        this->list.push_back(list[i]);

    // init active element
    this->activeElement = default_active_element;
    this->text.setString(this->list[this->activeElement]);
}

Selector::~Selector()
{
    for (auto& it : this->buttons)
        delete it.second;
}

unsigned Selector::getActiveElementID() const
{
    return this->activeElement;
}

std::string Selector::getActiveElement() const
{
    return this->list[this->activeElement];
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
        this->text.setString(this->list[this->activeElement]);
    } else if (this->buttons["right"]->isPressed() && this->getKeytime()) {
        if (this->activeElement >= this->list.size() - 1)
            activeElement = 0;
        else
            activeElement++;
        this->text.setString(this->list[this->activeElement]);
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

    target.draw(this->text);
}
}