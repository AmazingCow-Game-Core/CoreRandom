//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Random.h                                                      //
//  Project   : CoreRandom                                                    //
//  Date      : Apr 06, 2016                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2016 - 2018                                      //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

// std
#include <random>
#include <time.h>
// AmazingCow Libs
#include "acow/cpp_goodies.h"

//------------------------------------------------------------------------------
// Undefine Windows crap...
#if (ACOW_OS_IS_WINDOWS) 
    #undef max
    #undef min
#endif

namespace acow { namespace RandomUtils {

class Random
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    //--------------------------------------------------------------------------
    /// @brief
    ///   A meta value to indicate to Random()
    ///   that it should use a random seed.
    /// @see Random(), getSeed(), isUsingRandomSeed().
    static const int kRandomSeed;

    ///-------------------------------------------------------------------------
    /// @brief Typedef to reduce verbosity.
    typedef std::mt19937 NumberGeneratorType;

    ///-------------------------------------------------------------------------
    /// @brief Typedef to reduce verbosity.
    typedef std::uniform_int_distribution<int> IntegerDistributionType;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Constructs a Random object with the target seed.
    /// @param seed
    ///   The seed that the random number generator will
    ///   be initialized. If seed is kRandomSeed it will be
    ///   selected from the system std::time(nullptr).
    /// @see kRandomSeed, reseed(), getSeed(), isUsingRandomSeed().
    inline Random(int seed = kRandomSeed) noexcept
        : m_randomDist(0, 1)
    {
        Reseed(seed);
    }


    //------------------------------------------------------------------------//
    // Generation Methods                                                     //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [0, std::numeric_limits<int>::max()].
    /// @returns
    ///   An integer in [0, std::numeric_limits<int>::max()] range.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(int max), next(int min, int max);
    inline int
    Next() noexcept
    {
        ResetRange(0, std::numeric_limits<int>::max());
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [0, max].
    /// @param max
    ///   The upperbound of the range.
    /// @warning
    ///   max must be >= 0.
    /// @returns
    ///   An integer in [0, max] range.
    /// @throws
    ///   std::invalid_argument if max < 0.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(), next(int min, int max);
    inline int
    Next(int max) noexcept
    {
        ResetRange(0, max);
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random integer between [min, max].
    /// @param min
    ///   The lowerbound of the range.
    /// @param max
    ///   The upperbound of the range.
    /// @warning
    ///   max >= min.
    /// @returns
    ///   An integer in [min, max] range.
    /// @throws
    ///   std::invalid_argument if max < min.
    /// @note
    ///   next return is INCLUSIVE.
    /// @see next(), next(int max);
    inline int
    Next(int min, int max) noexcept
    {
        ResetRange(min, max);
        return m_dist(m_rnd);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Generate a random bool value.
    /// @returns
    ///   A bool value.
    /// @see next(), next(int max), next(int min, int max);
    inline bool
    NextBool() noexcept
    {
        return static_cast<bool>(m_randomDist(m_rnd));
    }


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the reference for the internal number generator.
    /// @returns
    ///   A reference for the internal number generator.
    /// @see NumberGeneratorType.
    inline NumberGeneratorType&
    GetNumberGenerator() noexcept
    {
        return m_rnd;
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the constant reference for the internal number generator.
    /// @returns
    ///   A constant reference for the internal number generator.
    /// @see NumberGeneratorType.
    inline const NumberGeneratorType&
    GetNumberGenerator() const noexcept
    {
        return m_rnd;
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the reference for the internal integer distribution.
    /// @returns
    ///   A reference for the internal integer distribution.
    /// @see IntegerDistributionType.
    inline IntegerDistributionType&
    GetIntDistribution() noexcept
    {
        return m_dist;
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the constant reference for the internal integer distribution.
    /// @returns
    ///   A constant reference for the internal integer distribution.
    /// @see IntegerDistributionType.
    inline const IntegerDistributionType&
    GetIntDistribution() const noexcept
    {
        return m_dist;
    }


    ///-------------------------------------------------------------------------
    /// @brief
    ///   Reseed object with the target seed.
    /// @param seed
    ///   The seed that the random number generator will
    ///   be initialized. If seed is kRandomSeed it will be
    ///   selected from the system std::time(nullptr).
    /// @see getSeed(), isUsingRandomSeed().
    inline void
    Reseed(int seed = kRandomSeed) noexcept
    {
        m_seed = (seed == Random::kRandomSeed)
              ? time(nullptr)
              : seed;

        m_isUsingRandomSeed = (seed == kRandomSeed);
        m_rnd.seed(m_seed);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the actual seed used.
    /// @returns
    ///   The actual seed used in this object - If Random was created
    ///   using kRandomSeed it will the chosen seed, otherwise will
    ///   return the argument used in the CTOR.
    inline int
    GetSeed() const
    {
        return m_seed;
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Checks if CTOR was initialized with kRandomSeed.
    /// @returns
    ///   True if kRandomSeed was used, False otherwise.
    inline bool
    IsUsingRandomSeed() const
    {
        return m_isUsingRandomSeed;
    }


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    inline void
    ResetRange(int min, int max) noexcept
    {
        ACOW_ASSERT(
            min <= max,
            "Invalid values given - Min: (%d) - Max: (%d)",
            min,
            max
        );

        // Just make sure that in runtime we give valid results
        // no matter what user passed to us...
        if(min > max) { std::swap(min, max); }

        // Reset the range..
        if(m_dist.min() != min || m_dist.max() != max) {
            m_dist.param(
                std::uniform_int_distribution<int>::param_type(min, max)
            );
        }
    }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    // Housekeeping.
    int  m_seed;
    bool m_isUsingRandomSeed;

    // Random.
    NumberGeneratorType     m_rnd;
    IntegerDistributionType m_dist;
    IntegerDistributionType m_randomDist;
};

} // namespace RandomUtils
} // namespace acow
