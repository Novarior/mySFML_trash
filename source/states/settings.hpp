#ifndef CPP_SETTINGS_STATE_HPP
#define CPP_SETTINGS_STATE_HPP

#include "State.hpp"

/// @brief  Class for the settings state
/// @note   Inherited from the State class
/// @retval None
class SettingsState : public State {
private:
    // Variables
    sf::Texture backgroundTexture; // Texture for the background
    sf::RectangleShape background; // Shape for the background
    sf::Font font; // Font used in the settings state
    std::map<std::string, gui::Button*> buttons; // Map of buttons

    // Resources for settings
    std::vector<sf::VideoMode> video_modes; // List of video modes
    std::vector<int> framerates_list; // List of frame rates
    std::vector<int> antialiasing_list; // List of antialiasing levels
    std::vector<int> vsync_list; // List of VSync options
    std::vector<int> fullscreen_list; // List of fullscreen options
    std::vector<sf::Text> keybindText; // List of keybind texts

    std::vector<sf::Text> settings_list; // List of settings texts
    std::vector<sf::RectangleShape> text_shapes; // List of text shapes
    std::vector<sf::RectangleShape> keybindBackground; // List of keybind backgrounds

    // Gui selectors
    gui::Selector* selector_resolutions; // Selector for resolutions
    gui::Selector* selector_framerates; // Selector for frame rates
    gui::Selector* selector_antialiasing; // Selector for antialiasing levels
    gui::Selector* selector_vsync; // Selector for VSync options
    gui::Selector* selector_fullscreen; // Selector for fullscreen options

    // Initializer functions
    void initVariables(); // Initialize variables
    void initFonts(); // Initialize fonts
    void initKeybinds(); // Initialize key bindings
    void initGui(); // Initialize GUI
    void resetGui(); // Reset GUI

public:
    /// @brief Constructor for SettingsState
    /// @param state_data
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    // Functions
    void updateInput(const float& delta_time); // Update input
    void updateGui(const float& delta_time); // Update GUI
    void update(const float& delta_time); // Update the state
    void renderGui(sf::RenderTarget& target); // Render the GUI
    void render(sf::RenderWindow& target); // Render the state
};

#endif // CPP_SETTINGS_STATE_HPP