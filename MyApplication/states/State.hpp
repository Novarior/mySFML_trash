#ifndef CPP_STATE_CORESTATE_HPP
#define CPP_STATE_CORESTATE_HPP

#include "../GUI/GUISYS.hpp"
#include "../header.h"
#include "../math/mymath.hpp"
#include "gfx.hpp"
// include parser
#include "../source/mypars/parsJSON.hpp"

/// @brief Forward declaration of State class
class State;
/// @brief Class for state data
class StateData {
public:
    StateData() { }

    float grid_size;
    sf::RenderWindow* sWindow;
    sf::Font font;
    sf::Font debugFont;
    GraphicsSettings* gfxSettings;
    mypars::parsJSON* parser;
    std::stack<State*>* sStates;
    std::map<std::string, int>* supportedKeys;
};

/// @brief Abstract class for game states
class State {
private:
protected:
    StateData* IstateData;
    std::stack<State*>* Istates;
    sf::RenderWindow* Iwindow;
    std::map<std::string, int>* IsupportedKeys;
    std::map<std::string, int> Ikeybinds;
    mypars::parsJSON* Iparser;

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
    // Resources
    std::map<std::string, sf::Texture> textures;

    // Functions
    virtual void initKeybinds() = 0;

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