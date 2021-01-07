/************************************************************
 *           STD::EMPLACE_BACK() THE NEW RECEIPE            *
 ************************************************************/

/*!
 * @brief 
 * 
 * The std::emplace methods were introduced in C++11 in order
 * to be able to create objects in place, but usually did not
 * return anything at all, especially for std::vector.
 * 
 * template< class... Args >
 * void emplace_back( Args&&... args );
 * 
 * Since C++17 however these methods return a reference to the
 * inserted object.
 * 
 * template< class... Args >
 * reference emplace_back( Args&&... args );
 * 
 * This will help alot for code simplification in situations
 * you need to access the inserted object right away as we 
 * see in the below example.
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/container/vector/emplace_back
 */

/*!
 * @note In C++20, the std::emplace_back method will
 *       return a constexpr reference.
 */

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> myVec { "Hello", "," };

    // C++11 version
    myVec.emplace_back("beautiful");
    myVec.back().append(" beautiful");

    // C++17 version
    myVec.emplace_back("world").append("!");

    for ( const auto& elm : myVec ) std::cout << elm << " ";
    std::cout << "\n";

    return EXIT_SUCCESS;
}

/*
 Hello , beautiful beautiful world!
 */