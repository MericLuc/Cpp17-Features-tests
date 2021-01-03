/************************************************************
 *          String conversion using std::from_chars         *
 *                     and std::to_chars                    *
 ************************************************************/

/*!
 * @brief C++17 introduces std::from_chars and std::to_chars
 *        to perform fast, low-level string conversions.
 * 
 * See https://en.cppreference.com/w/cpp/utility/from_chars
 * and https://en.cppreference.com/w/cpp/utility/to_chars
 * for more details.
 */

/*!
 * @note Here are a list of conversion functions
 *       that are provided by C++ :
 *          - sprintf
 *          - snprintf 
 *          - sscanf 
 *          - atol 
 *          - strtol
 *          - strstream 
 *          - stringstream 
 *          - to_string 
 *          - stoi
 * 
 *       We will try to compare their performances
 *       with a basic benchmark.
 *       We will perform comparison between the following :
 *          - from_chars/to_chars
 *          - stoi/to_string
 *          - atoi/sprintf
 *          - stringstream/ostringstream
 */

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <charconv>
#include <random>
#include <chrono>
#include <thread>
#include <sstream>
#include <stdlib.h>

#define CYCLE_NB 1000
#define ELEMENTS 1000

//////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief A stopwatch class to perform measures
 */
template < typename Clock = std::chrono::high_resolution_clock >
class stopwatch
{
private:
    const std::string                m_title;
    const typename Clock::time_point m_start;

public:
    stopwatch(const std::string& p_title = "") : m_title(p_title), m_start( Clock::now() ) {}
    ~stopwatch() {
        std::cout << "Computation using " << m_title << " performed in "
                  << elapsed_time<unsigned int, std::chrono::milliseconds>() << " ms\n";
    }

    template < typename Rep   = typename Clock::duration::rep, 
               typename Units = typename Clock::duration >
    Rep elapsed_time(void) const
    {
        std::atomic_thread_fence(std::memory_order_relaxed);
        auto l_time = std::chrono::duration_cast<Units>(Clock::now() - m_start).count();
        std::atomic_thread_fence(std::memory_order_relaxed);

        return static_cast<Rep>(l_time);
    }
};

using precise_stopwatch   = stopwatch<>;
using system_stopwatch    = stopwatch<std::chrono::system_clock>;
using monotonic_stopwatch = stopwatch<std::chrono::steady_clock>;

//////////////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief Creates a vector of size p_size 
 *        filled with random integers.
 */
std::vector<int> createIntVector(int p_size) 
{
    std::uniform_int_distribution<int> distrib( 0, INT_MAX );
    std::default_random_engine         random_engine;

    std::vector<int> myVec( p_size );
    for ( auto& v : myVec ) { v = distrib(random_engine); }

    return myVec;
}

//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "\t\tPARAMETERS\nElements - " << ELEMENTS 
              << "\nNumber of cycles - "       << CYCLE_NB;
    std::cout << "\n--------------------------------------------------\n";

    auto myIntVec{createIntVector    (ELEMENTS)};// Vector of integers to convert to string
    std::vector<std::string> myStrVec(ELEMENTS); // Vector containing the conversion results
    std::vector<int>         myResVec(ELEMENTS); // Vector containing the back conversion results
    std::string              resStr   (15, ' '); // String holding the result of std::to_chars()
    
    // std::to_chars() and st::from_chars()
    {
        {
            stopwatch myWatch("std::to_chars()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    const auto l_res = std::to_chars( resStr.data(), 
                                                    resStr.data() + resStr.size(), 
                                                    myIntVec[elm] );
                    myStrVec[elm] = std::string_view( resStr.data(),
                                                    l_res.ptr - resStr.data());
                }
            }
        }

        {
            stopwatch myWatch("std::from_chars()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    std::from_chars( myStrVec[elm].data(),
                                    myStrVec[elm].data() + myStrVec[elm].size(),
                                    myResVec[elm] );
                }
            }
        }

        // Make sure final output is the same as input
        // i.e. myResVec == myIntVec for each element
        if ( myIntVec != myResVec ) 
        {
            std::cout << "SOMETHING WENT WRONG!\n";
        }
    }

    // std::to_string() and std::stoi()
    {
        {
            stopwatch myWatch("std::to_string()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    myStrVec[elm] = std::to_string( myIntVec[elm] );
                }
            }
        }

        {
            stopwatch myWatch("std::stoi()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    myResVec[elm] = std::stoi( myStrVec[elm] );
                }
            }
        }

        // Make sure final output is the same as input
        // i.e. myResVec == myIntVec for each element
        if ( myIntVec != myResVec ) 
        {
            std::cout << "SOMETHING WENT WRONG!\n";
        }
    }

    // std::sprintf() and std::atoi()
    {
        {
            stopwatch myWatch("std::sprintf()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    std::sprintf( myStrVec[elm].data(), "%d", myIntVec[elm] );
                }
            }
        }

        {
            stopwatch myWatch("std::atoi()");
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    myResVec[elm] = std::atoi( myStrVec[elm].c_str() );
                }
            }
        }

        // Make sure final output is the same as input
        // i.e. myResVec == myIntVec for each element
        if ( myIntVec != myResVec ) 
        {
            std::cout << "SOMETHING WENT WRONG!\n";
        }
    }

    // std::ostringstream and std::stringstream
    {
        {
            stopwatch myWatch("std::ostringstream()");
            std::ostringstream ss;
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    ss << myIntVec[elm];
                    myStrVec[elm] = ss.str();
                    ss.str(std::string());
                }
            }
        }

        {
            stopwatch myWatch("std::stringstream()");
            std::stringstream ss;
            for ( size_t cycle = 0; cycle < CYCLE_NB; ++cycle ) 
            {
                for ( size_t elm = 0; elm < myIntVec.size(); ++elm ) 
                {
                    ss << myStrVec[elm];
                    ss >> myResVec[elm];
                    ss.str("");
                }
            }
        }

        // Make sure final output is the same as input
        // i.e. myResVec == myIntVec for each element
        if (myIntVec != myResVec)
        {
            std::cout << "SOMETHING WENT WRONG!\n";
        }
    }

    return EXIT_SUCCESS;
}

/*
 --------------------------------------------------
 		PARAMETERS
 Elements - 1000
 Number of cycles - 1000
 --------------------------------------------------
 Computation using std::to_chars() performed in 23 ms
 Computation using std::from_chars() performed in 12 ms
 Computation using std::to_string() performed in 65 ms
 Computation using std::stoi() performed in 68 ms
 Computation using std::sprintf() performed in 54 ms
 Computation using std::atoi() performed in 33 ms
 Computation using std::ostringstream() performed in 64 ms
 Computation using std::stringstream() performed in 18 ms
 */