#ifndef CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#define CPP_MATH_PSEDO_GENERATION_NOICE_HPP


#include "mymath.hpp"

struct noiceData
{
    unsigned int mapSizeX;
    unsigned int mapSizeY;
    float gridSize;
    long seed;
    unsigned octaves;
    double frequency;
    float persistence;
    unsigned int RenderWindowX;
    unsigned int RenderWindowY;
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