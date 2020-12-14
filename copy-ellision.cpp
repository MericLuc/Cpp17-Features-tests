/************************************************************
 *                 GARANTEED COPY ELLISION                  *
 ************************************************************/

#include <iostream>
#include <ostream>

/*!
 * @brief : This class cannot be copied or assigned due to
 *          corresponding constructors deleted.
 */
class NonCopiableClass
{
    public:
        NonCopiableClass(uint32_t p_id = 0) : m_id(p_id) {}
        ~NonCopiableClass() {}

        NonCopiableClass(const NonCopiableClass& ) = delete;
        NonCopiableClass(NonCopiableClass&&) = delete;

        friend std::ostream& operator<<(std::ostream& o, const NonCopiableClass& nc) {
            o << nc.m_id << " - ok\n";
            return o;
        }

    private:
        uint32_t m_id{0};
};

/*!
 * @brief Returns a value of type NonCopiableClass.
 *        In C++11 and C++14, this would not work
 *        as NonCopiableClass lacks copy and move
 *        constructors.
 */
NonCopiableClass testCopyEllision(uint32_t p_val) 
{
    // In C++17, the compiler will ellide copy even on 
    // named object because it is used to initialize myClass.
     return NonCopiableClass(p_val);
}

int main()
{
    NonCopiableClass myClass = testCopyEllision(10);

    std::cout << myClass << std::endl;

    return 0;
}