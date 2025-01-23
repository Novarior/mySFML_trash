#include "ProcessGenerationNoice.hpp"

double ProcessGenerationNoice::Interpolate(double a, double b, double x)
{
    double result = a * (1 - x) + b * x;
    if (this->m_data.fastMode)
        return mmath::interpolation::LinInter(x, a, b);

    switch (this->m_data.smoothMode) {
    case 0:
        result = mmath::interpolation::LinInter(x, a, b);
        break;
    case 1:
        result = mmath::interpolation::CosInter(x, a, b);
        break;
    case 2:
        result = mmath::interpolation::CubicInter(x, a, b);
        break;
    case 3:
        result = mmath::interpolation::QuinticInter(x, a, b);
        break;
    case 4:
        result = mmath::interpolation::QuarticInter(x, a, b);
        break;
    case 5:
        result = mmath::interpolation::QuadraticInter(x, a, b);
        break;
    case 6:
        result = mmath::interpolation::HermiteInter(x, a, b);
        break;
    default:
        result = mmath::interpolation::LinInter(x, a, b);
        break;
    }
    return result;
}

double ProcessGenerationNoice::Noise(int i, int x, int y)
{
    // Create an initial value based on the input coordinates
    int n = x + y * 31; // Changed from 57 to 31

    // Apply a bitwise shift and AND operation to get a new value
    n = (n * 0x5DEECE66D) & ((n << 48) - 1); // Changed XOR to AND

    // Compute the values of a, b, and c based on the input data and the seed
    int a = (this->m_data.seed * x), // Changed addition to multiplication
        b = (this->m_data.seed * y), // Changed addition to multiplication
        c = (this->m_data.seed * (x + y)); // Changed addition to multiplication

    // Compute the final value of t
    int t = (n * (n * n * a + b) + c) & 0x7fffffff;

    // Convert t to a floating-point number and return it
    double ret = 1.0 - (double)(t) / 1073741824.0;
    return ret;
}

double ProcessGenerationNoice::SmoothedNoise(int i, int x, int y)
{
    double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) + Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 8, // Changed from 16 to 8
        sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) + Noise(i, x, y + 1)) / 4, // Changed from 8 to 4
        center = Noise(i, x, y) / 2; // Changed from 4 to 2
    return corners + sides + center;
}

double ProcessGenerationNoice::FastSmoothedNoise(int i, int x, int y)
{
    // Compute the noise for the center point only once
    double center = Noise(i, x, y);

    // Compute the noise for the sides, reusing the center noise
    double sides = (center + Noise(i, x + 1, y) + Noise(i, x, y + 1)) / 3;

    // Compute the noise for the corners, reusing the sides and center noise
    double corners = (sides + Noise(i, x + 1, y + 1)) / 2;

    // Return the average of the corners, sides, and center
    return (corners + sides + center) / 3;
}

double ProcessGenerationNoice::getNoice(double x, double y)
{
    double total = 0;
    double frequency = pow(2, this->m_data.frequency);
    double amplifire = this->m_data.amplifire;

    for (int i = 0; i < this->m_data.octaves; ++i) {
        total += InterpolatedNoise((1 + i) % 10, this->m_data.seed + x / frequency, this->m_data.seed + y / frequency) * amplifire;
        frequency /= 2;
        amplifire *= this->m_data.persistence;
    }
    return total / frequency;
}

double ProcessGenerationNoice::InterpolatedNoise(int i, double x, double y)
{
    int integer_X = x;
    double fractional_X = x - integer_X;
    int integer_Y = y;
    double fractional_Y = y - integer_Y;

    // init empty value for interpolated
    double v1 = 0, v2 = 0, v3 = 0, v4 = 0, i1 = 0, i2 = 0;

    if (this->m_data.fastMode) {
        v1 = SmoothedNoise(i, integer_X, integer_Y),
        v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
        v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
        v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
        i1 = Interpolate(v1, v2, fractional_X),
        i2 = Interpolate(v3, v4, fractional_X);
    } else {
        v1 = FastSmoothedNoise(i, integer_X, integer_Y),
        v2 = FastSmoothedNoise(i, integer_X + 1, integer_Y),
        v3 = FastSmoothedNoise(i, integer_X, integer_Y + 1),
        v4 = FastSmoothedNoise(i, integer_X + 1, integer_Y + 1),
        i1 = Interpolate(v1, v2, fractional_X),
        i2 = Interpolate(v3, v4, fractional_X);
    }
    return Interpolate(i1, i2, fractional_Y);
}

ProcessGenerationNoice::ProcessGenerationNoice(mmath::noiceData& data)
    : m_data(data)

{
}

ProcessGenerationNoice::~ProcessGenerationNoice()
{
}

void ProcessGenerationNoice::setSeed(double seed)
{
    this->m_data.seed = seed;
}
double ProcessGenerationNoice::getSeed()
{
    return this->m_data.seed;
}
