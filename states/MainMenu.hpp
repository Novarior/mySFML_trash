#ifndef CPP_MAINMENU_CORESTATE_HPP
#define CPP_MAINMENU_CORESTATE_HPP

#include "State.hpp"
#include "Process.hpp"
#include "NoiceView.hpp"
#include "../GUI/GUISYS.hpp"
#include "../Content/rotationCircle.hpp"
#include "../Content/Map/genTree.hpp"

class MainMenu : public State
{
private:

sf::RectangleShape background;
sf::View view;
sf::RenderTexture renderTexture;
sf::Sprite renderSprite;

std::map<std::string,gui::Button*> buttons;
RotarionCircle* rotationCyrcleShape;
GenTree* m_tree;


void initRenderDefines();
void initKeybinds();
void initView();
void initBackground();
void initButtons();
void initBlocks();

//elements for start 
sf::RectangleShape fadeShape;
bool isstatred;
bool isStarted();
void initStartProcces();
void updateStartProcces();
void resetView();


public:
    MainMenu(StateData* sDate);
    virtual ~MainMenu();


	void updateInput(const float& deltatime);
    void updateButtons();
    void update(const float& deltatime);
    void render(sf::RenderWindow* target);

};
#endif