#ifndef GUI_SIMPLE_TEXTBOX_H
#define GUI_SIMPLE_TEXTBOX_H
#include "../../core/header.h"

namespace gui {
class Textbox {
public:
    Textbox(sf::Vector2f pos, sf::Vector2f size,
        sf::Font& font, std::string text, int charSize,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    virtual ~Textbox();

    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);

    void setString(std::string str);
    std::string getString();

    void setLimit(bool ToF);
    void setLimit(bool ToF, int lim);

    void setFont(sf::Font& font);
    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setCharSize(int size);
    void setColors(sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    void setFocus(bool focus);
    bool getFocus();

    void typedOn(sf::Event* input);

private:
    sf::RectangleShape shape;
    sf::Font& font;
    sf::Text text;

    std::string str;
    bool limit;
    int limitChar;

    bool focused;
    bool active;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    // Private functions

    void inputLogic(int charTyped);
    void deleteLastChar();
};
}

#endif // GUI_TEXTBOX_H