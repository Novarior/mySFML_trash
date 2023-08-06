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
const float mmath::p2pX(const float perc, const sf::VideoMode& vm)
{
    //  Converts a percentage value to pixels relative to the current resolution in the x-axis.
    //  @param		float perc				The percentage value.
    //  @param		sf::VideoMode& vm		The current videomode of the window (resolution).
    //  @return		float					The calculated pixel value.
    return floor(static_cast<float>(vm.width) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const sf::Vector2f& vec)
{
    return floor(static_cast<float>(vec.x) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const unsigned int& i)
{
    return floor(static_cast<float>(i) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const float& i)
{
    return floor(static_cast<float>(i) * (perc / 100.f));
}
const float mmath::p2pY(const float perc, const sf::VideoMode& vm)
{
    return floor(static_cast<float>(vm.height) * (perc / 100.f));
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