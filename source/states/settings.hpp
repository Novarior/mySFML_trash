#ifndef CPP_SETTINGS_STATE_HPP
#define CPP_SETTINGS_STATE_HPP

#include "State.hpp"

/// @brief  Class for the settings state
/// @note   Inherited from the State class
/// @retval None
class SettingsState : public State {
private:
    // logger
    Logger myLogger_settings;

    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
    // Resouses for settings
    std::vector<sf::VideoMode> video_modes;
    std::vector<int> framerates_list;
    std::vector<int> antialiasing_list;
    std::vector<int> vsync_list;
    std::vector<int> fullscreen_list;

    std::vector<sf::Text> settings_list;
    std::vector<sf::RectangleShape> text_shapes;
    // Gui selectors
    gui::Selector* selector_resolutions;
    gui::Selector* selector_framerates;
    gui::Selector* selector_antialiasing;
    gui::Selector* selector_vsync;
    gui::Selector* selector_fullscreen;

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