#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP

#include "../header.h"
namespace mmath {

struct noiceData {
    unsigned int mapSizeX = 0;
    unsigned int mapSizeY = 0;
    float gridSize = 0;
    long seed = 0;
    unsigned octaves = 0;
    double frequency = 0;
    float amplifire = 0;
    float persistence = 0;
    unsigned int RenderWindowX = 0;
    unsigned int RenderWindowY = 0;
    unsigned int smoothMode = 0;
};

const double randZeroToOne();

const double randDoubleFromToNum(double Min_val, double Max_val);
const int randIntFromToNum(int Min_val, int Max_val);

/// @brief return float from present of resolution, number, ect
/// @param perc precent from 0 to 100
/// @param vm
/// @return float
const float p2pX(const float perc, const sf::VideoMode& vm);
const float p2pY(const float perc, const sf::VideoMode& vm);
const float p2pX(const float perc, const float& i);
const float p2pX(const float perc, const unsigned int& i);

const float normalize(const float value, const float min, const float max);

// fade function
static const double Fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}
// linear interpolation
static const double Lerp(double t, double a, double b) { return a + t * (b - a); }
// gradient
const double Gradient(int hash, double x, double y);

/// @brief rescale value from input to output
/// @param r_value rescalable value
/// @param minInput min value from input
/// @param maxInput max value from input
/// @param minOutput min value from output
/// @param maxOutput max value from output
/// @return rescaled value
const double Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput);
const unsigned int calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2u resolution, const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2f resolution, const unsigned modifier = 60);
};

#endif // CPP_MATH_CORE_HPP