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
    bool _isConnected; // port is connected or not
    bool _mIsDragging; // port is dragging or not
    Node* _selfNode; // node to which the port belongs
    Node* _linkNode; // link to node

    NodePort* _connectedPort; // connected port

    sf::CircleShape _shape; // port _shape

    unsigned int _index; // index of port

    sf::Vector2f _offset; // offset of port
    sf::Vertex _line[2]; // line between two port
    std::vector<std::pair<sf::VertexArray, bool>> _mLines; // lines between two port

    NodeEnum::NodePortType _mPortType; // port type (input or output)

public:
    /// @brief  create a port
    /// @param selfNode node to which the port belongs
    /// @param rectNode  rect of node
    /// @param direction  direction of port, left or right
    /// @param type  type of port, input or output
    /// @param index /index of port
    NodePort(Node* selfNode, sf::FloatRect rectNode,
        NodeEnum::NodePortDirection direction = NodeEnum::NodePortDirection::RIGHT,
        NodeEnum::NodePortType type = NodeEnum::NodePortType::OUTPUT,
        unsigned int index = 0);
    virtual ~NodePort();

    bool isConnect() { return _isConnected; }
    bool isInput() { return _mPortType == NodeEnum::NodePortType::INPUT; }
    void connect(Node* _linkNode = nullptr, NodePort* _connectedPort = nullptr);
    void disconnect();

    const bool isContains(sf::Vector2f _mousePosWindow) const { return _shape.getGlobalBounds().contains(_mousePosWindow); }
    const sf::FloatRect getGlobalBounds() const { return _shape.getGlobalBounds(); }

    /// @brief get the node to which the port belongs
    /// @return  Node*
    Node* getSelfNode() const { return _selfNode; }
    /// @brief get the node to which it is connected
    /// @return Node*
    Node* getLinkNode() const { return _linkNode; }
    /// @brief get index the node
    /// @return const unsigened int
    unsigned int getIndex() const { return _index; }
    /// @brief get type of the port
    /// @return const NodeEnum::NodePortType
    NodeEnum::NodePortType getPortType() const { return _mPortType; }

    void setOffset(sf::Vector2f offset) { _offset = _shape.getPosition() - offset; }
    void move(sf::Vector2f offset) { _shape.setPosition(offset + _offset); }
    const sf::Vector2f getPosPort() { return _shape.getPosition(); }
    const sf::Vector2f getPosPortCenter() { return _shape.getPosition() + sf::Vector2f(_shape.getRadius(), _shape.getRadius()); }

    void update(const sf::Vector2f _mousePosWindow, sf::Event& _event, std::vector<std::unique_ptr<Node>>& _nodes);
    void updateLines();

    void render(sf::RenderTarget& target)
    {
        target.draw(_shape);

        if (_mIsDragging)
            target.draw(_line, 2, sf::Lines);

        for (auto& line : _mLines)
            target.draw(line.first);
    }
};

// node class
class Node {
private:
    std::string _mName; // the name of the node
    unsigned int _mId; // the id of the node

    std::vector<std::unique_ptr<NodePort>> _mInputPort; // the input of the node

    sf::RectangleShape _mShape; // the _shape of the node used like body of the node
    sf::RectangleShape _mShapeHeader; // the _shape of the node header used like head of the node (the header is the top of the node)
    sf::Text _mText; // the text of the node used like name of the node
    sf::Font& _mFont; // the font of the node

    bool _mIsDragged; // if the node is dragged
    sf::Vector2f _mDragOffset; // the offset of the node when dragged
    NodeEnum::NodeStateAction _mNode_state; // Node state (idle, selected, moved)
protected:
    static Node* _currentDraggingNode; // the current node that is dragged

public:
    /// @brief create a node with a name and a id
    /// @param _name the name of the node
    /// @param  _id the id of the node
    Node(std::string name, unsigned int id, sf::Font& font, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(100, 100));
    virtual ~Node();

    /// return position of the node
    const sf::Vector2f getPosition() { return _mShape.getPosition(); }
    /// @return vector of input port of the node
    const std::vector<std::unique_ptr<NodePort>>& get_InputPorts() { return _mInputPort; }
    /// @return the global bounds of the node
    const sf::FloatRect get_GlobalBounds() const;
    bool is_Contains(sf::Vector2f _mousePosWindow);

    inline const NodeEnum::NodeStateAction getStateNode() const { return _mNode_state; }

    const unsigned int
    getId() const
    {
        return _mId;
    }
    const std::string getName() const { return _mName; }

    void onMousePressed(const sf::Vector2f mousePos);
    void onMouseReleased();
    void onMouseMoved(const sf::Vector2f mousePos);

    void update(const sf::Vector2f mousePosWindow, sf::Event& event, std::vector<std::unique_ptr<Node>>& nodes);

    // render the node
    void render(sf::RenderTarget& target);
};

#endif // NODES_NODE_HPP
