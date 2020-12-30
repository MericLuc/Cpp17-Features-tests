/************************************************************
 *                 STD::ANY - BYE BYE VOID*                 *
 ************************************************************/

/*!
 * @brief Good to know 
 *        - Unlike std::variant and std::optional,
 *          std::any is not a template class.
 *        - By default it contains no value 
 *          ( any.has_value() == false )
 *        - When a different type is assigned,
 *          the active type is destroyed.
 *        - You can get the type using .type()
 *          which returns a std::type_info
 *        - You can access the value using 
 *          std::any_cast<T> (which can throw).
 * 
 * NB : Unlike the void* pattern, std::any is type-safe
 *      and you do not have to worry about life cycle nor
 *      bad casts.
 * 
 * More infos about std::any here
 * https://en.cppreference.com/w/cpp/utility/any
 */

/*!
 * @note When to use ?
 *       Here are some possible use cases for std::any :
 *       - file/message parsing 
 *       - binding with a scripting language
 *       - Interpreter for scripting language
 *       - Basically everywhere void* was applied...
 * 
 * NB : If you can limit the number of types to a reasonnable
 *      value, you might prefer using std::variant.
 */


#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <any>
#include <utility>

int main()
{
    std::cout << "\t-----      std::any Creation       -----\n";
    {
        {
            /*!
             * Default constructor
             * Creates an empty object
             */
            std::any myAny;
            std::cout << "Default constructed - has value ? " 
                    << std::boolalpha << myAny.has_value() << "\n";
        }

        {
            /*!
             * Initialisation with an object
             */
            std::any myAny( std::string("Hello world!") );
            std::cout << "Initialised with a " << myAny.type().name() 
                      << ": " << std::any_cast<std::string>(myAny) << "\n";
        }

        {
            /*!
             * Copy/Move constructor
             * Copies/Moves the content of other into a new instance.
             * If other is empty, then copied/moved object is empty too.
             */
            std::any a1, a2{8}, a3(a1), a4(a2);
            std::cout << "Copy/move constructors work as expected!\n";
        }

        {
            /*!
             * Initialised using std::in_place
             * Creates object in place so that no
             * temporary object is used.
             */
            std::any myAny( std::in_place_type<std::string>,
                            "Hello World!" );
            std::cout << "Initialised using std::in_place_type with " 
                      << myAny.type().name()
                      << ": " << std::any_cast<std::string>(myAny) << "\n";
        }

        {
            /*!
             * Creation using the std::make_any factory
             */
            auto myAny = std::make_any<std::string>("Hello world!");
            std::cout << "Initialised using std::make_any factory : "
                      << std::any_cast<std::string>(myAny) << "\n";
        }
    }

    std::cout << "\t----- std::any Changing the value  -----\n";
    {
        /*!
         * You basically have 2 options
         * 1 - use std::any::emplace
         * 2 - assign a new value
         * 
         * NB: You can also reset the value using std::any::reset
         *     https://en.cppreference.com/w/cpp/utility/any/reset
         */

        {
            std::any myAny{ std::in_place_type<std::string>, "Hello World!"};

            std::cout << "Changed the value from " 
                      << std::any_cast<std::string>(myAny) << " to ";

            myAny.emplace<int>(42);
            std::cout << std::any_cast<int>(myAny)
                      << " using std::any::emplace\n"; 
        }

        {
            std::any myAny{std::in_place_type<std::string>, "Hello World!"};

            std::cout << "Changed the value from " 
                      << std::any_cast<std::string>(myAny) << " to ";
            
            myAny = 42;

            std::cout << std::any_cast<int>(myAny)
                      << " using assignement\n";
        }
    }

    std::cout << "\t----- std::any Accessing the value -----\n";
    {
        /*!
         * You only have 1 option
         * 1 - use std::any_cast<T>()
         * 
         * It has 3 modes :
         * a - read access
         * b - read/write access using references
         * c - read/write access using pointers
         * 
         * More informations here
         * https://en.cppreference.com/w/cpp/utility/any/any_cast
         */

        {
            auto myAny = std::make_any<int>(42);

            // Any cast can throw std::bad_any_cast
            // if the required type is not the active one.
            try {
                std::cout << std::any_cast<std::string>(myAny) << "\n";
            }
            catch( const std::bad_any_cast& e ) {
                std::cout << "std::any_cast<T>() failed : " << e.what() << "\n";
            }
        }

        {
            // Read/Write using references
            auto a   = std::make_any<std::string>("Hello world!");
            auto &ra = std::any_cast<std::string&>(a);
            ra[11] = '?';

            std::cout << "read using const reference: "
                      << std::any_cast<const std::string &>(a) << '\n'; //< const reference

        }

        {
            // Read/Write using pointers
            auto a = std::make_any<int>(42);

            if ( int* ptr = std::any_cast<int>(&a) )
            {
                std::cout << "read a using pointers: " << *ptr << '\n';
            }
            else if ( std::string* ptr = std::any_cast<std::string>(&a) )
            {
                std::cout << "read a using pointers: " << *ptr << '\n';
            }
        }
    }

    return EXIT_SUCCESS;
}

/*
        -----      std::any Creation       -----
Default constructed - has value ? false
Initialised with a NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE: Hello world!
Copy/move constructors work as expected!
Initialised using std::in_place_type with NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE: Hello World!
Initialised using std::make_any factory : Hello world!
        ----- std::any Changing the value  -----
Changed the value from Hello World! to 42 using std::any::emplace
Changed the value from Hello World! to 42 using assignement
        ----- std::any Accessing the value -----
std::any_cast<T>() failed : bad any_cast
read using const reference: Hello world?
read a using pointers: 42
*/