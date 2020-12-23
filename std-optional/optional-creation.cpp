/************************************************************
 *              STD::OPTIONAL : CONSTRUCTORS                *
 ************************************************************/

/*!
 * ------------------------------------
 * std::optional creation
 * ------------------------------------
 * 1. As empty
 * 2. From rvalue
 * 3. Copy constructor
 * 4. With std::in_place
 * 5. With a value using deduction guides
 * 6. Using std::make_optional
 */

#include <iostream>
#include <string>
#include <optional>

/*!
 * More infos on https://en.cppreference.com/w/cpp/utility/optional
 */

int main()
{
    /*!
     * ------------------------------------
     * Initialize as empty
     * ------------------------------------
     * constexpr optional() noexcept;
     * constexpr optional( std::nullopt_t ) noexcept;
     */
    std::optional<int> o1;

    /*!
     * ------------------------------------
     * Init from rvalue
     * ------------------------------------
     */
    std::optional<int> o2{1};

    /*!
     * ------------------------------------
     * Copy constructor
     * ------------------------------------
     * constexpr optional( const optional& other );
     */
    std::optional<int> o3{o2};

    /*!
     * ------------------------------------
     * Initialized with std::in_place
     * ------------------------------------
     */
    // calls std::string( initializer_list<CharT> ) constructor
    std::optional<std::string> o4(std::in_place, {'h', 'e', 'l', 'l', 'o', '!' } );

    if ( o4 ) { std::cout << *o4 << "\n"; }

    // calls std::string( size_type count, CharT ch ) constructor
    std::optional<std::string> o5(std::in_place, 6, '*');
    if ( o5 ) { std::cout << *o5 << "\n"; }

    /*!
     * ------------------------------------
     * Initialized with a value using 
     * deduction guides
     * ------------------------------------
     */
    std::optional o6( std::string{"init with deduction guides"} );
    if ( o6 ) { std::cout << *o6 << "\n"; }

    /*!
     * ------------------------------------
     * Initialized using make_optional
     * ------------------------------------
     */
    auto o7 = std::make_optional( "init with std::make_optional" );
    if ( o7 ) { std::cout << *o7 << "\n"; }

    return EXIT_SUCCESS;
}