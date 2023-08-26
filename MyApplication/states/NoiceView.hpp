#ifndef CPP_STATE_NOICEVIEW_HPP
#define CPP_STATE_NOICEVIEW_HPP

#include "../GUI/GUISYS.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "State.hpp"

class NoiceView : public State {
private:
    struct {
        int grass = 0;
        int dirt = 0;
        int sand = 0;
        int rock = 0;
        int ocean = 0;
        int mud = 0;
        int other = 0;
    } m_BlocksCounter;

    noiceData noicedata;
    ProcessGenerationNoice* myGN;
    sf::Image image;
    sf::Texture texture;
    sf::RectangleShape shape;
    std::map<std::string, gui::Button*> buttons;
    bool showTabmenu;
    sf::RectangleShape tabShape;
    std::map<std::string, gui::StaticSelector*> staticSelector;
    gui::Selector* selector;


    int gridSizeX, gridSizeY;
    sf::Vector2f closeGrid;
    bool isGeneratorClosed;

    void initKeybinds();
    void initButton();

    void createStepByStep(sf::Vector2f pos);

public:
    NoiceView(StateData* statedata, bool quick);
    virtual ~NoiceView();

    void updateInput(const float& delta_time);
    void update(const float& delta_time);
    void renderTabMenu(sf::RenderTarget& target);
    void render(sf::RenderWindow& target);
};
#endif