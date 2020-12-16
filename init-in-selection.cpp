/*************************************************************
 *       LIMIT VARIABLES SCOPE TO IF/ELSE STATEMENTS         *
 ************************************************************/

/*!
 * C++17 allows for Init statements in selection statements
 * (such as IF/ELSE and SWITCH).
 * 
 * It prevents the variables you only need in your
 * if/else statements to `leak` outside of the if/else scope.
 * 
 * Below is an example of this feature :)
 */

/*!
 * Note : To accomplish the same goal ( i.e. keep the scope 
 * of your variables as small as possible ) before C++17, you
 * would have to use extra braces around the corresponding code
 * which is way less readable.
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> myVec = { 5, 172, -3, 17, 11, 3985, -112, 6 };

    if ( auto it = std::find(std::begin(myVec), std::end(myVec), -3); it != std::end(myVec) )
    {
        std::cout << *it << " was found at idx " << std::distance( std::begin(myVec), it) << "\n";
        // Do what you want with it
        // ...
    }
    else
    {
        std::cout << "Could not find the required element in myVec\n";
    }
    
    // it did not `leak` here

        return 0;
}