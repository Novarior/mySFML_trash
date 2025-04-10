#include "button.hpp"

gui::Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font &font,
                    std::string text, unsigned character_size,
                    sf::Color text_idle_color, sf::Color text_hover_color,
                    sf::Color text_active_color, sf::Color idle_color,
                    sf::Color hover_color, sf::Color active_color,
                    sf::Color outline_idle_color, sf::Color outline_hover_color,
                    sf::Color outline_active_color, short unsigned id)
    : text(font, text, character_size) {
  this->buttonState = BTN_IDLE;
  this->id = id;

  this->shape.setPosition(sf::Vector2f(pos.x, pos.y));
  this->shape.setSize(sf::Vector2f(size.x, size.y));
  this->shape.setFillColor(idle_color);
  this->shape.setOutlineThickness(-1.f);
  this->shape.setOutlineColor(outline_idle_color);

  this->text.setFillColor(text_idle_color);
  this->text.setPosition({this->shape.getPosition().x +
                              (this->shape.getGlobalBounds().size.x / 2.f) -
                              this->text.getGlobalBounds().size.x / 2.f,
                          this->shape.getPosition().y +
                              this->text.getGlobalBounds().size.y / 2.f});

  this->textIdleColor = text_idle_color;
  this->textHoverColor = text_hover_color;
  this->textActiveColor = text_active_color;

  this->idleColor = idle_color;
  this->hoverColor = hover_color;
  this->activeColor = active_color;

  this->outlineIdleColor = outline_idle_color;
  this->outlineHoverColor = outline_hover_color;
  this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button() {}

// Accessors
const bool gui::Button::isPressed() const {
  if (this->buttonState == BTN_ACTIVE)
    return true;
  return false;
}

const bool gui::Button::isHover() const {
  if (this->buttonState == BTN_HOVER)
    return true;
  return false;
}

const std::string gui::Button::getText() const {
  return this->text.getString();
}

const short unsigned &gui::Button::getId() const { return this->id; }

// Modifiers
void gui::Button::setText(const std::string text) {
  this->text.setString(text);
}

void gui::Button::setId(const short unsigned id) { this->id = id; }

// Functions
void gui::Button::update(const sf::Vector2i &mousePosWindow) {
  /*Update the booleans for hover and pressed*/
  // Idle
  this->buttonState = gui::BTN_IDLE;
  // Hover
  if (this->shape.getGlobalBounds().contains(
          static_cast<sf::Vector2f>(mousePosWindow))) {
    this->buttonState = gui::BTN_HOVER;

    // Pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
      this->buttonState = gui::BTN_ACTIVE;
  }

  switch (this->buttonState) {
  case gui::BTN_IDLE:
    this->shape.setFillColor(this->idleColor);
    this->text.setFillColor(this->textIdleColor);
    this->shape.setOutlineColor(this->outlineIdleColor);
    break;

  case gui::BTN_HOVER:
    this->shape.setFillColor(this->hoverColor);
    this->text.setFillColor(this->textHoverColor);
    this->shape.setOutlineColor(this->outlineHoverColor);
    break;

  case gui::BTN_ACTIVE:
    this->shape.setFillColor(this->activeColor);
    this->text.setFillColor(this->textActiveColor);
    this->shape.setOutlineColor(this->outlineActiveColor);
    break;

  default:
    this->shape.setFillColor(sf::Color::Red);
    this->text.setFillColor(sf::Color::Blue);
    this->shape.setOutlineColor(sf::Color::Green);
    break;
  }
}
