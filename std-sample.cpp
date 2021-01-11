/************************************************************
 *                 STD::SAMPLE() ALGORITHM                  *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 introduced the std::sample() algorithm that
 * allows to randomly select n elements in a range and 
 * append them into the output iterator.
 * 
 * template< class PopulationIterator, 
 *           class SampleIterator,
 *           class Distance, class URBG >
 * SampleIterator sample( PopulationIterator first, 
 *                        PopulationIterator last,
                          SampleIterator     out, 
                          Distance           n,
                          URBG&&             g );

 * NB : The relative order of elements is preserved if
 * PopulationIterator meets the requirements of
 * LegacyForwardIterator.
 * 
 * NB : if n >= #elements in [first, last]
 * std::sample will return last - first elements.
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/algorithm/sample
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    std::string inStr{ "abcdefghijklmnopqrstuvwxyz" }, outStr;
    int         elements { 10 };

    std::sample( std::begin( inStr ), 
                 std::end  ( inStr ),
                 std::back_inserter(outStr),
                 elements,
                 std::mt19937{ std::random_device{}() } );
    
    std::cout << "Here are "                << elements 
              << " elements from '"         << inStr
              << "' using std::sample():\n" << outStr
              << "\n";

    return EXIT_SUCCESS;
}

/*
Here are 10 elements from 'abcdefghijklmnopqrstuvwxyz' using std::sample():
dehijnpuvy
*/