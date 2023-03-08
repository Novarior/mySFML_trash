#include "../header.h"
#include "State.hpp"

/**
 * @brief Construct a new State:: State object
 *
 * @param state_data
 */
State::State(StateData* state_data)
{
	this->IstateData = state_data;
	this->Iwindow = state_data->sWindow;
	this->Istates = state_data->sStates;
	this->Iquit = false;
	this->Ipaused = false;
	this->Ikeytime = 0.f;
	this->IkeytimeMax = 10.f;
	this->IgridSize = state_data->grid_size;
	this->IsupportedKeys = state_data->supportedKeys;

	this->dString_Stream.str("");
	this->debugMode = true;

	this->dText.setFillColor(sf::Color::White);
	this->dText.setCharacterSize(35);
	this->dText.setOutlineThickness(3);
	this->dText.setOutlineColor(sf::Color::Black);
	this->dText.setFont(this->IstateData->debugFont);
}

State::~State() { }

//Accessors
const bool& State::getQuit() const
{
	return this->Iquit;
}

const bool State::getKeytime()
{
	if (this->Ikeytime >= this->IkeytimeMax) {
		this->Ikeytime = 0.f;
		return true;
	}
	return false;
}

void State::endState()
{
	this->Iquit = true;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->Iwindow);

	if (view)
		this->Iwindow->setView(*view);

	this->mousePosView = this->Iwindow->mapPixelToCoords(sf::Mouse::getPosition(*this->Iwindow));
	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->IgridSize),
		static_cast<int>(this->mousePosView.y) / static_cast<int>(this->IgridSize));

	this->Iwindow->setView(this->Iwindow->getDefaultView());
}

void State::updateKeytime(const float& delta_time)
{
	if (this->Ikeytime < this->IkeytimeMax)
		this->Ikeytime += 100.f * delta_time;
}