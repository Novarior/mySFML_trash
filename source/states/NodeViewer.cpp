#include "NodeViewer.hpp"

void NodeViewer::initKeybinds()
{
    this->Ikeybinds["KEY_CLOSE"] = this->IsupportedKeys->at("Escape");
    this->Ikeybinds["KEY_SLASH"] = this->IsupportedKeys->at("Slash");
    this->Ikeybinds["TAB_KEY"] = this->IsupportedKeys->at("Tab");
}

void NodeViewer::initNodes()
{
    int i = 0;
    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 3; y++) {
            this->mNode.push_back(std::make_unique<Node>("Node " + std::to_string(i), i, this->IstateData->debugFont,
                sf::Vector2f(100 + (450 * x), 100 + 220 * y), // pos
                sf::Vector2f(300, 200))); // size
            i++;
        }
}

void NodeViewer::initButtons()
{
}

void NodeViewer::initGUI()
{
    this->mSideBar.setSize(sf::Vector2f(300, this->IstateData->sWindow->getSize().y));
    this->mSideBar.setPosition(sf::Vector2f(this->IstateData->sWindow->getSize().x - this->mSideBar.getSize().x, 0));
    this->mSideBar.setFillColor(sf::Color(30, 34, 41));
    this->mSideBar.setOutlineThickness(2.f);
    this->mSideBar.setOutlineColor(sf::Color(30, 18, 16));
}

void NodeViewer::initView()
{

    this->mView.reset(sf::FloatRect(0.f, 0.f, this->IstateData->sWindow->getSize().x, this->IstateData->sWindow->getSize().y));
}

NodeViewer::NodeViewer(StateData* state_data)
    : State(state_data)
    , mShowSideBar(false)
    , mCurrentPort(nullptr)
    , _currentMousePositon(0.f, 0.f)
    , _deltaMousePosition(0.f, 0.f)
    , _previousMousePosition(0.f, 0.f)
{
    this->initKeybinds();
    this->initView();
    this->initNodes();

    this->mBackground.setSize(sf::Vector2f(this->IstateData->sWindow->getSize()));
    this->mBackground.setFillColor(sf::Color(0, 20, 40));
}

NodeViewer::~NodeViewer()
{
    // ParserJson::saveNodesdata(this->mNode);

    for (auto& i : this->mButtons)
        delete i.second;

    mNode.clear();
    mButtons.clear();

    Logger::log("NodeViewer", "destructor", logType::INFO);
}

void NodeViewer::updateInput(const float& delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_CLOSE"))) && this->getKeytime())
        this->endState();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("KEY_SLASH"))) && this->getKeytime())
        this->debugMode = !this->debugMode;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode(this->Ikeybinds.at("TAB_KEY"))) && this->getKeytime())
        mShowSideBar = !mShowSideBar;

    bool isMouseOnNode = true;
    _currentMousePositon = this->mousePosWindow;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (auto& node : mNode) {
            if (node.get()->getStateNode() == NodeEnum::NodeStateAction::SELECTED
                || node.get()->getStateNode() == NodeEnum::NodeStateAction::ACTIVED) {
                isMouseOnNode = true;
                break;
            } else {
                isMouseOnNode = false;
            }
        }
        if (isMouseOnNode == false) {
            _deltaMousePosition = _currentMousePositon - _previousMousePosition;
            mView.move(-_deltaMousePosition.x, -_deltaMousePosition.y);
        }
    }
    _previousMousePosition = _currentMousePositon;
}
void NodeViewer::update(const float& delta_time)
{
    this->updateKeytime(delta_time);
    this->updateMousePositions(&mView);
    this->updateInput(delta_time);

    bool isMoved = false;
    bool isPressed = false;

    for (auto& node : this->mNode)
        node->update(static_cast<sf::Vector2f>(this->mousePosView), *this->Ievent, this->mNode);

    this->dString_Stream.str("");
    this->dString_Stream << "Mouse Pos: " << this->mousePosView.x << " " << this->mousePosView.y << "\n"
                         << "Mouse Pos Grid: " << this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
                         << "Mouse Pos Window: " << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n"
                         << "Mouse Pos Screen: " << this->mousePosScreen.x << " " << this->mousePosScreen.y << "\n"
                         << "node[0]\n\tpos: " << this->mNode[0]->getPosition().x << " " << this->mNode[0]->getPosition().y << "\n"
                         << "\tstate: " << mNode[0]->getStateNode() << "\n"
                         << "\tis_Contains: " << mNode[0]->is_Contains(this->mousePosView) << "\n"
                         << "Is Moved: " << isMoved << "\n"
                         << "Is Pressed: " << isPressed << "\n"
                         << "Keytime: " << this->Ikeytime << "\n"
                         << "FPS: " << 1.f / delta_time << "\n"
                         << "Nodes: " << this->mNode.size() << "\n";
}

void NodeViewer::render(sf::RenderWindow& window)
{

    window.setView(mView);
    window.draw(this->mBackground);

    // draw elements with shifted view

    for (auto& i : this->mNode)
        i->render(window);

    // draw elements with default view
    window.setView(window.getDefaultView());

    if (this->mShowSideBar)
        window.draw(this->mSideBar);

    if (this->debugMode) {
        this->dText.setString(this->dString_Stream.str());
        window.draw(this->dText);
    }
}