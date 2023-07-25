#ifndef CPP_SETTINGS_STATE_HPP
#define CPP_SETTINGS_STATE_HPP

#include "State.hpp"

class SettingsState : public State
{
    private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

    public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderWindow& target );
};

#endif //CPP_SETTINGS_STATE_HPP