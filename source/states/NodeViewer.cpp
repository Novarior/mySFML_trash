#include "NodeViewer.hpp"

void NodeViewer::initKeybinds()
{
    this->Ikeybinds["KEY_CLOSE"] = this->IsupportedKeys->at("Escape");
}

void NodeViewer::initNodes()
{
    int i = 0;
    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 3; y++) {
            this->mNode.push_back(new Node("Node " + std::to_string(i), i, this->IstateData->debugFont,
                sf::Vector2f(100 + (450 * x), 100 + 220 * y), // pos
                sf::Vector2f(300, 200))); // size
            i++;
        }
}

void NodeViewer::inttView()
{
    this->mView.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
    this->mView.setCenter(sf::Vector2f(this->IstateData->sWindow->getSize()) / 2.f);
}

NodeViewer::NodeViewer(StateData* state_data)
    : State(state_data)
{
    this->initKeybinds();
    this->initNodes();
    this->inttView();

    this->mBackground.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
    this->mBackground.setFillColor(sf::Color::Black);
}

NodeViewer::~NodeViewer()
{
    Logger::log("NodeViewer", "destructor", logType::INFO);
    ParserJson::saveNodesdata(this->mNode);

    for (auto& i : this->mNode)
        delete i;
}

void NodeViewer::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_CLOSE"))) && this->getKeytime())
        this->endState();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->debugMode = !this->debugMode;
}

void NodeViewer::startConnection(NodePort* startPort)
{
}

void NodeViewer::endConnection(NodePort* endPort)
{
}

void NodeViewer::update(const float& delta_time)
{
    this->updateInput(delta_time);
    this->updateKeytime(delta_time);
    this->updateMousePositions(&this->mView);

    bool isMoved = false;
    bool isPressed = false;

    for (auto& node : this->mNode) {
        node->update(static_cast<sf::Vector2f>(this->mousePosWindow), this->Ievent, this->mNode);
        for (auto& port : node->get_InputPorts()) {
            if (port->isContains(static_cast<sf::Vector2f>(this->mousePosWindow))) {
                if (Ievent->type == sf::Event::MouseButtonPressed && Ievent->mouseButton.button == sf::Mouse::Left) {
                    startConnection(port);
                } else if (Ievent->type == sf::Event::MouseButtonReleased && Ievent->mouseButton.button == sf::Mouse::Left) {
                    endConnection(port);
                }
            }
        }
        for (auto& port : node->get_OutputPorts()) {
            if (port->isContains(static_cast<sf::Vector2f>(this->mousePosWindow))) {
                if (Ievent->type == sf::Event::MouseButtonPressed && Ievent->mouseButton.button == sf::Mouse::Left) {
                    startConnection(port);
                } else if (Ievent->type == sf::Event::MouseButtonReleased && Ievent->mouseButton.button == sf::Mouse::Left) {
                    endConnection(port);
                }
            }
        }
    }

    this->dString_Stream.str("");
    this->dString_Stream << "Mouse Pos: " << this->mousePosView.x << " " << this->mousePosView.y << "\n"
                         << "Mouse Pos Grid: " << this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
                         << "Mouse Pos Window: " << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n"
                         << "Mouse Pos Screen: " << this->mousePosScreen.x << " " << this->mousePosScreen.y << "\n"
                         << "node[0].pos" << this->mNode[0]->getPosition().x << " " << this->mNode[0]->getPosition().y << "\n"
                         << "Is Moved: " << isMoved << "\n"
                         << "Is Pressed: " << isPressed << "\n"
                         << "Keytime: " << this->Ikeytime << "\n"
                         << "FPS: " << 1.f / delta_time << "\n"
                         << "Nodes: " << this->mNode.size() << "\n";
}

void NodeViewer::render(sf::RenderWindow& window)
{
    window.draw(this->mBackground);

    for (auto& i : this->mNode)
        i->render(window);

    if (this->debugMode) {
        this->dText.setString(this->dString_Stream.str());
        window.draw(this->dText);
    }
}