#include "staticSelector.hpp"
namespace gui {
// private functions
void StaticSelector::updateKeyTime(const float& delta_time)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += delta_time;
}

const bool StaticSelector::getKeytime()
{
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

StaticSelector::StaticSelector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font,
    unsigned int character_size, float current_value, float max_value, float change_step)
    : valueMax(max_value)
    , keytimeMax(0.2f)
    , keytime(0.f)
    , value(current_value)
    , sizeStep(change_step)
{
    // init box
    this->box.setPosition(pos.x + (mmath::p2pX(10, size.x)), pos.y);
    this->box.setSize(sf::Vector2f(size.x - (mmath::p2pX(20, size.x)), size.y));
    this->box.setFillColor(sf::Color(50, 50, 50, 100));
    // init text
    this->text.setFont(font);
    this->text.setCharacterSize(character_size);
    this->text.setFillColor(sf::Color(255, 255, 255, 200));
    this->text.setPosition(
        this->box.getPosition().x + this->box.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->box.getPosition().y + this->box.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);
    // init value's

    // init buttons
    this->buttons["left"] = new gui::Button(
        sf::Vector2f(pos.x, pos.y),
        sf::Vector2f(mmath::p2pX(10, size.x), size.y),
        font, "-", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

    this->buttons["right"] = new gui::Button(
        sf::Vector2f(this->box.getPosition().x + this->box.getSize().x, pos.y),
        sf::Vector2f(mmath::p2pX(10, size.x), size.y),
        font, "+", 30,
        sf::Color::White, sf::Color(200, 200, 200, 200), sf::Color(150, 150, 150, 200),
        sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
}

StaticSelector::~StaticSelector()
{
    for (auto& it : this->buttons)
        delete it.second;
}

// accessors
const float StaticSelector::getCurrentValue()
{
    return this->value;
}
void StaticSelector::setCurrentValue(const float value)
{
    this->value = value;
}
void StaticSelector::setSizeStep(const float size_step)
{
    this->sizeStep = size_step;
}

const bool StaticSelector::isValueChanged()
{
    return this->ValueIsChanged;
}

void StaticSelector::closeChangeValue()
{
    this->ValueIsChanged = false;
}

void StaticSelector::update(const float& delta_time, const sf::Vector2i& mousePos)
{
    this->updateKeyTime(delta_time);

    for (auto& it : this->buttons)
        it.second->update(mousePos);

    if (this->buttons["left"]->isPressed() && this->getKeytime()) {
        if (this->value > -this->valueMax)
            this->value -= this->sizeStep;
        else
            this->value = this->valueMax;

        this->ValueIsChanged = true;
    }

    if (this->buttons["right"]->isPressed() && this->getKeytime()) {
        if (this->value < this->valueMax)
            this->value += this->sizeStep;
        else
            this->value = -this->valueMax;

        this->ValueIsChanged = true;
    }
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << this->value;
    this->text.setString(ss.str());
    this->text.setPosition(
        this->box.getPosition().x + this->box.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->box.getPosition().y + this->box.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);
}

// render
void StaticSelector::render(sf::RenderTarget& target)
{
    target.draw(this->box);
    for (auto& it : this->buttons)
        it.second->render(target);
    target.draw(this->text);
}
}
// namespace gui