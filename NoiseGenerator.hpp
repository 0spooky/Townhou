#ifndef NOISEGEN_HPP_INCLUDED
#define NOISEGEN_HPP_INCLUDED

class PerlinNoise
{
public:

  // Constructor
    PerlinNoise();
    PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _random_seed);

  // Get Height
    double getHeight(double x, double y) const;

  // Get
    double getPersistence() const { return m_persistence; }
    double getFrequency()   const { return m_frequency;   }
    double getAmplitude()   const { return m_amplitude;   }
    int    getOctaves()     const { return m_octaves;     }
    int    getRandomSeed()  const { return m_random_seed;  }

  // Set
    void set(double _persistence, double _frequency, double _amplitude, int _octaves, int _random_seed);

    void setPersistence(double _persistence) { m_persistence = _persistence; }
    void setFrequency(  double _frequency)   { m_frequency = _frequency;     }
    void setAmplitude(  double _amplitude)   { m_amplitude = _amplitude;     }
    void setOctaves(    int    _octaves)     { m_octaves = _octaves;         }
    void setRandomSeed( int    _random_seed)  { m_random_seed = _random_seed;   }

private:

    double total(double i, double j) const;
    double getValue(double x, double y) const;
    double interpolate(double x, double y, double a) const;
    double noise(int x, int y) const;

    double m_persistence, m_frequency, m_amplitude;
    int m_octaves, m_random_seed;

};


#endif // NOISEGEN_HPP_INCLUDED
