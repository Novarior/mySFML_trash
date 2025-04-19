#ifndef CORE
#define CORE

#include "../localisation/helperText.hpp"
#include "../states/MainMenu.hpp"
#include "../states/gfx.hpp"
#include "_cmakever.h"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "dataCollector/_man_Volume.hpp"
#include "keyboard.hpp"
#include "systemFunctionUNIX.hpp"
#include <IOKit/hid/IOHIDManager.h>
#include <cstdint>
#include <memory>
#include <sys/_types/_u_int32_t.h>

class Core {
private:
  float deltaTime;
  sf::Clock deltaClock;

  std::shared_ptr<sf::RenderWindow> mWindow;
  StateData mStatedata;
  std::stack<State *> mState;
  GraphicsSettings gfxSettings;
  std::map<std::string, uint32_t> supportedKeys;
  // IOS keyboard
  std::shared_ptr<keyboardOSX> keyboard;
  // initilization functions
  void initDirectories();
  void initKeyBinds();
  void initVar();
  void initStateData();
  void initState();
  void initWindow();
  void initLocations();
  void initTextures();

public:
  Core();
  virtual ~Core();
  void run();

  void updateEventsWindow();
  void updateDeltaTime();
  void updateSound();
  void update();
  void render();
};

#endif /* CORE */
