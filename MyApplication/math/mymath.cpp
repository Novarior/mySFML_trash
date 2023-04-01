#include "mymath.hpp"

double randDoubleFromToNum(double Min_val, double Max_val)
{
    return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}

int randIntFromToNum(int Min_val, int Max_val)
{
    return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}
double randZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}
