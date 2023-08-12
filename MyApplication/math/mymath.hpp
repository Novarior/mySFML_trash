#ifndef CPP_MATH_GENERATION_PSEUDO_RANDOM_NUMBER_HPP
#define CPP_MATH_GENERATION_PSEUDO_RANDOM_NUMBER_HPP

#include "../header.h"
namespace mmath {
enum colorMode { RED_GRADIENT,
    GREEN_GRADIENT,
    BLURE_GRADIENT,
    GRAY_GRADIENT };

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

const unsigned int calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2u resolution, const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2f resolution, const unsigned modifier = 60);
};
#endif