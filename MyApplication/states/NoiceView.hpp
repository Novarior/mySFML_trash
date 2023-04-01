#ifndef CPP_STATE_NOICEVIEW_HPP
#define CPP_STATE_NOICEVIEW_HPP
#include "State.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "../GUI/GUISYS.hpp"
#define DB_PERLIN_IMPL
#include "../math/noice.hpp"
class NoiceView: public State
{
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

    short tick;
    int gridSizeX, gridSizeY;
    sf::Vector2f closeGrid;
    bool isGeneratorClosed;


    void initKeybinds();
    void initButton();

    void createStepByStep(sf::Vector2f pos);
    public:
    NoiceView(StateData* statedata);
    virtual ~NoiceView();


    void updateInput(const float& delta_time);
    void update(const float& delta_time);
    void render(sf::RenderWindow* target);
};
#endif