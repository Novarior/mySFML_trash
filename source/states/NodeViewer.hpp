#ifndef STATES_NODEVIEWER_HPP
#define STATES_NODEVIEWER_HPP

#include "../GUI/GUISYS.hpp"
#include "../Nodes/Node.hpp"

#include "State.hpp"

class NodeViewer : public State {
private:
    // background
    sf::RectangleShape mBackground;
    sf::View mView;
    // GUI
    std::map<std::string, gui::Button*> mButtons;
    bool mShowSideBar;
    sf::RectangleShape mSideBar;
    // nodes
    std::vector<std::unique_ptr<Node>> mNode;
    NodePort* mCurrentPort;

    // mouse movenet
    sf::Vector2i _currentMousePositon;
    sf::Vector2i _deltaMousePosition;
    sf::Vector2i _previousMousePosition;

    void initKeybinds();
    void initButtons();
    void initView();
    void initGUI();

    void initNodes();

public:
    NodeViewer(StateData* state_data);
    virtual ~NodeViewer();



    void updateInput(const float& delta_time);
    void update(const float& delta_time);
    void render(sf::RenderWindow& window);
};
#endif // STATES_NODEVIEWER_HPP