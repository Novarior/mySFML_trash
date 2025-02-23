#ifndef CPP_CUSTOMHEADER_H
#define CPP_CUSTOMHEADER_H

// including stl lib
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <execution>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <unordered_map>
#include <utility>
#include <vector>


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
#include "../math/mymath.hpp"

#include "MemoryUsageMonitor.hpp"
#include "_cmakever.h"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "staticFPSMetter.hpp"

#endif