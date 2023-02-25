#include "MutationNoice.hpp"


SomeNoice::SomeNoice(){}
SomeNoice::~SomeNoice(){}

/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
double SomeNoice::interpolate(double a0, double a1, double w) {
    /* // You may want clamping by inserting:
     * if (0.0 > w) return a0;
     * if (1.0 < w) return a1;
     */
     //return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    //return (a1 - a0) * w + a0;
    /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
     *
     * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
     */
     return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}
/* Create pseudorandom direction vector
 */
sf::Vector2f SomeNoice::randomGradient(double ix, double iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    double random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
    return sf::Vector2f(cos(random),sin(random));
}

// Computes the dot product of the distance and gradient vectors.
double SomeNoice::dotGridGradient(double ix, double iy, double x, double y) {
    // Get gradient from integer coordinates
    sf::Vector2f gradient = this->randomGradient(ix, iy);
    

    // Compute the distance vector
    double dx = x - (double)ix;
    double dy = y - (double)iy;

    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y);
}

// Compute Perlin noise at coordinates x, y
double SomeNoice::perlin(double x, double y) {
    // Determine grid cell coordinates
    double x0 = (int)floor(x);
    double x1 = x0 + 1;
    double y0 = (int)floor(y);
    double y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    double sx = x - (double)x0;
    double sy = y - (double)y0;

    // Interpolate between grid podouble gradients
    double n0, n1, ix0, ix1, value;

    n0 = this->dotGridGradient(x0, y0, x, y);
    n1 = this->dotGridGradient(x1, y0, x, y);
    ix0 = this->interpolate(n0, n1, 1);

    n0 = this->dotGridGradient(x0, y1, x, y);
    n1 = this->dotGridGradient(x1, y1, x, y);
    ix1 = this->interpolate(n0, n1, 1);
    value = interpolate(ix0, ix1, 1);
    std::cout << sx << '\t'<<sy <<'\n';
    return value*0.5+0.5; // Will return in range -1 to 1. To make it in range 0 to 1, multiply by 0.5 and add 0.5
}