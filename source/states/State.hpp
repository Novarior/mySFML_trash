#ifndef CPP_STATE_CORESTATE_HPP
#define CPP_STATE_CORESTATE_HPP

#include "../GUI/GUISYS.hpp"
#include "../math/mymath.hpp"
#include "../source/mypars/parsJSON.hpp"
#include "../staticFPSMetter.hpp"
#include "VolumeManager.hpp"
#include "gfx.hpp"

// Forward declaration of State class
class State;

// Class for state data
// This class holds data that is shared across different states
class StateData {
public:
    // Constructor initializes all pointers to nullptr
    StateData()
    {
        this->sWindow = nullptr;
        this->supportedKeys = nullptr;
        this->sStates = nullptr;
        this->gfxSettings = nullptr;
        this->sEvent = nullptr;
    }

    float grid_size; // Size of the grid
    sf::RenderWindow* sWindow; // Pointer to the SFML window
    sf::Font font; // Font used in the game
    sf::Font debugFont; // Font used for debugging
    GraphicsSettings* gfxSettings; // Pointer to the graphics settings

    std::stack<State*>* sStates; // Stack of states
    std::map<std::string, int>* supportedKeys; // Map of supported keys
    unsigned int characterSize_debug; // Character size for debug text
    unsigned int characterSize_game_big; // Character size for big game text
    unsigned int characterSize_game_medium; // Character size for medium game text
    unsigned int characterSize_game_small; // Character size for small game text
    bool reserGUI; // Flag to reset GUI

    sf::Event* sEvent; // Pointer to the SFML event
};

// Abstract class for game states
class State {
private:
protected:
    // Variables
    StateData* IstateData; // Pointer to shared state data
    std::stack<State*>* Istates; // Stack of states
    sf::RenderWindow* Iwindow; // Pointer to the SFML window
    sf::Event* Ievent; // Pointer to the SFML event
    std::map<std::string, int>* IsupportedKeys; // Map of supported keys
    std::map<std::string, int> Ikeybinds; // Map of key bindings
    std::unique_ptr<VolumeManager> IvolumeManager; // Volume manager

    // Resources
    bool Iquit; // Flag to quit the state
    bool Ipaused; // Flag to pause the state
    float Ikeytime; // Time since last key press
    float IkeytimeMax; // Maximum time between key presses
    float IgridSize; // Size of the grid

    sf::Vector2i mousePosScreen; // Position of the mouse on the screen
    sf::Vector2i mousePosWindow; // Position of the mouse in the window
    sf::Vector2f mousePosView; // Position of the mouse in the view
    sf::Vector2i mousePosGrid; // Position of the mouse on the grid

    std::stringstream dString_Stream; // Stream for debug string
    sf::Text dText; // Debug text
    bool debugMode; // Flag for debug mode
    std::map<std::string, sf::Texture> textures; // Map of textures

    // Functions
    virtual void initKeybinds() = 0; // Initialize key bindings (pure virtual function)
    void reCaclulateCharacterSize(); // Recalculate character size

public:
    // Constructor
    State(StateData* state_data);
    // Destructor
    virtual ~State();

    // Accessors
    const bool& getQuit() const { return this->Iquit; } // Get quit flag
    const bool getKeytime(); // Get key time

    // Functions
    void endState() { this->Iquit = true; } // End the state
    void pauseState() { this->Ipaused = true; } // Pause the state
    void unpauseState() { this->Ipaused = false; } // Unpause the state

    // update sounds (virtual function)
    virtual void updateSounds(const float& delta_time) = 0;
    // Update mouse positions (virtual function)
    virtual void updateMousePositions(sf::View* view = NULL);
    // Update key time (virtual function)
    virtual void updateKeytime(const float& delta_time);
    // Update input (pure virtual function)
    virtual void updateInput(const float& delta_time) = 0;
    // Update the state (pure virtual function)
    virtual void update(const float& delta_time) = 0;
    // Render the state (pure virtual function)
    virtual void render(sf::RenderWindow& target) = 0;
};
#endif