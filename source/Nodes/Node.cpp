#include "Node.hpp"

void NodePort::connect(Node* _node, NodePort* _connectedPort)
{
    if (this->isConnected)
        return; // Если этот порт уже подключен, пропускаем подключение

    this->isConnected = true;
    this->linkNode = _node;
    this->connectedPort = _connectedPort;

    if (!this->connectedPort->isConnected) // Если подключаемый порт еще не подключен
        this->connectedPort->connect(_node, this); // Подключаем его
}
void NodePort::disconnect()
{
    this->isConnected = false;
    this->linkNode = nullptr;
}

void NodePort::update(const sf::Vector2f _mousePosWindow, sf::Event* _event, std::vector<Node*> _nodes)
{
    if (isConnected)
        shape.setFillColor(sf::Color(0, 255, 0));
    else
        shape.setFillColor(sf::Color(255, 255, 255));

    if (shape.getGlobalBounds().contains(_mousePosWindow.x, _mousePosWindow.y)) {
        if (!isInput())
            if (_event->type == sf::Event::MouseButtonPressed && _event->mouseButton.button == sf::Mouse::Left) {
                this->mIsDragging = true;
                this->line[0].position = shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
                this->line[1].position = _mousePosWindow;
            }
    }

    if (mIsDragging) {
        this->line[0].position = shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
        this->line[1].position = _mousePosWindow;

        // Проверяем, находится ли курсор мыши на другой ноде или порту
        Node* otherNode = nullptr;
        NodePort* otherPort = nullptr;
        for (Node* node : _nodes) {
            if (node != this->seflNode && node->is_Contains(_mousePosWindow)) {
                otherNode = node;
                for (NodePort* port : node->get_InputPorts()) {
                    if (port->getGlobalBounds().contains(_mousePosWindow)) {
                        otherPort = port;

                        if (_event->type == sf::Event::MouseButtonReleased && _event->mouseButton.button == sf::Mouse::Left) {
                            // link ports
                            this->mIsDragging = false;
                            this->line[1].position = otherPort->getPosPort() + sf::Vector2f(otherPort->shape.getRadius(), otherPort->shape.getRadius());

                            this->mLines.push_back(std::make_pair(this->line, true));
                            this->connect(otherNode, otherPort);
                        }
                        break;
                    }
                }
                break;
            }
        }

        // Меняем цвет линии в зависимости от того, на что указывает курсор мыши
        if (otherPort) {
            this->line[0].color = sf::Color::Green;
            this->line[1].color = sf::Color::Green;
        } else if (otherNode) {
            this->line[0].color = sf::Color::Yellow;
            this->line[1].color = sf::Color::Yellow;
        } else {
            this->line[0].color = sf::Color::Red;
            this->line[1].color = sf::Color::Red;
        }
    }

    this->updateLines();
}

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

void NodePort::updateLines()
{
    for (auto& line : mLines) {
        if (line.second) { // Если флаг shouldDraw установлен в true
            line.first[0].position = shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius()); // Обновляем начальную позицию линии
            // Обновляем конечную позицию линии. Здесь вам нужно будет установить позицию соответствующего порта.
            // Это зависит от того, как вы храните ссылку на соединенный порт.
            line.first[1].position = connectedPort->getPosPortCenter();
        }
    }
}

Node::~Node() { }
const sf::FloatRect Node::get_GlobalBounds() const
{
    return this->mShape.getGlobalBounds();
}
bool Node::is_Contains(sf::Vector2f _mousePosWindow)
{
    return this->mShape.getGlobalBounds().contains(_mousePosWindow);
}

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

void connectToPort(NodePort* _outPort, NodePort* _inPort)
{
}

void Node::update(const sf::Vector2f _mousePosWindow, sf::Event* _event, std::vector<Node*> _nodes)
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

    if (_event->type == sf::Event::MouseButtonPressed && _event->mouseButton.button == sf::Mouse::Left)
        this->onMousePressed(sf::Vector2f(_event->mouseButton.x, _event->mouseButton.y));
    else if (_event->type == sf::Event::MouseButtonReleased && _event->mouseButton.button == sf::Mouse::Left)
        this->onMouseReleased();
    else if (_event->type == sf::Event::MouseMoved)
        this->onMouseMoved(sf::Vector2f(_event->mouseMove.x, _event->mouseMove.y));

    // update NodePort
    for (auto& i : mInputPort)
        i->update(_mousePosWindow, _event, _nodes);

    for (auto& i : mOutputPort)
        i->update(_mousePosWindow, _event, _nodes);
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