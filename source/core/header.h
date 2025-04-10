#ifndef HEADER
#define HEADER

// including stl lib
#include <chrono>
#include <cmath>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>


// include nlohmann/json libary
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann;

// include SFML libary
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "LOGGER.hpp"
// include in program files
#include "../math/mymath.hpp"

#include "MemoryUsageMonitor.hpp"
#include "_cmakever.h"
#include "dataCollector/_man_Texture.hpp"
#include "staticFPSMetter.hpp"

#endif /* HEADER */
