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


    void updateInput(const float& deltatime);
    void update(const float& deltatime);
    void render(sf::RenderWindow* target);
};
#endif