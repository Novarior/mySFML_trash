#include "State.hpp"
#include "VolumeManager.hpp"

/**
 * @brief Construct a new State:: State object
 *
 * @param state_data
 */
State::State(StateData* state_data)
{
    // write log message what im here doing something
    Logger::log("Start initilization state", "State::State()");

    // init variabless from state_data to curent state
    IstateData = state_data;
    Iwindow = state_data->sd_Window;
    Istates = state_data->sd_States;
    Iquit = false;
    Ipaused = false;
    Ikeytime = 0.f;
    IkeytimeMax = 0.3f;
    IgridSize = state_data->sd_gridSize;
    IsupportedKeys = state_data->sd_supportedKeys;
    Ievent = state_data->sd_Event;

    // get access to volume manager from global state data like a shared pointer and init it
    IvolumeManager = std::make_shared<VolumeManager>();

    IstringStream.str("");
    Idebud = __MDEBUG__;

    Itext.setFillColor(sf::Color::White);
    Itext.setCharacterSize(IstateData->sd_characterSize_debug);
    Itext.setOutlineThickness(1);
    Itext.setOutlineColor(sf::Color::Black);
    Itext.setFont(IstateData->sd_debugFont);

    Logger::log("End initilization state", "State::State()");
}

State::~State()
{
    Logger::log("destroy state", "State::~State()");
}

// Accessors
const bool State::getKeytime()
{
    if (Ikeytime >= IkeytimeMax) {
        Ikeytime = 0.f;
        return true;
    }
    return false;
}

// create shared maps with sounds and categoty, buffers and categoty
void State::initBuffer()
{
    this->IsoundsMap = std::make_shared<std::map<std::string, sf::Sound>>();
    this->IsoundBufferMap = std::make_shared<std::map<std::string, sf::SoundBuffer>>();
}

// load sound to buffer
bool State::loadSoundtoBuffer(std::string _namepath, std::string _typename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(_namepath)) {
        Logger::log("Failed to load sound buffer", "State::loadSoundtoBuffer()");
        return false;
    }

    this->IsoundBufferMap->insert(std::make_pair(_typename, buffer));
    return true;
}

void State::updateKeytime(const float& delta_time)
{
    if (Ikeytime < IkeytimeMax)
        Ikeytime += delta_time;
}

void State::reCaclulateCharacterSize()
{
    IstateData->sd_characterSize_debug = mmath::calcCharSize(Iwindow->getSize(), 150);
    IstateData->sd_characterSize_game_big = mmath::calcCharSize(Iwindow->getSize(), 75);
    IstateData->sd_characterSize_game_medium = mmath::calcCharSize(Iwindow->getSize(), 85);
    IstateData->sd_characterSize_game_small = mmath::calcCharSize(Iwindow->getSize(), 95);
}

void State::updateMousePositions(sf::View* view)
{
    ImousePosScreen = sf::Mouse::getPosition();
    ImousePosWindow = sf::Mouse::getPosition(*Iwindow);

    if (view)
        Iwindow->setView(*view);

    ImousePosView = Iwindow->mapPixelToCoords(sf::Mouse::getPosition(*Iwindow));
    ImousePosGrid = sf::Vector2i(
        static_cast<int>(ImousePosView.x) / static_cast<int>(IgridSize),
        static_cast<int>(ImousePosView.y) / static_cast<int>(IgridSize));

    Iwindow->setView(Iwindow->getDefaultView());
}
