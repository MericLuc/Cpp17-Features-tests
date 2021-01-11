/************************************************************
 *                       STD::LCM()                         *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 introduced alot of new mathematical functions
 * that were long waited (at least by me).
 * Among them is the std::lcm() function that computes
 * the least common multiple of two integers.
 * 
 * template< class M, class N>
 * constexpr std::common_type_t<M, N> lcm(M m, N n);
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/numeric/lcm
 */

#include <iostream>
#include <numeric>

int main()
{
    // https://en.cppreference.com/w/cpp/language/constexpr
    // Constant expression evaluated at compile-time
    constexpr int m { 2 * 2 * 3 * 3 * 7 * 7  * 11 }; 
    constexpr int n { 2 * 3 * 3 * 3 * 7 * 11 * 13 };
    constexpr int lcm { std::lcm( m, n ) };

    // https://en.cppreference.com/w/cpp/language/static_assert
    // Compile-time assertion checking.
    static_assert ( lcm == 2 * 2 * 3 * 3 * 3 * 7 * 7 * 11 * 13,
                    "std::lcm() did not behave as expected ?!" );

    std::cout << "The least common multiple of "
              << m << " and " << n << " is " 
              << lcm
              << "\n";

    return EXIT_SUCCESS;
}

/*
 The least common multiple of 19404 and 54054 is 756756.
*/