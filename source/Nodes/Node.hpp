#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#define NODES_MAX_INPUT 10 // Maximum number of input ports a node can have
#define NODES_MAX_OUTPUT 10 // Maximum number of output ports a node can have

#define NODES_MAX_UID 0xff // Maximum unique identifier for a node
#include "../header.h"

// This is a simple node class for the node system
// A node is represented as a square with a circle on each side (left and right)
// The circle represents the input or output of the node (left circle is input and right circle is output)
// Each node has a name and an ID
// The ID is a number from 0 to NODES_MAX_UID

// The NodeEnum namespace contains enums for different node states, port types, port states, and port directions
namespace NodeEnum {
enum NodeStateAction {
    IDLE, // The node is idle
    SELECTED, // The node is selected
    ACTIVED // The node is active
};
enum NodePortType {
    INPUT, // The port is an input port
    OUTPUT // The port is an output port
};
enum NodePortState {
    CONNECTED, // The port is connected
    DISCONNECTED // The port is disconnected
};
enum NodePortDirection {
    LEFT, // The port is on the left side of the node
    RIGHT // The port is on the right side of the node
};
};

class Node;

/// @brief Class representing a port on a node, which can be connected to other ports
class NodePort {
private:
    bool _isConnected; // Whether the port is connected or not
    bool _mIsDragging; // Whether the port is being dragged or not
    Node* _selfNode; // The node to which the port belongs
    Node* _linkNode; // The node to which this port is connected

    NodePort* _connectedPort; // The port to which this port is connected

    sf::CircleShape _shape; // The shape of the port

    unsigned int _index; // The index of the port

    sf::Vector2f _offset; // The offset of the port
    sf::Vertex _line[2]; // The line between this port and the connected port
    std::vector<std::pair<sf::VertexArray, bool>> _mLines; // The lines between this port and the connected port

    NodeEnum::NodePortType _mPortType; // The type of the port (input or output)

public:
    /// @brief  Constructor for creating a port
    /// @param selfNode The node to which the port belongs
    /// @param rectNode  The rectangle representing the node
    /// @param direction  The direction of the port, left or right
    /// @param type  The type of the port, input or output
    /// @param index The index of the port
    NodePort(Node* selfNode, sf::FloatRect rectNode,
        NodeEnum::NodePortDirection direction = NodeEnum::NodePortDirection::RIGHT,
        NodeEnum::NodePortType type = NodeEnum::NodePortType::OUTPUT,
        unsigned int index = 0);
    virtual ~NodePort();

    bool isConnect() { return _isConnected; } // Returns whether the port is connected or not
    bool isInput() { return _mPortType == NodeEnum::NodePortType::INPUT; } // Returns whether the port is an input port or not
    void connect(Node* _linkNode = nullptr, NodePort* _connectedPort = nullptr); // Connects the port to another port
    void disconnect(); // Disconnects the port

    const bool isContains(sf::Vector2f _mousePosWindow) const { return _shape.getGlobalBounds().contains(_mousePosWindow); } // Returns whether the port contains the given mouse position or not
    const sf::FloatRect getGlobalBounds() const { return _shape.getGlobalBounds(); } // Returns the global bounds of the port

    /// @brief Returns the node to which the port belongs
    /// @return  Node*
    Node* getSelfNode() const { return _selfNode; }
    /// @brief Returns the node to which the port is connected
    /// @return Node*
    Node* getLinkNode() const { return _linkNode; }
    /// @brief Returns the index of the port
    /// @return const unsigned int
    unsigned int getIndex() const { return _index; }
    /// @brief Returns the type of the port
    /// @return const NodeEnum::NodePortType
    NodeEnum::NodePortType getPortType() const { return _mPortType; }

    void setOffset(sf::Vector2f offset) { _offset = _shape.getPosition() - offset; } // Sets the offset of the port
    void move(sf::Vector2f offset) { _shape.setPosition(offset + _offset); } // Moves the port
    const sf::Vector2f getPosPort() { return _shape.getPosition(); } // Returns the position of the port
    const sf::Vector2f getPosPortCenter() { return _shape.getPosition() + sf::Vector2f(_shape.getRadius(), _shape.getRadius()); } // Returns the center position of the port

    void update(const sf::Vector2f _mousePosWindow, sf::Event& _event, std::vector<std::unique_ptr<Node>>& _nodes); // Updates the port
    void updateLines(); // Updates the lines between this port and the connected port

    void render(sf::RenderTarget& target) // Renders the port and the lines
    {
        target.draw(_shape);

        if (_mIsDragging)
            target.draw(_line, 2, sf::Lines);

        for (auto& line : _mLines)
            target.draw(line.first);
    }
};

// Node class
class Node {
private:
    std::string _mName; // The name of the node
    unsigned int _mId; // The ID of the node

    std::vector<std::unique_ptr<NodePort>> _mInputPort; // The input ports of the node

    sf::RectangleShape _mShape; // The shape of the node, used as the body of the node
    sf::RectangleShape _mShapeHeader; // The shape of the node header, used as the head of the node (the header is the top part of the node)
    sf::Text _mText; // The text of the node, used as the name of the node
    sf::Font& _mFont; // The font of the node

    bool _mIsDragged; // Flag indicating whether the node is being dragged
    sf::Vector2f _mDragOffset; // The offset of the node when it is being dragged
    NodeEnum::NodeStateAction _mNode_state; // The state of the node (idle, selected, moved)
protected:
    static Node* _currentDraggingNode; // The current node that is being dragged

public:
    // Constructor to create a node with a name, an ID, a font, and optional position and size
    Node(std::string name, unsigned int id, sf::Font& font, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(100, 100));
    virtual ~Node();

    // Method to get the position of the node
    const sf::Vector2f getPosition() { return _mShape.getPosition(); }
    // Method to get the input ports of the node
    const std::vector<std::unique_ptr<NodePort>>& get_InputPorts() { return _mInputPort; }
    // Method to get the global bounds of the node
    const sf::FloatRect get_GlobalBounds() const;
    // Method to check if the node contains the given mouse position
    bool is_Contains(sf::Vector2f _mousePosWindow);

    // Method to get the state of the node
    inline const NodeEnum::NodeStateAction getStateNode() const { return _mNode_state; }

    // Method to get the ID of the node
    const unsigned int getId() const { return _mId; }
    // Method to get the name of the node
    const std::string getName() const { return _mName; }

    // Method to handle mouse press events
    void onMousePressed(const sf::Vector2f mousePos);
    // Method to handle mouse release events
    void onMouseReleased();
    // Method to handle mouse move events
    void onMouseMoved(const sf::Vector2f mousePos);

    // Method to update the node
    void update(const sf::Vector2f mousePosWindow, sf::Event& event, std::vector<std::unique_ptr<Node>>& nodes);

    // Method to render the node
    void render(sf::RenderTarget& target);
};

#endif // NODES_NODE_HPP