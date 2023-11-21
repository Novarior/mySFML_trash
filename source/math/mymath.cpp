#include "mymath.hpp"

const double mmath::randDoubleFromToNum(double Min_val, double Max_val)
{
    return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}

const int mmath::randIntFromToNum(int Min_val, int Max_val)
{
    return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}
const double mmath::randZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}
// precent to X and Y
const float mmath::p2pX(const float perc, const sf::VideoMode& vm)
{
    return floor(static_cast<float>(vm.width) * (perc / 100.f));
}
const float mmath::p2pY(const float perc, const sf::VideoMode& vm)
{
    return floor(static_cast<float>(vm.height) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const unsigned int& i)
{
    return floor(static_cast<float>(i) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const float& i)
{
    return floor(static_cast<float>(i) * (perc / 100.f));
}

const float mmath::normalize(const float value, const float min, const float max)
{
    double buff = (value - min) / (max - min);
    float result = static_cast<float>(buff * 255);

    if (result < 0)
        result = 0;
    else if (result > 255)
        result = 255;

    return result;
}

const double mmath::Gradient(int hash, double x, double y)
{
    int h = hash & 15;
    double grad = 1 + (h & 7);
    if (h & 8)
        grad = -grad;
    return (grad * x + grad * y);
}

const double mmath::Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput)
{
    return minOutput + (r_value - minInput) * (maxOutput - minOutput) / (maxInput - minInput);
}

const unsigned int mmath::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    //  Calculates the character size for text using the current resolution and a constant.
    //  @param		sf::VideoMode& vm		The current videomode of the window (resolution).
    //  @param		unsigned modifier		Used to modify the character size in a more custom way.
    //  @return		unsigned int			The calculated character size value.
    return static_cast<unsigned int>((vm.width + vm.height) / modifier);
}

const unsigned int mmath::calcCharSize(const sf::Vector2u resolution, const unsigned modifier)
{
    //  Calculates the character size for text using the current resolution and a constant.
    //  @param		sf::VideoMode& vm		The current videomode of the window (resolution).
    //  @param		unsigned modifier		Used to modify the character size in a more custom way.
    //  @return		unsigned int			The calculated character size value.
    return static_cast<unsigned int>((resolution.x + resolution.y) / modifier);
}

const unsigned int mmath::calcCharSize(const sf::Vector2f resolution, const unsigned modifier)
{
    //  Calculates the character size for text using the current resolution and a constant.
    //  @param		sf::VideoMode& vm		The current videomode of the window (resolution).
    //  @param		unsigned modifier		Used to modify the character size in a more custom way.
    //  @return		unsigned int			The calculated character size value.
    return static_cast<unsigned int>((resolution.x + resolution.y) / modifier);
}