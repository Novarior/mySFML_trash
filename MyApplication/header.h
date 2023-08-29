#ifndef CPP_CUSTOMHEADER_H
#define CPP_CUSTOMHEADER_H

// including stl lib
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <stack>
#include <string>
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
// include in program files
#include "math/mymath.hpp"

#include "ConfigurationProgram.h"
#include "myConst.h"

#endif