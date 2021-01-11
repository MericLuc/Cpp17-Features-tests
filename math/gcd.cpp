/************************************************************
 *                       STD::GCD()                         *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 introduced alot of new mathematical functions
 * that were long waited (at least by me).
 * Among them is the std::gcd() function that computes
 * the greatest common divisor of two integers.
 * 
 * template< class M, class N >
 * constexpr std::common_type_t<M, N> gcd(M m, N n);
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/numeric/gcd
 */

#include <iostream>
#include <numeric>

int main()
{
    // https://en.cppreference.com/w/cpp/language/constexpr
    // Constant expression evaluated at compile-time
    constexpr int m { 2 * 2 * 3 * 3 * 7 * 7  * 11 }; 
    constexpr int n { 2 * 3 * 3 * 3 * 7 * 11 * 13 };

    std::cout << "The greatest common divisor of "
              << m << " and " << n << " is " 
              << std::gcd( m, n )
              << "\n";

    return EXIT_SUCCESS;
}

/*
 The greatest common divisor of 19404 and 54054 is 1386.
*/