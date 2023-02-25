#include "tabMenu.hpp"
using namespace gui;

TabMenu::TabMenu(sf::Vector2u windowsize)
{
    this->tabshape.setSize(sf::Vector2f(windowsize.x/5,windowsize.y));
    this->tabshape.setPosition(sf::Vector2f(windowsize.x-this->tabshape.getSize().x,0));
    this->tabshape.setFillColor(sf::Color(80,80,80,100));
    this->tabshape.setOutlineThickness(-3.f);
    this->tabshape.setOutlineColor(sf::Color(100,100,100,100));
}

TabMenu::~TabMenu()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
    this->buttons.clear();
}

void TabMenu::addButton(std::string keyButton, gui::Button* button)
{
    this->buttons[keyButton]= button;
}

void TabMenu::toggleSwitch()
{
    this->isopen = !this->isopen;
}

void TabMenu::opentab()
{
    this->isopen = true;
}

void TabMenu::closetab()
{
    this->isopen = false;
}

const bool TabMenu::isOpen()
{
    return this->isopen;
}

const bool TabMenu::isPressed(std::string key_button)
{
    if(this->buttons[key_button]->isPressed())
        return true;

    return false;
}

void TabMenu::updateButtons(sf::Vector2i mousePosWindow)
{
    for(auto it :this->buttons)
        it.second->update(mousePosWindow);
}

void TabMenu::update(const float& deltatime,sf::Vector2i mousePosWindow)
{
    this->updateButtons(mousePosWindow);
}

void TabMenu::render(sf::RenderTarget* target)
{
    target->draw(this->tabshape);

      for(auto&it:this->buttons)
       it.second->render(target);
}