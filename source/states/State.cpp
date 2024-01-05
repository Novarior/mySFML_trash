#include "State.hpp"
#include "../header.h"

/**
 * @brief Construct a new State:: State object
 *
 * @param state_data
 */
State::State(StateData* state_data)
{
    Logger::log("Start initilization state", "State::State()");

    IstateData = state_data;
    Iwindow = state_data->sWindow;
    Istates = state_data->sStates;
    Iquit = false;
    Ipaused = false;
    Ikeytime = 0.f;
    IkeytimeMax = 0.3f;
    IgridSize = state_data->grid_size;
    IsupportedKeys = state_data->supportedKeys;
    Ievent = state_data->sEvent;

    IvolumeManager = std::make_unique<VolumeManager>();

    dString_Stream.str("");
    debugMode = true;

    dText.setFillColor(sf::Color::White);
    dText.setCharacterSize(IstateData->characterSize_debug);
    dText.setOutlineThickness(1);
    dText.setOutlineColor(sf::Color::Black);
    dText.setFont(IstateData->debugFont);

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

void State::updateKeytime(const float& delta_time)
{
    if (Ikeytime < IkeytimeMax)
        Ikeytime += delta_time;
}

void State::reCaclulateCharacterSize()
{
    IstateData->characterSize_debug = mmath::calcCharSize(Iwindow->getSize(), 150);
    IstateData->characterSize_game_big = mmath::calcCharSize(Iwindow->getSize(), 75);
    IstateData->characterSize_game_medium = mmath::calcCharSize(Iwindow->getSize(), 85);
    IstateData->characterSize_game_small = mmath::calcCharSize(Iwindow->getSize(), 95);
}

void State::updateMousePositions(sf::View* view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*Iwindow);

    if (view)
        Iwindow->setView(*view);

    mousePosView = Iwindow->mapPixelToCoords(sf::Mouse::getPosition(*Iwindow));
    mousePosGrid = sf::Vector2i(
        static_cast<int>(mousePosView.x) / static_cast<int>(IgridSize),
        static_cast<int>(mousePosView.y) / static_cast<int>(IgridSize));

    Iwindow->setView(Iwindow->getDefaultView());
}
