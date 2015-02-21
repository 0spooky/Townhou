#include <cmath>
#include "Noisegen.hpp"

PerlinNoise::PerlinNoise()
{
    m_persistence = 0;
    m_frequency = 0;
    m_amplitude  = 0;
    m_octaves = 0;
    m_random_seed = 0;
}

PerlinNoise::PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _random_seed)
{
    m_persistence = _persistence;
    m_frequency = _frequency;
    m_amplitude  = _amplitude;
    m_octaves = _octaves;
    m_random_seed = 2 + _random_seed * _random_seed;
}

void PerlinNoise::set(double _persistence, double _frequency, double _amplitude, int _octaves, int _random_seed)
{
    m_persistence = _persistence;
    m_frequency = _frequency;
    m_amplitude  = _amplitude;
    m_octaves = _octaves;
    m_random_seed = 2 + _random_seed * _random_seed;
}

double PerlinNoise::getHeight(double x, double y) const
{
    return m_amplitude * total(x, y);
}

double PerlinNoise::total(double i, double j) const
{
    //properties of one octave (changing each loop)
    double total = 0.0f;
    double _amplitude = 1;
    double _frequency = m_frequency;

    for(int k = 0; k < m_octaves; k++)
    {
        total += getValue(j * _frequency + m_random_seed, i * _frequency + m_random_seed) * _amplitude;
        _amplitude *= m_persistence;
        _frequency *= 2;
    }

    return total;
}

double PerlinNoise::getValue(double x, double y) const
{
    int Xint = floor(x);
    int Yint = floor(y);
    double Xfrac = x - Xint;
    double Yfrac = y - Yint;

    //noise values
    double n00 = noise(Xint-1, Yint-1);                 // (0,0)_________           //
    double n01 = noise(Xint-1, Yint);                   //      \__\__\__\          //
    double n02 = noise(Xint-1, Yint+1);                 //       \__\__\__\         //
    double n03 = noise(Xint-1, Yint+2);                 //        \__\__\__\(3,3)   //

    double n10 = noise(Xint, Yint-1);                   //      (Xint, Yint) == (1,1)
    double n11 = noise(Xint, Yint);
    double n12 = noise(Xint, Yint+1);
    double n13 = noise(Xint, Yint+2);

    double n20 = noise(Xint+1, Yint-1);
    double n21 = noise(Xint+1, Yint);
    double n22 = noise(Xint+1, Yint+1);
    double n23 = noise(Xint+1, Yint+2);

    double n30 = noise(Xint+2, Yint-1);
    double n31 = noise(Xint+2, Yint);
    double n32 = noise(Xint+2, Yint+1);
    double n33 = noise(Xint+2, Yint+2);

    //find the noise values of the four corners
    double x0y0 = 0.0625*(n00+n02+n20+n22) + 0.125*(n01+n10+n21+n12) + 0.25*(n11);
    double x1y0 = 0.0625*(n10+n12+n30+n32) + 0.125*(n11+n31+n20+n22) + 0.25*(n21);
    double x0y1 = 0.0625*(n01+n03+n21+n23) + 0.125*(n02+n22+n11+n13) + 0.25*(n12);
    double x1y1 = 0.0625*(n11+n13+n31+n33) + 0.125*(n12+n32+n21+n23) + 0.25*(n22);

    //interpolate between those values according to the x and y fractions
    double v1 = interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
    double v2 = interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
    double fin = interpolate(v1, v2, Yfrac);  //interpolate in y direction

    return fin;
}

double PerlinNoise::interpolate(double x, double y, double a) const
{
    double negA = 1.0 - a;
    double fac1 = 3.0 * (negA * negA) - 2.0 * (negA * negA * negA);
    double fac2 = 3.0 * (a * a) - 2.0 * (a * a * a);

    return x * fac1 + y * fac2; //add the weighted factors
}

double PerlinNoise::noise(int x, int y) const
{
    int n = x * 29 + y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - t * 0.931322574615478515625e-9;/// 1073741824.0);
}


