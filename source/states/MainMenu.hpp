#ifndef CPP_MAINMENU_CORESTATE_HPP
#define CPP_MAINMENU_CORESTATE_HPP

#include "../GUI/GUISYS.hpp"
#include "EditorState.hpp"
#include "Process.hpp"
#include "State.hpp"
#include "settings.hpp"

class MainMenu : public State {
private:
    // render components
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    std::map<std::string, gui::Button*> buttons;

    std::vector<sf::Texture> background_textures;
    std::vector<sf::RectangleShape> backgrond_shapes;

    void initRenderDefines();
    void initKeybinds();
    void initButtons();
    void initBackground();
    void initGUI();
    void resetGUI();

    // elements for start

    void resetView();

public:
    MainMenu(StateData* sDate);
    virtual ~MainMenu();

    void updateInput(const float& delta_time);
    void updateButtons();
    void updateGUI(const float& delta_time);
    void update(const float& delta_time);
    void render(sf::RenderWindow& target);
};
#endif