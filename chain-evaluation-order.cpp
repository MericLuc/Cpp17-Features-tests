/*************************************************************
 *                  CHAIN EVALUATION ORDER                   *
 ************************************************************/

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>

/*!
 * @brief : Just a Class with methods that can be chained.
 */
class AClass
{
public:
    AClass& addInt  (int p_val) { 
        std::cout << "Adding int " << p_val << "\n";
        m_val += p_val;

        return *this;
    }
    AClass& addFloat(float p_val) { 
        std::cout << "Adding float " << p_val << "\n";
        m_val += p_val;

        return *this;
    }

private:
    double m_val{0.};
};

int computeAnInt(void) { 
    std::cout << "Computing an int...\n";

    return std::rand();
}

float computeAFloat(void) {
    static float X {100.f};

    std::cout << "Computing a float...\n";

    return static_cast<float> ( std::rand() ) / static_cast<float>(RAND_MAX/X);
}

int main()
{
    std::srand( std::time(nullptr) );

    AClass myClass;

    /*
     * --------------- Before C++17 -----------------
     *  The chaining already worked from left to right
     *  (So addInt is called before addFloat) but the order of
     *  evaluation of the inner arguments is not garanteed !
     * 
     *  The compiler may choose to perform both computation
     *  functions before actually calling addInt, which leads to
     *  the following :
     *      Computing an int...
     *      Computing a float...
     *      Adding int 2612
     *      Adding float 24.015
     */
    myClass.addInt( computeAnInt() ).addFloat( computeAFloat() );
    /*
     * --------------- Since C++17 -----------------
     *  The order of evaluation for the inner expressions is
     *  also garanteed to be from left to right, leading to
     *  the way more logical output :
     *      Computing an int...
     *      Adding int 2612
     *      Computing a float...
     *      Adding float 24.015
     */

    return 0;
}