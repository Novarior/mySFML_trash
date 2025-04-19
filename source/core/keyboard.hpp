#ifndef KEYBOARD
#define KEYBOARD

#include <IOKit/hid/IOHIDLib.h>
#include <map>

class keyboardOSX {
public:
  std::map<uint32_t, bool> keyStates;
  IOHIDManagerRef hidManager;

  keyboardOSX();
  ~keyboardOSX();

  bool isKeyPressed(uint32_t key);
  void update();
};

#endif /* KEYBOARD */