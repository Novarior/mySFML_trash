#ifndef CPP_CUSTOMHEADER_H
#define CPP_CUSTOMHEADER_H

// including stl lib
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <pwd.h>
#include <random>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>

// system include
#include <CoreFoundation/CoreFoundation.h>

// include nlohmann/json libary
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann;

// include my libary
#include "LOGGER.hpp"
#include "systemFunctionUNIX.hpp"

// include SFML libary
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
// include in program files
#include "math/mymath.hpp"

#include "cmakever.h"
#include "myConst.h"

#endif