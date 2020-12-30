/************************************************************
 *               COMPRESS/DECOMPRESS STRINGS                *
 ************************************************************/

/*!
 * @brief Typical interview question.
 *        The goal is to perform string compression/decompression.
 *        For example, considering the input "Okkk"
 *              Compressed string should be "1O3k"
 *              Decompressed should of course be "Okkk"
 *
 *        We will use std::tuple and <algorithm> features
 *        (std::find_if) to answer it.
 */

/*!
 * @note These functions suppose the input string
 *       is correctly formatted.
 *       They are not safe for real-life example !
 * 
 *       To make sure about that, you can try these
 *       functions with an input string containing a number...
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <iterator>
#include <vector>

template < typename It >
std::tuple< It, char, std::size_t > getNext( It p_cur, It p_end ) {
    if ( p_cur == p_end ) { return { p_cur, '#', 0 }; }

    const char curV { *p_cur };
    const It   nxtIt( std::find_if( p_cur, p_end, 
                            [curV](char nxtV){ return curV != nxtV; }) );
    
    return { nxtIt, curV, std::distance(p_cur, nxtIt) };
}

std::string compress ( const std::string& p_in ) {
    auto       curIt( std::begin(p_in) );
    const auto endIt( std::end  (p_in) );
    std::stringstream res;

    while( curIt != endIt ) {
        const auto [ nxtIt, curV, curSz ] ( getNext( curIt, endIt ) );
        curIt = nxtIt;
        res << curSz << curV;
    }

    return res.str();
}

std::string decompress ( const std::string& p_in ) {
    std::stringstream l_in(p_in), l_res;
    char              curV;
    std::size_t       curSz;

    l_in >> std::noskipws;
    while ( l_in >> curSz >> curV ) { l_res << std::string(curSz, curV); }
    return l_res.str();
}

int main()
{
    std::string test1       {"Heeellllooooo wooooooooooooooooorld!!!"};
    std::string compressed  { compress  (test1)      };
    std::string decompressed{ decompress(compressed) };

    std::cout << "Input        : " << test1        << "\n";
    std::cout << "Compressed   : " << compressed   << "\n";
    std::cout << "Decompressed : " << decompressed << "\n";

    return EXIT_SUCCESS;
}