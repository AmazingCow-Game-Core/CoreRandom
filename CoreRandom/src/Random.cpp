//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Random.cpp                                                    //
//  Project   : CoreRandom                                                    //
//  Date      : Apr 06, 2016                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2016 - 2018                                      //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "../include/Random.h"
// std
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

// Usings
USING_NS_CORERANDOM;


//----------------------------------------------------------------------------//
// Enums / Constants / Typdefs                                                //
//----------------------------------------------------------------------------//
const int Random::kRandomSeed = -1;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Random::Random(int seed) :
    m_randomDist(0, 1)
{
    reseed(seed);
}


//----------------------------------------------------------------------------//
// Generation Methods                                                         //
//----------------------------------------------------------------------------//
int Random::next()
{
    resetRange(0, std::numeric_limits<int>::max());
    return m_dist(m_rnd);
}

int Random::next(int max)
{
    resetRange(0, max);
    return m_dist(m_rnd);
}

int Random::next(int min, int max)
{
    resetRange(min, max);
    return m_dist(m_rnd);
}

bool Random::nextBool()
{
    return static_cast<bool>(m_randomDist(m_rnd));
}


//----------------------------------------------------------------------------//
// Helper Methods                                                             //
//----------------------------------------------------------------------------//
Random::NumberGeneratorType&  Random::getNumberGenerator()
{
    return m_rnd;
}

const Random::NumberGeneratorType&  Random::getNumberGenerator() const
{
    return m_rnd;
}

Random::IntegerDistributionType&  Random::getIntDistribution()
{
    return m_dist;
}

const Random::IntegerDistributionType&  Random::getIntDistribution() const
{
    return m_dist;
}


void Random::reseed(int seed /* = kRandomSeed */)
{
    m_seed = (seed == Random::kRandomSeed)
              ? std::time(nullptr)
              : seed;

    m_isUsingRandomSeed = (seed == kRandomSeed);
    m_rnd.seed(m_seed);
}

int Random::getSeed() const
{
    return m_seed;
}

bool Random::isUsingRandomSeed() const
{
    return m_isUsingRandomSeed;
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
inline void Random::resetRange(int min, int max)
{
    if(min > max)
    {
        std::stringstream ss;
        ss << "CoreRandom::Random - Invalid range values - "
           << "min must be <= max - "
           << "Got min: " << min << " max: " << max;

        throw std::invalid_argument(ss.str());
    }

    if(m_dist.min() != min || m_dist.max() != max)
        m_dist.param(std::uniform_int_distribution<int>::param_type(min, max));
}
