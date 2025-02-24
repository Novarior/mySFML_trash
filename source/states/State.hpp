#ifndef CPP_STATE_CORESTATE_HPP
#define CPP_STATE_CORESTATE_HPP

#include "../GUI/GUISYS.hpp"

#include "../math/mymath.hpp"
#include "../source/mypars/parsJSON.hpp"
#include "gfx.hpp"
// Forward declaration of State class
class State;

// Class for state data
// This class holds data that is shared across different states
class StateData {
public:
  // Constructor initializes all pointers to nullptr
  StateData() {
    this->sd_Window = nullptr;
    this->sd_supportedKeys = nullptr;
    this->sd_States = nullptr;
    this->sd_gfxSettings = nullptr;

    this->reserGUI = false;
    this->sd_volumeManager = nullptr;
  }

  float sd_gridSize;                           // Size of the grid
  std::shared_ptr<sf::RenderWindow> sd_Window; // Pointer to the SFML window
  sf::Font sd_font;                            // Font used in the game
  sf::Font sd_debugFont;                       // Font used for debugging
  GraphicsSettings *sd_gfxSettings; // Pointer to the graphics settings
  std::shared_ptr<VolumeManager>
      sd_volumeManager; // Vector for link to volume manager

  std::stack<State *> *sd_States;               // Stack of states
  std::map<std::string, int> *sd_supportedKeys; // Map of supported keys
  unsigned int sd_characterSize_debug;          // Character size for debug text
  unsigned int sd_characterSize_game_big; // Character size for big game text
  unsigned int
      sd_characterSize_game_medium; // Character size for medium game text
  unsigned int
      sd_characterSize_game_small; // Character size for small game text
  bool reserGUI;                   // Flag to reset GUI
};

// Abstract class for game states
class State {
private:
protected:
  // Variables
  StateData *IstateData;                         // Pointer to shared state data
  std::stack<State *> *Istates;                  // Stack of states
  std::shared_ptr<sf::RenderWindow> Iwindow;     // Pointer to the SFML window
  sf::Event *Ievent;                             // Pointer to the SFML event
  std::map<std::string, int> *IsupportedKeys;    // Map of supported keys
  std::map<std::string, int> Ikeybinds;          // Map of key bindings
  std::shared_ptr<VolumeManager> IvolumeManager; // Volume manager

  // Resources
  bool Iquit;        // Flag to quit the state
  bool Ipaused;      // Flag to pause the state
  float Ikeytime;    // Time since last key press
  float IkeytimeMax; // Maximum time between key presses
  float IgridSize;   // Size of the grid

  sf::Vector2i ImousePosScreen;
  sf::Vector2i ImousePosWindow;
  sf::Vector2f ImousePosView;
  sf::Vector2i ImousePosGrid;

  std::stringstream IstringStream;              // Stream for debug string
  sf::Text Itext;                               // Debug text
  bool Idebud;                                  // Flag for debug mode into game
  std::map<std::string, sf::Texture> Itextures; // Map of textures

  // Sounds and him elements for game (volume, sound, buffer, ect )

  // shared map with sounds and name itself
  std::map<std::string, sf::Sound> IsoundsMap;

  // Map of sound buffers, one key one sound
  std::unordered_map<SoundCategory, std::map<std::string, sf::SoundBuffer>>
      IsoundBufferMap;

  void initBuffer(); // Initialize buffer

  // Functions for self state
  virtual void
  initKeybinds() = 0; // Initialize key bindings (pure virtual function)
  void reCaclulateCharacterSize(); // Recalculate character size

  // Functions for sounds key
  // for calling sf::Sound from map using category layer
  virtual bool loadSoundtoBuffer(SoundCategory _soundcategory,
                                 std::string _namepath, std::string _typename);

  void playSound(SoundCategory _soundcategory,
                 std::string _typename); // Play sound from category[_typename]

  // functions accses
  inline void setVolume(SoundCategory _category,
                        const float _newVal) // Set volume for all categories
  {
    this->IvolumeManager->setCategoryVolume(_category, _newVal);
    for (auto &it : IsoundsMap)
      it.second.setVolume(IvolumeManager->getCategoryVolume(_category));
  }

public:
  // Constructor
  State(StateData *state_data);
  // Destructor
  virtual ~State();

  // Accessors
  const bool &getQuit() const { return this->Iquit; } // Get quit flag
  const bool getKeytime();                            // Get key time

  // Functions
  void endState() { this->Iquit = true; }        // End the state
  void pauseState() { this->Ipaused = true; }    // Pause the state
  void unpauseState() { this->Ipaused = false; } // Unpause the state

  // update sounds (virtual function)
  virtual void updateSounds(const float &delta_time) = 0;
  // Update mouse positions (virtual function)
  virtual void updateMousePositions(sf::View *view = NULL);
  // Update key time (virtual function)
  virtual void updateKeytime(const float &delta_time);
  // Update input (pure virtual function)
  virtual void updateInput(const float &delta_time) = 0;
  // Update the state (pure virtual function)
  virtual void update(const float &delta_time) = 0;
  // Render the state (pure virtual function)
  virtual void render(sf::RenderWindow &target) = 0;
};
#endif