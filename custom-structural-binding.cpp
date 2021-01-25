/************************************************************
 *           STRUCTURAL BINDING FOR CUSTOM CLASS            *
 ************************************************************/

/*!
 * @brief Providing structual binding for custom class
 *        requires to provide the following specialisations :
 *          - get<I> : Returns the value for each element.
 * (https://en.cppreference.com/w/cpp/utility/tuple/get)
 *          - std::tuple_size : The number of available fields.
 * (https://en.cppreference.com/w/cpp/utility/tuple/tuple_size)
 *          - std::tuple_element : The type of each field.
 * (https://en.cppreference.com/w/cpp/utility/tuple/tuple_element)
 * 
 * See https://en.cppreference.com/w/cpp/language/structured_binding
 * for more details.
 */

#include <iostream>
#include <string>
#include <tuple>

class User {
    public:
        User( const std::string& p_name = "",
              uint32_t           p_age  = 0,
              uint32_t           p_size = 0 ):
              m_name(p_name),
              m_age (p_age ),
              m_size(p_size) {}
        
        std::string getName(void) const { return m_name; }
        uint32_t    getAge (void) const { return m_age;  }
        uint32_t    getSize(void) const { return m_size; }

    private:
        std::string m_name;
        uint32_t    m_age ;
        uint32_t    m_size;
};

// Returns the value of the specified element
template < size_t I >
auto get( const User& p_user ) {
    if      constexpr ( I == 0 ) return p_user.getName();
    else if constexpr ( I == 1 ) return p_user.getAge ();
    else if constexpr ( I == 2 ) return p_user.getSize();
}

namespace std {
    // The number of available fields
    template <> struct tuple_size<User> : integral_constant<size_t, 3> { };

    // The type for each elements
    template <> struct tuple_element<0, User> { using type = std::string; };
    template <> struct tuple_element<1, User> { using type = uint32_t;    };
    template <> struct tuple_element<2, User> { using type = uint32_t;    };
}

int main()
{
    User bob("Bob", 32, 180);

    auto [name, age, height] = bob;

    std::cout << name << ", " << age << " years old, " << height << "cm.\n";

    return EXIT_SUCCESS;
}

/*
Bob, 32 years old, 180cm.
*/