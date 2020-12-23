/************************************************************
 *        STD::OPTIONAL : ACCESSING THE STORED VALUE        *
 ************************************************************/

/*!
 * ------------------------------------
 * std::optional access value
 * ------------------------------------
 * 1. implicit bool conversion
 * 2. has_value()
 * 3. value()
 * 4. operator*
 * 5. operator->
 * 6. value_or()
 */

#include <iostream>
#include <string>
#include <optional>
#include <map>

/*!
 * More infos on https://en.cppreference.com/w/cpp/utility/optional
 */

template < typename T >
std::optional<T> maybe_get(
    const std::map<std::string, T>& p_map,
    const std::string&              p_val)
{
    std::optional<T> l_ret; // empty

    if ( p_map.find(p_val) != p_map.end() )
        return p_map.at(p_val);

    return std::nullopt;
}

int main()
{
    /*!
     * ------------------------------------
     * Implicit bool conversion
     * ------------------------------------
     * constexpr explicit operator bool() const noexcept;
     */
    std::optional<int> o1, o2{1}; 
    std::cout << "o1 " << ( o1 ? "has" : "does not have" ) << " a value\n";
    std::cout << "o2 " << ( o2 ? "has" : "does not have" ) << " a value\n";

    /*!
     * ------------------------------------
     * Using has_value()
     * ------------------------------------
     * constexpr bool has_value() const noexcept;
     */
    std::cout << "o1 " << (o1.has_value() ? "has" : "does not have") << " a value\n";
    std::cout << "o2 " << (o2.has_value() ? "has" : "does not have") << " a value\n";

    /*!
     * ------------------------------------
     * Using value
     * ------------------------------------
     * constexpr T& value() &;
     * constexpr const T& value() const &;
     * 
     * Note : If *this contains a value, returns a reference to 
     *        the contained value.
     *        Otherwise, throws a std::bad_optional_access exception. 
     */
    try {
        [[maybe_unused]] int i = o1.value();
    } catch ( const std::bad_optional_access& e ) {
        std::cout << e.what() << "\n";
    }
    std::cout << "o2.value() = " << o2.value() << "\n";

    /*!
     * ------------------------------------
     * Using operator*
     * ------------------------------------
     * constexpr T& operator*() &;
     * constexpr const T& operator*() const&;
     * 
     * Note : This operator does not check whether 
     *        the optional contains a value !
     */
    std::cout << "*o2 = " << *o2 << "\n";

    /*!
     * ------------------------------------
     * Using operator->
     * ------------------------------------
     * constexpr T* operator->();
     * constexpr const T* operator->() const;
     * 
     * Note : This operator does not check whether 
     *        the optional contains a value !
     */
    std::optional o3( std::string("Hello world!") );
    std::cout << "o3->size() = " << o3->size() << "\n";

    /*!
     * ------------------------------------
     * Using value_or()
     * ------------------------------------
     * template< class U >
     * constexpr T value_or( U&& default_value ) &&;
     * 
     * Note : Returns the stored value if *this has one,
     * otherwise returns the provided default value.
     */
    std::map<std::string, std::string> myMap = 
    {
        {"Hello", "World!"},
        {"CWD" , "/home/foo/bar"}
    };

    std::cout << maybe_get<std::string>(myMap, "CWD" ).value_or("(None)") << "\n";
    std::cout << maybe_get<std::string>(myMap, "TEST").value_or("(None)") << "\n";

    return EXIT_SUCCESS;
}