#ifndef CPP_MATH_GENERATION_PSEUDO_RANDOM_NUMBER_HPP
#define CPP_MATH_GENERATION_PSEUDO_RANDOM_NUMBER_HPP

#include "../header.h"

enum colorMode { RED_GRADIENT, GREEN_GRADIENT, BLURE_GRADIENT, GRAY_GRADIENT };

double randZeroToOne();

double randDoubleFromToNum(double Min_val, double Max_val);
int randIntFromToNum(int Min_val, int Max_val);


#endif