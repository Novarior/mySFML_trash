#include "dropDownList.hpp"

gui::DropDownList::DropDownList(float x, float y, float width, float height,
                                sf::Font &font, unsigned char_size,
                                std::string list[], unsigned nrOfElements,
                                unsigned default_index)
    : font(font), showList(false), keytimeMax(1.f), keytime(0.f) {
  this->activeElement = new gui::Button(
      sf::Vector2f(x, y), sf::Vector2f(width, height), this->font,
      list[default_index], char_size, sf::Color(255, 255, 255, 150),
      sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
      sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200),
      sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 200),
      sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

  for (unsigned i = 0; i < nrOfElements; i++)
    this->list.push_back(new gui::Button(
        sf::Vector2f(x, y + ((i + 1) * height)), sf::Vector2f(width, height),
        this->font, list[i], char_size, sf::Color(255, 255, 255, 150),
        sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200),
        sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 0),
        sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0), i));
}

gui::DropDownList::~DropDownList() {
  delete this->activeElement;
  for (size_t i = 0; i < this->list.size(); i++)
    delete this->list[i];
}

// Accessors
const bool gui::DropDownList::getKeytime() {
  if (this->keytime >= this->keytimeMax) {
    this->keytime = 0.f;
    return true;
  }
  return false;
}

const unsigned short &gui::DropDownList::getActiveElementId() const {
  return this->activeElement->getId();
}

// Functions
void gui::DropDownList::updateKeytime(const float &dt) {
  if (this->keytime < this->keytimeMax)
    this->keytime += dt;
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow,
                               const float &dt) {
  this->updateKeytime(dt);

  this->activeElement->update(mousePosWindow);

  // Show and hide the list
  if (this->activeElement->isPressed() && this->getKeytime()) {
    if (this->showList)
      this->showList = false;
    else
      this->showList = true;
  }

  if (this->showList)
    for (auto &i : this->list) {
      i->update(mousePosWindow);

      if (i->isPressed() && this->getKeytime()) {
        this->showList = false;
        this->activeElement->setText(i->getText());
        this->activeElement->setId(i->getId());
      }
    }
}
