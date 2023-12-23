#include "Node.hpp"

NodePort::NodePort(Node* selfNode, sf::FloatRect rectNode, NodeEnum::NodePortDirection direction, NodeEnum::NodePortType type, unsigned int index)
    : _isConnected(false)
    , _selfNode(selfNode)
    , _index(index)
    , _mPortType(type)
    , _mIsDragging(false)
    , _connectedPort(nullptr)
    , _linkNode(nullptr)
    , _offset(0, 0)

{
    _shape.setRadius(5.f);
    _shape.setFillColor(sf::Color(255, 255, 255));
    _shape.setOutlineColor(sf::Color(0, 0, 0));
    _shape.setOutlineThickness(1.f);

    if (direction == NodeEnum::NodePortDirection::LEFT) {
        _shape.setPosition(
            rectNode.left - _shape.getRadius(),
            rectNode.top + (rectNode.height * 0.2) + (_shape.getRadius() * 2 * index) + (mmath::p2pY(10.f, rectNode.height) * index));
    } else if (direction == NodeEnum::NodePortDirection::RIGHT) {
        _shape.setPosition(
            rectNode.left + rectNode.width - _shape.getRadius(),
            rectNode.top + (rectNode.height * 0.2) + (_shape.getRadius() * 2 * index) + (mmath::p2pY(10.f, rectNode.height) * index));
    }
}

NodePort::~NodePort()
{
    disconnect();
    for (size_t i = 0; i < _mLines.size(); i++)
        _mLines.erase(_mLines.begin() + i);

    _mLines.clear();
}

void NodePort::connect(Node* node, NodePort* connectedPort)
{
    if (_isConnected)
        return; // Если этот порт уже подключен, пропускаем подключение

    _isConnected = true;
    _linkNode = node;
    _connectedPort = connectedPort;

    if (!_connectedPort->_isConnected) // Если подключаемый порт еще не подключен
        _connectedPort->connect(node, this); // Подключаем его
}
void NodePort::disconnect()
{
    _isConnected = false;
    _linkNode = nullptr;
}

