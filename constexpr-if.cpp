/************************************************************
 *                    CONSTEXPR IF TEST                     *
 ************************************************************/

#include <vector>
#include <iostream>
#include <type_traits>

template <typename>
struct is_std_vector : std::false_type
{
};

template <typename T, typename A>
struct is_std_vector<std::vector<T, A>> : std::true_type
{
};

template< typename AType >
class MyClass
{
public:
    MyClass() = delete;
    MyClass(AType p_val) : m_val(p_val) {}

    template <typename AnotherType>
    AType add(AnotherType p_val) const 
    {
        /*!
         * Is evaluated at compile-time and
         * can save alot of CPU.
         */
        if constexpr ( std::is_same_v<AType, std::vector<AnotherType> >) 
        {
            AType l_cpy(m_val);
            for ( auto&& p_elm : l_cpy ) { p_elm += p_val; }
            return l_cpy;
        }
        else 
        { 
            return m_val + p_val; 
        }

        return m_val;
    } 

    template< typename BType >
    friend std::ostream& operator<<(std::ostream& os, const MyClass<BType>& myClass );

private : 
    AType m_val;
};

template <typename BType>
std::ostream &operator<<(std::ostream &os, const MyClass<BType> &myClass)
{
    if ( is_std_vector<BType>::value )
    {
        for (auto &l_elm : myClass.m_val)
        {
            os << l_elm << " ";
        }
        os << "\n";
    }
    else { os << myClass.m_val; }

    return os;
}

int main()
{
    /*!
     * When constructed from a std::vector,
     * the "add()" operation is applied on
     * every element of the vector.
     */
    {
        std::vector<int> myVec = {1, 2, 5, 10};
        MyClass<std::vector<int>> myClass( myVec );

        myVec = myClass.add(-1);

        for ( auto& it : myVec ) { std::cout << it << " "; }
        std::cout << "\n";
    }

    /*!
     * Otherwise, it is only applied to 
     * the m_val.
     */
    {
        std::string myStr("Hello");
        MyClass<std::string> myClass( myStr );
        myStr = myClass.add(" World!");

        std::cout << myStr << "\n";
    }

    return EXIT_SUCCESS;
}
