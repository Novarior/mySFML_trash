#ifndef CPP_MATH_PERLIN_NOISE_HPP
#define CPP_MATH_PERLIN_NOISE_HPP

#include "mymath.hpp"

class PerlinNoise {
public:
    PerlinNoise()
    {
        // Initialize the permutation vector with the reference values
        for (int i = 0; i < 256; ++i)
            p[i] = i;

        // shuffle the array
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(p, p + 256, gen);

        // duplicate the permutation vector
        for (int i = 0; i < 256; ++i)
            p[256 + i] = p[i];
    }
    double Noise(double x_cord, double y_cord, double minValue = -1, double maxValue = 1.0)
    {
        int X = (int)floor(x_cord) & 255;
        int Y = (int)floor(y_cord) & 255;

        x_cord -= floor(x_cord);
        y_cord -= floor(y_cord);

        double u = mmath::Fade(x_cord);
        double v = mmath::Fade(y_cord);

        int A = p[X] + Y;
        int AA = p[A];
        int AB = p[A + 1];
        int B = p[X + 1] + Y;
        int BA = p[B];
        int BB = p[B + 1];

        double res = mmath::Lerp(v,
            mmath::Lerp(u, mmath::Gradient(p[AA], x_cord, y_cord), mmath::Gradient(p[BA], x_cord - 1, y_cord)),
            mmath::Lerp(u, mmath::Gradient(p[AB], x_cord, y_cord - 1), mmath::Gradient(p[BB], x_cord - 1, y_cord - 1)));

        return mmath::normalize(res, minValue, maxValue);
    }

private:
    int p[512]; // permutation table
};
#endif // CPP_MATH_PERLIN_NOISE_HPP