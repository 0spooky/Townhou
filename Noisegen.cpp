#include <cmath>
#include "Noisegen.hpp"

PerlinNoise::PerlinNoise()
{
    persistence = 0;
    frequency = 0;
    amplitude  = 0;
    octaves = 0;
    randomseed = 0;
}

PerlinNoise::PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
    persistence = _persistence;
    frequency = _frequency;
    amplitude  = _amplitude;
    octaves = _octaves;
    randomseed = 2 + _randomseed * _randomseed;
}

void PerlinNoise::Set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
{
    persistence = _persistence;
    frequency = _frequency;
    amplitude  = _amplitude;
    octaves = _octaves;
    randomseed = 2 + _randomseed * _randomseed;
}

double PerlinNoise::GetHeight(double x, double y) const
{
    return amplitude * Total(x, y);
}

double PerlinNoise::Total(double i, double j) const
{
    //properties of one octave (changing each loop)
    double total = 0.0f;
    double _amplitude = 1;
    double _frequency = frequency;

    for(int k = 0; k < octaves; k++)
    {
        total += GetValue(j * _frequency + randomseed, i * _frequency + randomseed) * _amplitude;
        _amplitude *= persistence;
        _frequency *= 2;
    }

    return total;
}

double PerlinNoise::GetValue(double x, double y) const
{
    int Xint = floor(x);
    int Yint = floor(y);
    double Xfrac = x - Xint;
    double Yfrac = y - Yint;

    //noise values
    double n00 = Noise(Xint-1, Yint-1);                 // (0,0)_________           //
    double n01 = Noise(Xint-1, Yint);                   //      \__\__\__\          //
    double n02 = Noise(Xint-1, Yint+1);                 //       \__\__\__\         //
    double n03 = Noise(Xint-1, Yint+2);                 //        \__\__\__\(3,3)   //

    double n10 = Noise(Xint, Yint-1);                   //      (Xint, Yint) == (1,1)
    double n11 = Noise(Xint, Yint);
    double n12 = Noise(Xint, Yint+1);
    double n13 = Noise(Xint, Yint+2);

    double n20 = Noise(Xint+1, Yint-1);
    double n21 = Noise(Xint+1, Yint);
    double n22 = Noise(Xint+1, Yint+1);
    double n23 = Noise(Xint+1, Yint+2);

    double n30 = Noise(Xint+2, Yint-1);
    double n31 = Noise(Xint+2, Yint);
    double n32 = Noise(Xint+2, Yint+1);
    double n33 = Noise(Xint+2, Yint+2);

    //find the noise values of the four corners
    double x0y0 = 0.0625*(n00+n02+n20+n22) + 0.125*(n01+n10+n21+n12) + 0.25*(n11);
    double x1y0 = 0.0625*(n10+n12+n30+n32) + 0.125*(n11+n31+n20+n22) + 0.25*(n21);
    double x0y1 = 0.0625*(n01+n03+n21+n23) + 0.125*(n02+n22+n11+n13) + 0.25*(n12);
    double x1y1 = 0.0625*(n11+n13+n31+n33) + 0.125*(n12+n32+n21+n23) + 0.25*(n22);

    //interpolate between those values according to the x and y fractions
    double v1 = Interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
    double v2 = Interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
    double fin = Interpolate(v1, v2, Yfrac);  //interpolate in y direction

    return fin;
}

double PerlinNoise::Interpolate(double x, double y, double a) const
{
    double negA = 1.0 - a;
    double fac1 = 3.0 * (negA * negA) - 2.0 * (negA * negA * negA);
    double fac2 = 3.0 * (a * a) - 2.0 * (a * a * a);

    return x * fac1 + y * fac2; //add the weighted factors
}

double PerlinNoise::Noise(int x, int y) const
{
    int n = x * 29 + y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}


