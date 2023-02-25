#include "mymath.hpp"

sf::Color getRandomColor()
{

    return sf::Color(rand() % 255 + 1,rand() % 255 + 1,rand() % 255 + 1);
}

sf::Color getRandomColor(unsigned short gradient)
{
    switch(gradient)
    {
        case RED_GRADIENT:
        return sf::Color(rand() % 255 + 1,0,0);
        break;
        case GREEN_GRADIENT:
        return sf::Color(0,rand() % 255 + 1,0);
        break;
        case BLURE_GRADIENT:
        return sf::Color(0,0,rand() % 255 + 1);
        break;
        case GRAY_GRADIENT:
        int i=rand() % 255 + 1;
        return sf::Color(i,i,i);
        break;
    }
    return sf::Color(0,0,0,0);
}
double randDoubleFromToNum(double Min_val, double Max_val)
{
    return Min_val + (rand() / ( RAND_MAX / (Max_val-Min_val)));  
}

int randIntFromToNum(int Min_val, int Max_val)
{
    return Min_val + (rand() / ( RAND_MAX / (Max_val-Min_val)));  
}
double randZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}
