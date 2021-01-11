/************************************************************
 *           NON-MEMBER STD::SIZE(), STD::EMPTY()           *
 *                      AND STD::DATA()                     *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++11 introduced non-members std::begin() and std::end().
 * C++17 enforces this approach by added three new non-members :
 *      - std::size ()
 *      - std::empty()
 *      - std::data ()
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/iterator/size
 * https://en.cppreference.com/w/cpp/iterator/empty
 * https://en.cppreference.com/w/cpp/iterator/data
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

template < typename Container >
void printContainerInfos( const Container&   c,
                          const std::string& p_title = "" ) 
{
    if ( !std::empty(p_title) )
        std::cout << p_title << "\n";
    std::cout << "Type  : " << typeid(c).name() << "\n";
    std::cout << "Size  : " << std::size  (c)   << "\n";
    std::cout << "Empty : " << std::boolalpha 
                            << std::empty (c)   << "\n";
}

int main()
{
    std::vector<int>           myVec { 1, 2, 3, 5, 8, 13, 21 };
    std::map<std::string, int> myMap { {"Hello", 42} };

    printContainerInfos( myVec , "---On std::vector---");
    printContainerInfos( myMap , "---On std::map---"   );

    return EXIT_SUCCESS;
}

/*
---On std::vector---
Type  : St6vectorIiSaIiEE
Size  : 7
Empty : false
---On std::map---
Type  : St3mapINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEiSt4lessIS5_ESaISt4pairIKS5_iEEE
Size  : 1
Empty : false
*/