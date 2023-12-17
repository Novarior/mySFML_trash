#ifndef NODES_NODEPORT_HPP
#define NODES_NODEPORT_HPP

#include "../header.h"
class Node;
#include "Node.hpp"

namespace NodeEnum {
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

class NodePort {
private:
    bool isConnected; // port is connected or not
    Node* node; // node to which the port belongs

    sf::CircleShape shape; // port shape

    unsigned int index; // index of port

    sf::Vector2f offset; // offset of port

public:
    NodePort(Node* node, sf::FloatRect _rectNode,
        NodeEnum::NodePortDirection direction = NodeEnum::NodePortDirection::RIGHT,
        NodeEnum::NodePortType type = NodeEnum::NodePortType::OUTPUT,
        unsigned int index = 0);
    bool isConnect() const { return isConnected; }
    void connect() { isConnected = true; }
    void disconnect() { isConnected = false; }
    Node* getNode() const { return node; }

    void setOffset(sf::Vector2f _offset)
    {
        offset = this->shape.getPosition() - _offset;
    }

    void move(sf::Vector2f _offset) { shape.setPosition(_offset + offset); }

    void update(const sf::Vector2f _mousePosWindow, sf::Event* _event);

    void render(sf::RenderTarget& target);
};

#endif // NODES_NODEPORT_HPP