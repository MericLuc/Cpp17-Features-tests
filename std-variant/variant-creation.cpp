/************************************************************
 *                  STD::VARIANT CREATION                   *
 ************************************************************/

#include <iostream>
#include <string>
#include <variant>
#include <cassert>
#include <vector>

/*!
 * @brief std::variant creation
 *
 * This program shows the ways of creating
 * std::variant.
 * 
 * You can find them here
 * https://en.cppreference.com/w/cpp/utility/variant/variant
 */

/*!
 * @note When to use std::variant ?
 *
 * Well, basically everywhere you need alternative
 * types...
 *      - Polymorphism without vtables
 *      - Parsers, cmd lines...
 *      - Finite state machines
 *      - Everywhere you could benefit from having
 *        a small number of possible alternative types.
 *      - ...
 */

int main()
{
    {
        // By default, a variant object is initalised with the 
        // first type.
        // Note : In that case, the first type must be default-constructible !
        std::variant<int, std::string> myVariant;

        assert(std::holds_alternative<int>(myVariant) &&
               myVariant.index() == 0 &&
               std::get<int>(myVariant) == 0 );
        
        std::cout << "Variant default constructed with int = " 
                  << std::get<int>(myVariant) << "\n";

    }

    {
        // If you still want to default-construct
        // a std::variant but your first type is not default
        // constructible, you can use the std::monostate
        // type as a default type with no value

        // Not default constructible
        // so this is not possible :
        // std::variant<NotDefConst, int> myVariant;
        class NotDefConst
        {
            public:
                NotDefConst() = delete;
                NotDefConst( int p_val = 42 ) : m_val(p_val) {}

            private:
                int m_val;
        };

        std::variant<std::monostate, NotDefConst, std::string> myVariant;

        std::cout << "Variant default constructed using std::monostate\n";
    }

    {
        // Initialize second alternative with float 42.f
        std::variant<int, float, std::string> myVariant { 42.f };

        assert( std::holds_alternative<float>(myVariant) &&
                myVariant.index() == 1 &&
                std::get<float>(myVariant) == 42.f );
    }

    {
        // You can resolve any ambuiguity by using
        // std::in_place_index or std::in_place_type
        std::variant<long, float> myVariant { std::in_place_index<1>, 42.0 };

        std::cout << "Variant constructed with std::in_place_index (float = "
                  << std::get<float>(myVariant) << ")\n";
    }

    {
        // You can resolve any ambuiguity by using
        // std::in_place_index or std::in_place_type
        std::variant<long, float> myVariant{ std::in_place_type<long>, 42.0 };

        std::cout << "Variant constructed with std::in_place_type (long = "
                  << std::get<long>(myVariant) << ")\n";
    }

    {
        // std::in_place is also very handy for more complex types
        std::variant<std::vector<int>, std::string> myVariant {
            std::in_place_index<0>,
            { 1, 2, 3, 5, 8, 13 }
        };

        std::cout << "Variant with complex type constructed with "
                     "std::in_place_index (" 
                  << std::get<std::vector<int> >(myVariant).size() 
                  << " elements)\n";
    }

    {
        // std::variant can be copy-initialised from
        // other std::variant
        std::variant<int, std::string> myVariant { "'Hello world!'\n" };
        auto copyVariant { myVariant };

        std::cout << "Variant copy-initialised from other "
                     "std::variant with value "
                  << std::get<std::string>(copyVariant);
    }

    return EXIT_SUCCESS;
}