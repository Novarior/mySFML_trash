#ifndef NOICEMODEL_TUNELNOICE_HPP
#define NOICEMODEL_TUNELNOICE_HPP

#include <../../header.h>

class SimplexNoice {
public:
    SimplexNoice();
    virtual ~SimplexNoice();

    unsigned int getSeed() { return this->m_seed; }
    void setSeed(unsigned int seed) { this->m_seed = seed; }

private:
    sf::Vector2u size;
    unsigned int m_seed;
    unsigned int octaves;
    float frequency;
    float amplitude;
    float lacunarity;
    float persistence;
    float offset_x;
    float offset_y;
    float offset_z;

    float getNoise(float x, float y);

    void noice();
};

#endif // NOICEMODEL_TUNELNOICE_HPP