void NodePort::update(const sf::Vector2f mousePosWindow, sf::Event& event, std::vector<std::unique_ptr<Node>>& nodes)
{
    if (_isConnected)
        _shape.setFillColor(sf::Color(0, 255, 0));
    else
        _shape.setFillColor(sf::Color(255, 255, 255));

    if (_shape.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y)) {
        if (!isInput())
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                _mIsDragging = true;
                _line[0].position = _shape.getPosition() + sf::Vector2f(_shape.getRadius(), _shape.getRadius());
                _line[1].position = mousePosWindow;
            }
    }

    if (_mIsDragging) {
        _line[0].position = _shape.getPosition() + sf::Vector2f(_shape.getRadius(), _shape.getRadius());
        _line[1].position = mousePosWindow;

        // Проверяем, находится ли курсор мыши на другой ноде или порту
        Node* otherNode = nullptr;
        NodePort* otherPort = nullptr;
        for (auto& node : nodes) {
            if (node.get() != _selfNode && node->is_Contains(mousePosWindow)) {
                otherNode = node.get();
                for (auto& port : node->get_InputPorts()) {
                    if (port->getGlobalBounds().contains(mousePosWindow)) {
                        otherPort = port.get();

                        if (_mPortType != otherPort->_mPortType && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                            // link ports
                            _mIsDragging = false;
                            _line[1].position = otherPort->getPosPort() + sf::Vector2f(otherPort->_shape.getRadius(), otherPort->_shape.getRadius());

                            sf::VertexArray buffline(sf::Lines, 2);
                            buffline[0].position = _line[0].position;
                            buffline[1].position = _line[1].position;

                            _mLines.push_back(std::make_pair(buffline, true));
                            connect(otherNode, otherPort);
                        }
                        break;
                    }
                }
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            _mIsDragging = false;

        if (otherPort) { // if the mouse cursor is pointing to the port, then the line color is green
            _line[0].color = sf::Color::Green;
            _line[1].color = sf::Color::Green;
        } else if (otherNode) { // else if the mouse cursor is pointing to the other node, then the line color is yellow
            _line[0].color = sf::Color::Yellow;
            _line[1].color = sf::Color::Yellow;
        } else { // else the line color is red
            _line[0].color = sf::Color::Red;
            _line[1].color = sf::Color::Red;
        }
    }

    this->updateLines();
}

Node::Node(std::string name, unsigned int id, sf::Font& font, sf::Vector2f pos, sf::Vector2f size)
    : _mName(name)
    , _mId(id)
    , _mFont(font)
{
    _mShape.setPosition(pos);
    _mShape.setSize(size);
    _mShape.setFillColor(sf::Color(40, 44, 51));
    _mShape.setOutlineThickness(2.f);
    _mShape.setOutlineColor(sf::Color(30, 18, 16));

    _mShapeHeader.setPosition(pos);
    _mShapeHeader.setSize(sf::Vector2f(size.x, mmath::p2pY(15.f, _mShape.getGlobalBounds().height)));
    _mShapeHeader.setFillColor(sf::Color(30, 34, 41));

    _mText.setFont(_mFont);
    _mText.setString(_mName);
    _mText.setCharacterSize(15);
    _mText.setFillColor(sf::Color::White);
    _mText.setPosition(
        _mShape.getPosition().x + (_mShapeHeader.getGlobalBounds().width / 2.f) - _mText.getGlobalBounds().width / 2.f,
        _mShape.getPosition().y + _mText.getGlobalBounds().height / 2.f);

    // push 5 input and 5 output port to the node
    for (int i = 0; i < 5; i++) {
        _mInputPort.push_back(std::make_unique<NodePort>(this, sf::FloatRect(pos, size),
            NodeEnum::NodePortDirection::LEFT, NodeEnum::NodePortType::INPUT, i));
        _mInputPort.push_back(std::make_unique<NodePort>(this, sf::FloatRect(pos, size),
            NodeEnum::NodePortDirection::RIGHT, NodeEnum::NodePortType::OUTPUT, i));
    }
}

void NodePort::updateLines()
{
    for (auto& line : _mLines) {
        if (line.second) { // Если флаг shouldDraw установлен в true
            // Проверяем, что типы портов разные
            if (_mPortType != _connectedPort->_mPortType) {
                line.first[0].position = _shape.getPosition() + sf::Vector2f(_shape.getRadius(), _shape.getRadius()); // Обновляем начальную позицию линии
                // Обновляем конечную позицию линии. Здесь вам нужно будет установить позицию соответствующего порта.
                line.first[1].position = _connectedPort->getPosPortCenter();
            }
        }
    }
}

Node::~Node()
{
    _mInputPort.clear();
}

const sf::FloatRect Node::get_GlobalBounds() const
{
    return _mShape.getGlobalBounds();
}
bool Node::is_Contains(sf::Vector2f mousePosWindow)
{
    return _mShape.getGlobalBounds().contains(mousePosWindow);
}

void Node::onMousePressed(const sf::Vector2f mousePos)
{
    if (_mShapeHeader.getGlobalBounds().contains(mousePos)) {
        if (_currentDraggingNode == nullptr) {
            _mIsDragged = true;
            _currentDraggingNode = this;
            _mDragOffset = _mShapeHeader.getPosition() - mousePos;

            for (auto& i : _mInputPort)
                i->setOffset(mousePos);
        }
    }
}

void Node::onMouseReleased()
{
    if (_mIsDragged && _currentDraggingNode == this) {
        _mIsDragged = false;
        _currentDraggingNode = nullptr;
    }
}

void Node::onMouseMoved(const sf::Vector2f _mousePos)
{
    // Обновите позиции mInput, mOutput и mText также
    if (_mIsDragged && _currentDraggingNode == this) {
        _mShape.setPosition(_mousePos + _mDragOffset);
        _mShapeHeader.setPosition(_mShape.getPosition());

        for (auto& i : _mInputPort)
            i->move(_mousePos);

        _mText.setPosition(
            _mShape.getPosition().x + (_mShapeHeader.getGlobalBounds().width / 2.f) - _mText.getGlobalBounds().width / 2.f,
            _mShape.getPosition().y + _mText.getGlobalBounds().height / 2.f);
    }
}

void Node::update(const sf::Vector2f mousePosWindow, sf::Event& event, std::vector<std::unique_ptr<Node>>& nodes)
{

    // update Node state
    _mNode_state = NodeEnum::NodeStateAction::IDLE;
    _mShapeHeader.setFillColor(sf::Color(30, 34, 41));

    // Hover
    if (_mShapeHeader.getGlobalBounds().contains(mousePosWindow)) {
        _mNode_state = NodeEnum::NodeStateAction::SELECTED;
        _mShapeHeader.setFillColor(sf::Color(50, 64, 71));
        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _mNode_state = NodeEnum::NodeStateAction::ACTIVED;
            _mShapeHeader.setFillColor(sf::Color(70, 84, 81));
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->onMousePressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        this->onMouseReleased();
    else if (event.type == sf::Event::MouseMoved)
        this->onMouseMoved(sf::Vector2f(mousePosWindow));

    // update NodePort
    for (auto& i : _mInputPort)
        i->update(mousePosWindow, event, nodes);
}

// render the node
void Node::render(sf::RenderTarget& target)
{
    target.draw(_mShape);
    target.draw(_mShapeHeader);
    target.draw(_mText);

    if (!_mInputPort.empty())
        for (auto& i : _mInputPort)
            i->render(target);
}