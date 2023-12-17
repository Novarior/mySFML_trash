#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#define NODES_MAX_INPUT 10
#define NODES_MAX_OUTPUT 10

#define NODES_MAX_UID 0xff

#include "NodePort.hpp"

// simple node class for the node system

// node look like a square with a circle on sides (left and right)
// the circle is the input or output of the node (left is input and right is output)

// the node have a name and a id
// the id is a number from 0 to

namespace NodeEnum {
enum NodeStateAction {
    IDLE,
    SELECTED,
    ACTIVED
};
};
class NodePort;
// node class
class Node {
private:
    std::string mName; // the name of the node
    unsigned int mId; // the id of the node

    std::vector<NodePort*> mInputPort; // the input of the node
    std::vector<NodePort*> mOutputPort; // the output of the node

    sf::RectangleShape mShape; // the shape of the node used like body of the node
    sf::RectangleShape mShapeHeader; // the shape of the node header used like head of the node (the header is the top of the node)
    sf::Text mText; // the text of the node used like name of the node
    sf::Font& mFont; // the font of the node

    bool mIsDragged; // if the node is dragged
    sf::Vector2f mDragOffset; // the offset of the node when dragged
    unsigned int mNode_state; // Node state (idle, selected, moved)

public:
    /// @brief create a node with a name and a id
    /// @param _name the name of the node
    /// @param _id the id of the node
    Node(std::string _name, unsigned int _id, sf::Font& font, sf::Vector2f _pos = sf::Vector2f(0, 0), sf::Vector2f _size = sf::Vector2f(100, 100));
    virtual ~Node();

    sf::Vector2f getPosition() { return mShape.getPosition(); }

    void onMousePressed(const sf::Vector2f _mousePos);
    void onMouseReleased();
    void onMouseMoved(const sf::Vector2f _mousePos);

    void update(const sf::Vector2f _mousePosWindow, sf::Event* _event);

    // render the node
    void render(sf::RenderTarget& target);
};

#endif // NODES_NODE_HPP