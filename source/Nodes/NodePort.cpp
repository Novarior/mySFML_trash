#include "NodePort.hpp"

NodePort::NodePort(Node* node, sf::FloatRect _rectNode,
    NodeEnum::NodePortDirection direction,
    NodeEnum::NodePortType type,
    unsigned int index)
    : isConnected(false)
    , node(node)
    , index(index)
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
    //  this->mShape.getPosition().x - this->mInput[i].getRadius(),
    //     this->mShape.getPosition().y + (this->mShapeHeader.getGlobalBounds().height * 1.5) + (this->mInput[i].getRadius() * 2 * i) + (mmath::p2pY(5.f, this->mShape.getGlobalBounds().height) * i));

    //     this->mShape.getPosition().x + this->mShape.getGlobalBounds().width - this->mOutput[i].getRadius(),
    //     this->mShape.getPosition().y + (this->mShapeHeader.getGlobalBounds().height * 1.5) + (this->mInput[i].getRadius() * 2 * i) + (mmath::p2pY(5.f, this->mShape.getGlobalBounds().height) * i));
}

void NodePort::update(const sf::Vector2f _mousePosWindow, sf::Event* _event)
{
    if (shape.getGlobalBounds().contains(_mousePosWindow.x, _mousePosWindow.y))
        if (_event->type == sf::Event::MouseButtonPressed && _event->mouseButton.button == sf::Mouse::Left) {
            if (isConnected) {
                disconnect();
                shape.setFillColor(sf::Color(255, 255, 255));
            } else {
                connect();
                shape.setFillColor(sf::Color(0, 255, 0));
            }
        }
}

void NodePort::render(sf::RenderTarget& target)
{
    target.draw(shape);
}