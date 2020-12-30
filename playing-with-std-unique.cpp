/************************************************************
 *                PLAYING WITH STD::UNIQUE                  *
 ************************************************************/

/*!
 * @brief std::unique has been introduced in C++17.
 *        It allows to eliminate all except the first element
 *        from every consecutive group of equivalent elements
 *        in a given range.
 * 
 * More informations here :
 *      https://en.cppreference.com/w/cpp/algorithm/unique
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

/*!
 * @note Here we are using it to define a function
 *       that will remove every consecutive duplicates
 *       of a given character in a std::string
 */
std::string::iterator remove_multiple_char(
    std::string::iterator it_begin, 
    std::string::iterator it_end, 
    char                  p_remove = ' ')
{
    return std::unique( it_begin, it_end, [p_remove](const auto& c1, const auto& c2) {
        return ( c1 == p_remove && c2 == p_remove );
    });
}

/*!
 * @note Here is a templated version of the first
 *       function to work on every range compatible
 *       container.
 */
template <typename It, typename Val>
It remove_multiple_char(It it_begin, It it_end, Val p_val)
{
    return std::unique(it_begin, it_end, [p_val](const auto &c1, const auto &c2) {
        return (c1 == p_val && c2 == p_val);
    });
}

/*!
 * @note Here is a templated version that will
 *       remove every consecutive duplicates
 *       from a given range compatible container.
 */ 
template < typename It >
It remove_multiple_elms( It it_begin, It it_end )
{
    return std::unique(it_begin, it_end);
}

int main()
{
    std::string      test1{"Hello    beautiful       World!"};
    std::string      test2{"Heeellllooooo wooooooooooooooooorld!!!"};
    std::vector<int> test3 = {1, 1, 2, 2, 2, 3, 8, 8, 8, 8, 9, 11, 11};
    char             char_to_remove{' '};
    int              int_to_remove {8};

    std::cout << "-----test1-----\n" << test1 << "\n";
    test1.erase( remove_multiple_char( std::begin(test1), std::end(test1), ' '), 
                 std::end(test1) );
    std::cout << "Removed char " <<  char_to_remove << ": " << test1 << "\n";

    std::cout << "-----test2-----\n" << test2 << "\n";
    test2.erase(remove_multiple_elms(std::begin(test2), std::end(test2) ),
                std::end(test2));
    std::cout << "Removed duplicates : " << test2 << "\n";

    std::cout << "-----test3-----\n";
    std::copy( std::begin(test3), std::end(test3), 
               std::ostream_iterator<int>{ std::cout, ", "} );
    std::cout << "\n";
    test3.erase(remove_multiple_char(std::begin(test3), std::end(test3), int_to_remove),
                std::end(test3));
    std::cout << "Removed duplicate " << int_to_remove << ": ";
    std::copy(std::begin(test3), std::end(test3),
              std::ostream_iterator<int>{std::cout, ", "});
    std::cout << "\n";
    
    return EXIT_SUCCESS;
}