/************************************************************
 *     String matching using std::search and searchers      *
 ************************************************************/

/*!
 * @brief C++14 introduced std::search as a generic way to search for
 *        patterns in a given range - but the performance was quite low.
 * 
 *        C++17 got us new std::search overloads allowing us to specify
 *        searching algorithms with linear complexity like :
 *          - boyer moore algorithm
 *          - boyer_moore_horspool_searcher 
 * 
 * More infos here :
 *   - https://en.cppreference.com/w/cpp/algorithm/search
 *   - https://en.cppreference.com/w/cpp/utility/functional/boyer_moore_searcher
 */

/*!
 * @note this is a basic benchmark to compare
 *       std::search with default algorithm, with new searchers
 *       and std::string::find.
 */

#include <iostream>
#include <string>
#include <functional>
#include <time-measure.hpp>
#include <fileLoader.hpp>

//////////////////////////////////////////////////////////////////////////////////////////
#define INPUT_FILE   "./input/HP.txt" // File path to import text from
#define ITERATIONS   1000             // Number of time the search is performed
#define PATTERN_SIZE 1000             // The size of the pattern to search

int main()
{
    int pattern_start_pos { 200000 };
    std::optional<std::string> fileIn = loadFile( INPUT_FILE );

    if ( !fileIn.has_value() )
    {
        std::cout << "Could not open file '" << INPUT_FILE << "\n";
        return EXIT_SUCCESS;
    }

    std::string pattStr( fileIn.value(), pattern_start_pos, PATTERN_SIZE );
    std::string fileStr { fileIn.value() };

    std::cout << "\n---------------------------------\n";
    std::cout << "Input file   : " << INPUT_FILE << "\n";
    std::cout << "Iterations   : " << ITERATIONS << "\n";
    std::cout << "File size    : " << fileStr.size() << " chars\n";
    std::cout << "Pattern size : " << pattStr.size() << " chars";
    std::cout << "\n---------------------------------\n";

    {
        stopwatch myWatch("std::find");
        for ( size_t cycle = 0; cycle < ITERATIONS; ++cycle )
        {
            if ( size_t l_res = fileStr.find( pattStr ); 
                 l_res == std::string::npos ) 
            {
                std::cout << "\tERROR - string not found!\n";
                return -1;
            }
        }
    }

    {
        stopwatch myWatch("std::search default");
        for ( size_t cycle = 0; cycle < ITERATIONS; ++cycle )
        {
            if ( auto l_res = std::search( std::begin( fileStr ),
                                           std::end  ( fileStr ),
                                           std::begin( pattStr ),
                                           std::end  ( pattStr ) );
                 l_res == std::end( fileStr ) ) 
            {
                std::cout << "\tERROR - string not found!\n";
                return -1;
            }
        }
    }

    {
        stopwatch myWatch("std::search boyer_moore");
        for ( size_t cycle = 0; cycle < ITERATIONS; ++cycle )
        {
            if ( auto l_res = std::search( std::begin( fileStr ),
                                           std::end  ( fileStr ),
                                           std::boyer_moore_searcher(
                                                std::begin( pattStr ),
                                                std::end  ( pattStr ) ) );
                 l_res == std::end( fileStr ) ) 
            {
                std::cout << "\tERROR - string not found!\n";
                return -1;
            }
        }
    }

    {
        stopwatch myWatch("std::search boyer_moore_horspool");
        for ( size_t cycle = 0; cycle < ITERATIONS; ++cycle )
        {
            if ( auto l_res = std::search( std::begin( fileStr ),
                                           std::end  ( fileStr ),
                                           std::boyer_moore_horspool_searcher(
                                                std::begin( pattStr ),
                                                std::end  ( pattStr ) ) );
                 l_res == std::end( fileStr ) ) 
            {
                std::cout << "\tERROR - string not found!\n";
                return -1;
            }
        }
    }

    return EXIT_SUCCESS;
}

/*
 ---------------------------------
 Input file   : ./input/HP.txt
 Iterations   : 1000
 File size    : 492161 chars
 Pattern size : 1000 chars
 ---------------------------------
 std::find performed in 149 ms
 std::search default performed in 96 ms
 std::search boyer_moore performed in 16 ms
 std::search boyer_moore_horspool performed in 16 ms
*/