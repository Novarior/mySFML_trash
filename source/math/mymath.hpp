#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP

#include "../header.h"
namespace mmath {

enum eSmoothMode {
    SMOOTH_MODE = 0,
    FAST_MODE = 1
};

struct noiceData {
    unsigned int mapSizeX = 0;
    unsigned int mapSizeY = 0;
    unsigned int mapSizeZ = 0;
    float gridSize = 0;
    unsigned long seed = 0;
    int offsetSeed = 0xffffffff;
    float chanceToSpawnTree = 0.0f;
    unsigned octaves = 0;
    double frequency = 0;
    float amplifire = 0;
    float persistence = 0;
    unsigned int RenderWindowX = 0;
    unsigned int RenderWindowY = 0;
    unsigned int smoothMode = 0;
    bool fastMode = false;
};

const double randZeroToOne();

const double randDoubleFromToNum(double Min_val, double Max_val);
const int randIntFromToNum(int Min_val, int Max_val);

/// @brief return float from present of resolution, number, ect
/// @param perc precent from 0 to 100
/// @param vm
/// @return float
const float p2pX(const float perc, const sf::VideoMode& vm);
const float p2pX(const float perc, const unsigned int& i);
const float p2pX(const float perc, const float& i);

const float p2pY(const float perc, const sf::VideoMode& vm);
const float p2pY(const float perc, const unsigned int& i);
const float p2pY(const float perc, const float& i);

const float normalize(const float value, const float min, const float max);

// fade function
static const double Fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
// interpolations
namespace interpolation {
    // linear interpolation
    static const double LinInter(double t, double a, double b) { return a + t * (b - a); }
    // cosine interpolation
    static const double CosInter(double t, double a, double b) { return a * (1 - (1 - cos(t * M_PI)) * 0.5) + b * (1 - cos(t * M_PI)) * 0.5; }
    // cubic interpolation
    static const double CubicInter(double t, double a, double b) { return (a - b) * (3.0 - t * 2.0) * t * t + b; }
    // quintic interpolation
    static const double QuinticInter(double t, double a, double b) { return (a - b) * ((t * (t * 6.0 - 15.0) + 10.0) * t * t * t) + b; }
    // quartic interpolation
    static const double QuarticInter(double t, double a, double b) { return (a - b) * (t * t * (t * (t * 6.0 - 15.0) + 10.0)) + b; }
    // quadratic interpolation
    static const double QuadraticInter(double t, double a, double b) { return (a - b) * (t * (t - 2.0) * t + 1.0) + b; }
    // hermite interpolation
    static const double HermiteInter(double t, double a, double b) { return (a - b) * (t * t * (3.0 - t * 2.0)) + b; }
};

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