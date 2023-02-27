#ifndef CPP_STATE_CORESTATE_HPP
#define CPP_STATE_CORESTATE_HPP

#include "../header.h"
#include "gfx.hpp"
class State;

class StateData
{
    public:
    StateData(){}

    float grid_size;
    sf::RenderWindow* sWindow;
	sf::Font font;
	sf::Font debugFont;
	GraphicsSettings* gfxSettings;
    std::stack<State*>* sStates;
	std::map<std::string, int>* supportedKeys;
};
class State
{
    private:
    protected:
	StateData* IstateData;
	std::stack<State*>* Istates;
	sf::RenderWindow* Iwindow;
	std::map<std::string, int>* IsupportedKeys;
	std::map<std::string, int> Ikeybinds;

	bool Iquit;
	bool Ipaused;
	float Ikeytime;
	float IkeytimeMax;
	float IgridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	std::stringstream dString_Stream;
	sf::Text dText;
	bool debugMode;
	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;




    public:
    State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions	
	void endState(); 
	void pauseState();
	void unpauseState();
	
	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& deltatime);
	virtual void updateInput(const float& deltatime) = 0;
	virtual void update(const float& deltatime) = 0;
	virtual void render(sf::RenderWindow* target = NULL) = 0;
};
#endif 