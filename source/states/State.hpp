#ifndef CPP_STATE_CORESTATE_HPP
#define CPP_STATE_CORESTATE_HPP

#include "../GUI/GUISYS.hpp"
#include "../math/mymath.hpp"
#include "../source/mypars/parsJSON.hpp"
#include "gfx.hpp"

namespace mypars {
class parsJSON;
};

/// @brief Forward declaration of State class
class State;
/// @brief Class for state data
class StateData {
public:
    StateData()
    {
        this->sWindow = NULL;
        this->supportedKeys = NULL;
        this->sStates = NULL;
        this->gfxSettings = NULL;
    }

    float grid_size;
    sf::RenderWindow* sWindow;
    sf::Font font;
    sf::Font debugFont;
    GraphicsSettings* gfxSettings;

    std::stack<State*>* sStates;
    std::map<std::string, int>* supportedKeys;
    unsigned int characterSize_debug;
    unsigned int characterSize_game_big;
    unsigned int characterSize_game_medium;
    unsigned int characterSize_game_small;
    bool reserGUI;
};

/// @brief Abstract class for game states
class State {
private:
protected:
    // Variables
    StateData* IstateData;
    std::stack<State*>* Istates;
    sf::RenderWindow* Iwindow;
    std::map<std::string, int>* IsupportedKeys;
    std::map<std::string, int> Ikeybinds;

    // Resources
    bool Iquit;
    bool Ipaused;
    float Ikeytime;
    float IkeytimeMax;
    float IgridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    std::stringstream dString_Stream;
    sf::Text dText;
    bool debugMode;
    std::map<std::string, sf::Texture> textures;

    // Functions
    virtual void initKeybinds() = 0;
    void reCaclulateCharacterSize();

public:
    State(StateData* state_data);
    virtual ~State();

    // Accessors
    const bool& getQuit() const { return this->Iquit; }
    const bool getKeytime();

    // Functions
    void endState() { this->Iquit = true; }
    void pauseState() { this->Ipaused = true; }
    void unpauseState() { this->Ipaused = false; }

    virtual void updateMousePositions(sf::View* view = NULL);
    virtual void updateKeytime(const float& delta_time);
    virtual void updateInput(const float& delta_time) = 0;
    virtual void update(const float& delta_time) = 0;
    virtual void render(sf::RenderWindow& target) = 0;
};
#endif