#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#define NODES_MAX_INPUT 10
#define NODES_MAX_OUTPUT 10

#define NODES_MAX_UID 0xff
#include "../header.h"

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
enum NodePortType {
    INPUT,
    OUTPUT
};
enum NodePortState {
    CONNECTED,
    DISCONNECTED
};
enum NodePortDirection {
    LEFT,
    RIGHT
};
};

class Node;
/// @brief class with a line between two port

class NodePort {
private:
    bool isConnected; // port is connected or not
    bool mIsDragging; // port is dragging or not
    Node* seflNode; // node to which the port belongs
    Node* linkNode; // link to node

    NodePort* connectedPort; // connected port

    sf::CircleShape shape; // port shape

    unsigned int index; // index of port

    sf::Vector2f offset; // offset of port
    sf::Vertex line[2]; // line between two port
    std::vector<std::pair<sf::Vertex*, bool>> mLines; // lines between two port

    NodeEnum::NodePortType mPortType; // port type (input or output)

public:
    NodePort(Node* _seflNode, sf::FloatRect _rectNode,
        NodeEnum::NodePortDirection direction = NodeEnum::NodePortDirection::RIGHT,
        NodeEnum::NodePortType type = NodeEnum::NodePortType::OUTPUT,
        unsigned int index = 0)
        : isConnected(false)
        , seflNode(_seflNode)
        , index(index)
        , mPortType(type)
    {
        shape.setRadius(5.f);
        shape.setFillColor(sf::Color(255, 255, 255));
        shape.setOutlineColor(sf::Color(0, 0, 0));
        shape.setOutlineThickness(1.f);

        if (direction == NodeEnum::NodePortDirection::LEFT) {
            shape.setPosition(
                _rectNode.left - shape.getRadius(),
                _rectNode.top + (_rectNode.height * 0.2) + (shape.getRadius() * 2 * index) + (mmath::p2pY(10.f, _rectNode.height) * index));
        } else if (direction == NodeEnum::NodePortDirection::RIGHT) {
            shape.setPosition(
                _rectNode.left + _rectNode.width - shape.getRadius(),
                _rectNode.top + (_rectNode.height * 0.2) + (shape.getRadius() * 2 * index) + (mmath::p2pY(10.f, _rectNode.height) * index));
        }
    }

    virtual ~NodePort() { }

    bool isConnect() const { return isConnected; }
    void connect(Node* _linkNode = nullptr, NodePort* _connectedPort = nullptr);
    void disconnect();

    const bool isContains(sf::Vector2f _mousePosWindow) const { return shape.getGlobalBounds().contains(_mousePosWindow); }
    const sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }

    void startConnection() { }

    Node* getSelfNode() const
    {
        if (seflNode == nullptr)
            return nullptr;
        return this->seflNode;
    }
    Node* getLinkNode() const
    {
        if (linkNode == nullptr)
            return nullptr;
        return this->linkNode;
    }

    unsigned int getIndex() const { return this->index; }
    NodeEnum::NodePortType getPortType() const { return this->mPortType; }

    void setOffset(sf::Vector2f _offset) { offset = this->shape.getPosition() - _offset; }
    void move(sf::Vector2f _offset) { shape.setPosition(_offset + offset); }
    const sf::Vector2f getPosPort() { return shape.getPosition(); }
    const sf::Vector2f getPosPortCenter() { return shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius()); }

    bool isInput() const { return mPortType == NodeEnum::NodePortType::INPUT; }

    void update(const sf::Vector2f _mousePosWindow, sf::Event* _event, std::vector<Node*> _nodes);
    void updateLines();

    void render(sf::RenderTarget& target)
    {
        target.draw(shape);

        if (mIsDragging)
            target.draw(line, 2, sf::Lines);

        for (auto& line : mLines)
            target.draw(line.first, 2, sf::Lines);
    }
};

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

    /// return position of the node
    sf::Vector2f getPosition() { return mShape.getPosition(); }

    /// @return vector of input port of the node
    const std::vector<NodePort*> get_InputPorts() { return this->mInputPort; }
    /// @return vector of input port of the node
    const std::vector<NodePort*> get_OutputPorts() { return this->mOutputPort; }

    /// @return the global bounds of the node
    const sf::FloatRect get_GlobalBounds() const;
    bool is_Contains(sf::Vector2f _mousePosWindow);

    unsigned int getId() const { return this->mId; }
    std::string getName() const { return this->mName; }

    void onMousePressed(const sf::Vector2f _mousePos);
    void onMouseReleased();
    void onMouseMoved(const sf::Vector2f _mousePos);

    void update(const sf::Vector2f _mousePosWindow, sf::Event* _event, std::vector<Node*> _nodes);

    // render the node
    void render(sf::RenderTarget& target);
};

#endif // NODES_NODE_HPP