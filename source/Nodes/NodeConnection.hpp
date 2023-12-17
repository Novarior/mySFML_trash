#ifndef NODE_CONNECTION_HPP
#define NODE_CONNECTION_HPP

#include "Node.hpp"
class Connection {
private:
    Node* inNode;
    Node* outNode;

public:
    Connection(Node* _inNode, Node* _outNode)
        : inNode(_inNode)
        , outNode(_outNode)
    {
    }
    Node* getInNode() const { return inNode; }
    Node* getOutNode() const { return outNode; }

    void setInNode(Node* _inNode) { inNode = _inNode; }
    void setOutNode(Node* _outNode) { outNode = _outNode; }
};

#endif // NODE_CONNECTION_HPP