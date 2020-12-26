/************************************************************
 *                  STD::VARIANT HELPERS                    *
 ************************************************************/

#include <iostream>
#include <string>
#include <variant>
#include <cassert>
#include <vector>

/*!
 * @brief std::variant helpers
 *
 * This program highlights some helper
 * functions that might be usefull when working
 * with std::variant.
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
        /* 
        std::in_place_index
           In place construction specifying the
           index of the type to change in the
           std::variant.

        See https://en.cppreference.com/w/cpp/utility/in_place
        */

        std::variant< std::vector<int>, std::string, int > myVariant {
            std::in_place_index<0>, // Specify we will construct a std::vector<int>
            { 1, 2, 3, 5, 8, 13 }
        };

        std::cout << "Variant construction using std::in_place_index\n";
    }

    {
        /*  
        std::in_place_type
            In place construction specifying the
            type you want to change in the
            std::variant.
        
        See https://en.cppreference.com/w/cpp/utility/in_place
        */

        std::variant< std::vector<int>, std::string, int > myVariant {
            std::in_place_type<std::string>, // Specify we will construct a std::string
            {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!' , '\n'}};

        std::cout << "Variant construction using std::in_place_type\n";
    }

    {
        /*
        std::emplace
            Modifier of std::variant object.
            Creates a new value in-place in an existing
            std::variant object.
        
        See https://en.cppreference.com/w/cpp/utility/variant/emplace

        Note : Can throw any exception that would be thrown during
               the initialization of the contained value.
        */
        
        std::variant<std::string> myVariant; 
        // Default-constructed with std::string default constructor
        // i.e. empty string

        std::cout << "Variant modified using std::emplace - ";

        myVariant.emplace<0>("Hello ");
        std::cout << std::get<std::string>(myVariant);

        myVariant.emplace<std::string>("World!\n");
        std::cout << std::get<std::string>(myVariant);
    }

    {
        /*           
        std::get
            Returns the value of a std::variant providing
            either the type or the index.

            Note : It throws std::bad_variant_acess on error
        
        See https://en.cppreference.com/w/cpp/utility/variant/get
        */

        std::variant<int, std::string> myVariant{"Hello"};

        // Note : Returns a REFERENCE so can be used as a
        //        modifier function.
        std::get<std::string>(myVariant) += " World!\n";

        std::cout << "Used std::get<std::string> as a std::variant modifier ! "
                  << "See - " << std::get<std::string>(myVariant);

        try
        {
            auto &ref = std::get<int>(myVariant);
       }
       catch ( const std::bad_variant_access& e )
       {
           std::cout << e.what() << ": myVariant contains std::string, not int\n";
       }

    }

    {
        /*           
        std::get_if     
                Returns the value stored in the pointed-to variant
                or nullptr on error.  

        See https://en.cppreference.com/w/cpp/utility/variant/get_if
        */

       std::variant<int, std::string> myVariant { "Hello world!\n"};

       if ( auto l_val = std::get_if<int>(&myVariant); 
                 l_val != nullptr /* Silly but reminder of the if init feature */ )
       {
            std::cout << "std::get_if<int> got me the value " << *l_val << "\n";
       }
       else
       {
           std::cout << "std::get_if<int> failed to get a value of type std::string\n";
       }
        
    }

    {
        /*     
        std::holds_alternative 
            Checks if the std::variant holds
            the required alternative T.

        Note : The call is ill-formed if T does not
                appear exactly once in std::variant types.
        */

       std::variant<int, std::string> myVariant = "Hello world\n";

       std::cout << std::boolalpha
                 << "variant holds int? "
                 << std::holds_alternative<int>(myVariant) << '\n'
                 << "variant holds string? "
                 << std::holds_alternative<std::string>(myVariant) << '\n';
    }

    {
        /* 
        std::monostate
           If you want to default-construct a std::variant but 
           your first type is not default constructible, 
           you can use the std::monostate type as a default type 
           with no value.

           The behavior is similar to std::optional.

           Note : Possible "workaround" 
               - Shuffle the types to put a default-constructible 
                 one first.
               - Not default-construct your std::variant.
        */

        // Not default constructible so this is not possible :
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

    return EXIT_SUCCESS;
}