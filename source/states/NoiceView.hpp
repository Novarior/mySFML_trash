#ifndef CPP_STATE_NOICEVIEW_HPP
#define CPP_STATE_NOICEVIEW_HPP

#include "../GUI/GUISYS.hpp"
#include "../math/LSystem.hpp"
#include "State.hpp"
#include "editModes/NoiceViewer.hpp"

class NoiceView : public State {
private:
    // Variables
    NoiceViewer* m_NoiceViewer;
    mmath::noiceData m_noiceData;
    // trees
    LSystem* myLS;

    // gui elements (buttons, selectors, etc)
    bool showTabmenu;
    std::map<std::string, gui::Button*> buttons;
    sf::RectangleShape tabShape;
    std::map<std::string, gui::StaticSelector*> staticSelector;
    gui::Selector* selector;

    int current_View_Generator = 0;

    // init functions
    void initKeybinds();
    void initButtons();
    void initSelectors();
    void initTabMenu();
    void initNoice();
    void initDebugText();

    // update functions
    void saveTreeAsImage(sf::RenderWindow& window);
    sf::IntRect findNonTransparentRect(const sf::Image& image);

    void updateInput(const float& delta_time);
    void NewFunction();
    void updateButtons(const float& delta_time);
    void updateDebugText(const float& delta_time);

    // render functions
    void renderTabMenu(sf::RenderTarget& target);

public:
    NoiceView(StateData* statedata);
    virtual ~NoiceView();

    void update(const float& delta_time);
    void render(sf::RenderWindow& target);
};
#endif