#ifndef CPP_SETTINGS_STATE_HPP
#define CPP_SETTINGS_STATE_HPP

#include "State.hpp"

/// @brief  Class for the settings state
/// @note   Inherited from the State class
/// @retval None
class SettingsState : public State {
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;
    std::vector<sf::VideoMode> video_modes;

    // Initializer functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    /// @brief Constructor for SettingsState
    /// @param state_data
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    // Functions
    void updateInput(const float& delta_time);
    void updateGui(const float& delta_time);
    void update(const float& delta_time);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderWindow& target);
};

#endif // CPP_SETTINGS_STATE_HPP