#ifndef CPP_MAINMENU_CORESTATE_HPP
#define CPP_MAINMENU_CORESTATE_HPP

#include "../Content/rotationCircle.hpp"
#include "../GUI/GUISYS.hpp"
#include "NoiceView.hpp"
#include "Process.hpp"
#include "State.hpp"
#include "settings.hpp"

class MainMenu : public State {
private:
    sf::RectangleShape background;
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    std::map<std::string, gui::Button*> buttons;
    std::vector<RotarionCircle*> rotationCyrcleShape;

    std::vector<sf::RectangleShape> debug_shapes;

    void initRenderDefines();
    void initKeybinds();
    void initView();
    void initBackground();
    void initButtons();
    void initBlocks();
    void initGUI();
    void resetGUI();

    // elements for start
    sf::RectangleShape fadeShape;
    bool isstatred;
    void initStartProcces();
    void updateStartProcces();
    void resetView();

public:
    MainMenu(StateData* sDate);
    virtual ~MainMenu();

    void updateInput(const float& delta_time);
    void updateButtons();
    void update(const float& delta_time);
    void render(sf::RenderWindow& target);
};
#endif