#ifndef CPP_GUI_TABMENU_HPP
#define CPP_GUI_TABMENU_HPP

#include "../header.h"
#include "GUISYS.hpp"

namespace gui
{
class TabMenu
{
private:
    sf::RectangleShape tabshape;
    std::map<std::string, gui::Button*> buttons;
    bool isopen;

public:
    TabMenu(sf::Vector2u windowsize);
    virtual ~TabMenu();

    void addButton(std::string keyButton, gui::Button* button);
    void opentab();
    void closetab();
    const bool isOpen();
    void toggleSwitch();

    const bool isPressed(std::string key_button);


    void updateButtons(sf::Vector2i mousePosWindow);
    void update(const float& deltatime,sf::Vector2i mousePosWindow);
    void render(sf::RenderTarget* target);
};
}
#endif