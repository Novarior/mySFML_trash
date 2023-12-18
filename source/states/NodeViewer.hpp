#ifndef STATES_NODEVIEWER_HPP
#define STATES_NODEVIEWER_HPP

#include "../Nodes/Node.hpp"


#include "State.hpp"

class NodeViewer : public State {
private:
    // background
    sf::RectangleShape mBackground;
    sf::View mView;
    void initKeybinds();
    void inttView();

    void initNodes();

    std::vector<Node*> mNode;

    NodePort* mCurrentPort;

public:
    NodeViewer(StateData* state_data);
    virtual ~NodeViewer();

    void startConnection(NodePort* startPort);
    void endConnection(NodePort* endPort);

    void updateInput(const float& delta_time);
    void update(const float& delta_time);
    void render(sf::RenderWindow& window);
};
#endif // STATES_NODEVIEWER_HPP