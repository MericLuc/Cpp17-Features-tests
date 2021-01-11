/************************************************************
 *                      STD::CLAMP()                        *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 introduced alot of new mathematical functions
 * that were long waited (at least by me).
 * Among them is the std::clamp() function that clamps
 * an input value in a given range :
 *      - if      v < lo : l0
 *      - else if v > hi : hi
 *      - else    v
 * 
 * template< class T, class Compare >
 * constexpr const T& clamp( const T& v, 
 *                           const T& lo, 
 *                           const T& hi, 
 *                           Compare comp );
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/algorithm/clamp
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>

int main()
{
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<> d(-300, 300);
    std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
    for (int n = 0; n < 5; ++n)
    {
        int v = d(g);
        std::cout << std::setw( 4) << v
                  << std::setw(20) << std::clamp(v, INT8_MIN, INT8_MAX)
                  << std::setw(21) << std::clamp(v, 0, UINT8_MAX) << '\n';
    }

    return EXIT_SUCCESS;
}

/*
 raw   clamped to int8_t   clamped to uint8_t
  37                  37                   37
 136                 127                  136
 -91                 -91                    0
 250                 127                  250
-297                -128                    0
*/