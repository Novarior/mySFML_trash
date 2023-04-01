#ifndef CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#define CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#include "../header.h"


struct noiceData
{
    sf::Vector2u mapSize;
    float gridSize;
    long seed;
    unsigned octaves;
    double frequency;
    float persistence;
    sf::Vector2f RenderWindow;
};


class ProcessGenerationNoice
{
    private:
    noiceData m_data;

    public:
    double InterpolatedNoise(int i, double x, double y);
    double Interpolate(double a, double b, double x);
    double SmoothedNoise(int i, int x, int y);
    double Noise(int i, int x, int y);


    ProcessGenerationNoice(noiceData data);
    virtual ~ProcessGenerationNoice();

    void setSeed(double seed);
    double getSeed();
    double getNoice(double x, double y);

};
#endif