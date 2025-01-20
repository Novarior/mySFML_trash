#include "textbox.hpp"

gui::Textbox::Textbox(sf::Vector2f pos, sf::Vector2f size,
    sf::Font& font, std::string text, int charSize,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
    : text(font, text, charSize)
{
    this->limit = false;
    this->limitChar = 10;
    this->focused = false;

    this->shape.setPosition(pos);
    this->shape.setSize(size);
    this->shape.setFillColor(idleColor);

    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(
        { this->shape.getPosition().x + (this->shape.getGlobalBounds().size.x / 2.f) - this->text.getGlobalBounds().size.y / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().size.x / 2.f) - this->text.getGlobalBounds().size.y / 2.f });

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
}
gui::Textbox::~Textbox()
{
}

void gui::Textbox::update(const sf::Vector2i& mousePos)
{
    this->active = false;

    if (this->shape.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
        this->shape.setFillColor(this->hoverColor);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            this->shape.setFillColor(this->activeColor);
            this->active = true;
            this->focused = true;
        }
    } else {
        this->shape.setFillColor(this->idleColor);
    }
}

void gui::Textbox::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

void gui::Textbox::setString(std::string str)
{
    this->text.setString(str);
}

std::string gui::Textbox::getString()
{
    return this->text.getString();
}

void gui::Textbox::setLimit(bool ToF)
{
    this->limit = ToF;
}

void gui::Textbox::setLimit(bool ToF, int lim)
{
    this->limit = ToF;
    this->limitChar = lim;
}

void gui::Textbox::setPosition(sf::Vector2f pos)
{
    this->shape.setPosition(pos);
    this->text.setPosition(
        { this->shape.getPosition().x + (this->shape.getGlobalBounds().size.x / 2.f) - this->text.getGlobalBounds().size.x / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().size.y / 2.f) - this->text.getGlobalBounds().size.y / 2.f });
}

void gui::Textbox::setSize(sf::Vector2f size)
{
    this->shape.setSize(size);
}

void gui::Textbox::setCharSize(int size)
{
    this->text.setCharacterSize(size);
}

void gui::Textbox::setColors(sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
}

void gui::Textbox::setFocus(bool focus)
{
    this->focused = focus;
}

bool gui::Textbox::getFocus()
{
    return this->focused;
}

void gui::Textbox::typedOn(sf::Event* input)
{
    if (this->focused) {
        if (input->is<sf::Event::TextEntered>()) {
            int charTyped = input->getIf<sf::Event::TextEntered>()->unicode;
            if (charTyped < 128) {
                if (this->limit) {
                    if (this->str.length() <= this->limitChar) {
                        this->inputLogic(charTyped);
                    }
                } else {
                    this->inputLogic(charTyped);
                }
            }
        }
        // Обработка клавиши Delete
        else if (input->is<sf::Event::KeyPressed>()) {
            if (input->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Delete) {
                this->deleteLastChar();
            }
        }
    }
}

void gui::Textbox::inputLogic(int charTyped)
{
    // Игнорируем специальные клавиши, такие как Delete, Enter, Escape
    if (charTyped == static_cast<int>(sf::Keyboard::Key::Delete) || charTyped == static_cast<int>(sf::Keyboard::Key::Enter) || charTyped == static_cast<int>(sf::Keyboard::Key::Escape)) {
        return;
    }

    // Игнорируем модификаторы клавиш и другие спец. клавиши
    if (charTyped == static_cast<int>(sf::Keyboard::Key::Backspace))
        return;
    if (charTyped == static_cast<int>(sf::Keyboard::Key::LAlt))
        return;
    if (charTyped == static_cast<int>(sf::Keyboard::Key::LControl))
        return;
    if (charTyped == static_cast<int>(sf::Keyboard::Key::LShift))
        return;
    if (charTyped == static_cast<int>(sf::Keyboard::Key::Tab))
        return;

    // Добавляем символ в строку
    if (charTyped >= 0 && charTyped <= 127) {
        this->str += static_cast<char>(charTyped);
    }

    // Проверка на нежелательные символы (например, знаки препинания)
    if (!this->str.empty()) {
        char lastChar = this->str[this->str.length() - 1];
        if (lastChar == '.' || lastChar == ',' || lastChar == ';' || lastChar == ':' || lastChar == '!' || lastChar == '?') {
            this->deleteLastChar();
        }
    }

    // Обновляем текст
    this->text.setString(this->str);
}

void gui::Textbox::deleteLastChar()
{
    std::string tempStr = "";

    for (int i = 0; i < this->str.length() - 1; i++) {
        tempStr += this->str[i];
    }

    this->str = tempStr;
    this->text.setString(this->str);
}