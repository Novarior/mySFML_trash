#include "Node.hpp"

Node::Node(std::string _name, unsigned int _id, sf::Font& font, sf::Vector2f _pos, sf::Vector2f _size)
    : mName(_name)
    , mId(_id)
    , mFont(font)
{
    this->mShape.setPosition(_pos);
    this->mShape.setSize(_size);
    this->mShape.setFillColor(sf::Color(40, 44, 51));
    this->mShape.setOutlineThickness(2.f);
    this->mShape.setOutlineColor(sf::Color(30, 18, 16));

    this->mShapeHeader.setPosition(_pos);
    this->mShapeHeader.setSize(sf::Vector2f(_size.x, mmath::p2pY(15.f, this->mShape.getGlobalBounds().height)));
    this->mShapeHeader.setFillColor(sf::Color(30, 34, 41));

    this->mText.setFont(mFont);
    this->mText.setString(mName);
    this->mText.setCharacterSize(15);
    this->mText.setFillColor(sf::Color::White);
    this->mText.setPosition(
        this->mShape.getPosition().x + (this->mShapeHeader.getGlobalBounds().width / 2.f) - this->mText.getGlobalBounds().width / 2.f,
        this->mShape.getPosition().y + this->mText.getGlobalBounds().height / 2.f);

    // push 5 input and 5 output port to the node
    for (int i = 0; i < 5; i++) {
        this->mInputPort.push_back(new NodePort(this, sf::FloatRect(_pos, _size),
            NodeEnum::NodePortDirection::LEFT, NodeEnum::NodePortType::INPUT, i));
        this->mOutputPort.push_back(new NodePort(this, sf::FloatRect(_pos, _size),
            NodeEnum::NodePortDirection::RIGHT, NodeEnum::NodePortType::OUTPUT, i));
    }
}

Node::~Node() { }

void Node::onMousePressed(const sf::Vector2f _mousePos)
{
    if (mShapeHeader.getGlobalBounds().contains(_mousePos)) {
        mIsDragged = true;
        mDragOffset = mShapeHeader.getPosition() - _mousePos;

        for (auto& i : mInputPort)
            i->setOffset(_mousePos);

        for (auto& i : mOutputPort)
            i->setOffset(_mousePos);
    }
}

void Node::onMouseReleased()
{
    mIsDragged = false;
}

void Node::onMouseMoved(const sf::Vector2f _mousePos)
{
    // Обновите позиции mInput, mOutput и mText также
    if (mIsDragged) {
        mShape.setPosition(_mousePos + mDragOffset);
        mShapeHeader.setPosition(mShape.getPosition());

        for (auto& i : mInputPort)
            i->move(_mousePos);

        for (auto& i : mOutputPort)
            i->move(_mousePos);

        this->mText.setPosition(
            this->mShape.getPosition().x + (this->mShapeHeader.getGlobalBounds().width / 2.f) - this->mText.getGlobalBounds().width / 2.f,
            this->mShape.getPosition().y + this->mText.getGlobalBounds().height / 2.f);
    }
}

void Node::update(const sf::Vector2f _mousePosWindow, sf::Event* _event)
{

    // update Node state
    this->mNode_state = NodeEnum::NodeStateAction::IDLE;
    this->mShapeHeader.setFillColor(sf::Color(30, 34, 41));

    // Hover
    if (this->mShapeHeader.getGlobalBounds().contains(_mousePosWindow)) {
        this->mNode_state = NodeEnum::NodeStateAction::SELECTED;
        this->mShapeHeader.setFillColor(sf::Color(50, 64, 71));
        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->mNode_state = NodeEnum::NodeStateAction::ACTIVED;
            this->mShapeHeader.setFillColor(sf::Color(70, 84, 81));
        }
    }

    if (_event->type == sf::Event::MouseButtonPressed)
        this->onMousePressed(sf::Vector2f(_event->mouseButton.x, _event->mouseButton.y));
    if (_event->type == sf::Event::MouseButtonReleased)
        this->onMouseReleased();
    else if (_event->type == sf::Event::MouseMoved)
        this->onMouseMoved(sf::Vector2f(_event->mouseMove.x, _event->mouseMove.y));

    // update NodePort
    for (auto& i : mInputPort)
        i->update(_mousePosWindow, _event);

    for (auto& i : mOutputPort)
        i->update(_mousePosWindow, _event);
}

// render the node
void Node::render(sf::RenderTarget& target)
{
    target.draw(mShape);
    target.draw(mShapeHeader);
    target.draw(mText);

    if (!this->mInputPort.empty())
        for (auto& i : mInputPort)
            i->render(target);

    if (!this->mOutputPort.empty())
        for (auto& i : mOutputPort)
            i->render(target);
}