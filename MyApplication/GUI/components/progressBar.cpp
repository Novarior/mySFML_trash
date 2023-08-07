#include "progressBar.hpp"

gui::ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size,
    sf::Color inner_color, unsigned character_size,
    sf::Vector2f resolution, sf::Font& font)
{

    this->back.setSize(size);
    this->back.setFillColor(sf::Color(50, 50, 50, 200));
    this->back.setPosition(pos);

    this->inner.setSize(size);
    this->inner.setFillColor(inner_color);
    this->inner.setPosition(this->back.getPosition());

    this->text.setFont(font);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        this->inner.getPosition().x + resolution.x * 0.53,
        this->inner.getPosition().y + resolution.y * 0.5);
}

gui::ProgressBar::~ProgressBar() { }

// Functions
void gui::ProgressBar::update(const int current_value, const int max_value)
{
    float percent = static_cast<float>(current_value) / static_cast<float>(max_value);

    this->inner.setSize(sf::Vector2f(static_cast<float>(floor(max_value * percent)), this->inner.getSize().y));

    this->barString = std::to_string(current_value) + " / " + std::to_string(max_value);
    this->text.setString(this->barString);
}

void gui::ProgressBar::render(sf::RenderTarget& target)
{
    target.draw(this->back);
    target.draw(this->inner);
    target.draw(this->text);
}