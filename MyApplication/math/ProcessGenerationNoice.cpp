#include "ProcessGenerationNoice.hpp"

double ProcessGenerationNoice::Interpolate(double a, double b, double x)
{
    // double ft = x * M_PI;
    // double f = (1 - cos(ft)) * 0.5;
    // return  a*(1-f) + b*f;

    // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
    // return (a - b) * (3.0 - x * 2.0) * x * x + b;
    // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
    // return (a - b) * ((x * (x * 6.0 - 15.0) + 10.0) * x * x * x) + b;
    return a + x * (b - a);

    // function
}

double ProcessGenerationNoice::Noise(int i, int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int a = (this->m_data.seed + x),
        b = (this->m_data.seed + y),
        c = (this->m_data.seed + x + y);
    int t = (n * (n * n * a + b) + c) & 0x7fffffff;
    double ret = 1.0 - (double)(t) / 0x7fffffff;
    return ret;
}

double ProcessGenerationNoice::SmoothedNoise(int i, int x, int y)
{
    double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) + Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16,
           sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) + Noise(i, x, y + 1)) / 8,
           center = Noise(i, x, y) / 4;
    return corners + sides + center;
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

    double v1 = SmoothedNoise(i, integer_X, integer_Y),
           v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
           v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
           v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
           i1 = Interpolate(v1, v2, fractional_X),
           i2 = Interpolate(v3, v4, fractional_X);
    return Interpolate(i1, i2, fractional_Y);
}

ProcessGenerationNoice::ProcessGenerationNoice(noiceData data)
{
    this->m_data = data;
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
