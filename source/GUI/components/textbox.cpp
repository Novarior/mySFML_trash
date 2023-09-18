#include "textbox.hpp"

gui::Textbox::Textbox(sf::Vector2f pos, sf::Vector2f size,
    sf::Font& font, std::string text, int charSize,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
    : font(font)
{
    this->limit = false;
    this->limitChar = 10;
    this->focused = false;

    this->shape.setPosition(pos);
    this->shape.setSize(size);
    this->shape.setFillColor(idleColor);

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(charSize);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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

void gui::Textbox::setFont(sf::Font& font)
{
    this->text.setFont(font);
}

void gui::Textbox::setPosition(sf::Vector2f pos)
{
    this->shape.setPosition(pos);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);
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
        if (input->KeyPressed) {
            int charTyped = input->text.unicode;
            if (charTyped < 128) {
                if (this->limit) {
                    if (this->str.length() <= this->limitChar) {
                        this->inputLogic(charTyped);
                    } else if (this->str.length() > this->limitChar && charTyped == sf::Keyboard::Delete) {
                        this->deleteLastChar();
                    }
                } else {
                    this->inputLogic(charTyped);
                }
            }
        }
    }
}

void gui::Textbox::inputLogic(int charTyped)
{ // if not presse some keys
    if (charTyped != sf::Keyboard::Delete && charTyped != sf::Keyboard::Enter && charTyped != sf::Keyboard::Escape) {
        if (charTyped != sf::Keyboard::BackSpace && charTyped != sf::Keyboard::LAlt)
            if (charTyped != sf::Keyboard::LControl && charTyped != sf::Keyboard::LShift && charTyped != sf::Keyboard::Tab) {

                this->str += static_cast<char>(charTyped);
                if (this->str.length() > 0) {
                    if (this->str[this->str.length() - 1] == '.' || this->str[this->str.length() - 1] == ',' || this->str[this->str.length() - 1] == ';')
                        this->deleteLastChar();
                    if (this->str[this->str.length() - 1] == '\0' || this->str[this->str.length() - 1] == '\n' || this->str[this->str.length() - 1] == '\t')
                        this->deleteLastChar();
                    if (this->str[this->str.length() - 1] == ':' || this->str[this->str.length() - 1] == '!' || this->str[this->str.length() - 1] == '?')
                        this->deleteLastChar();
                    if (charTyped == 1 || charTyped == 95 || charTyped == 2 || charTyped == 94 || charTyped == 6)
                        this->deleteLastChar();
                    if (charTyped == 2 || charTyped == 94)
                        //  this->deleteLastChar();

                        if (charTyped == sf::Keyboard::Space)
                            this->deleteLastChar();
                }
            }
    } else if (charTyped == sf::Keyboard::Delete) {
        if (this->str.length() > 0) {
            this->deleteLastChar();
        }
    }

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