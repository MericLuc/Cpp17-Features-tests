/*************************************************************
 *          REMOVE VECTOR ELEMENT IN O(1) TIME              *
 ************************************************************/

/*!
 * As you might know ( if not, you might want to throw an eye here 
 * https://en.cppreference.com/w/cpp/container/vector/erase ), removing
 * an element from a std::vector is a O(N) time operation ( unless you remove
 * the last element ).
 * 
 * On large vectors, this operation can therefore be time-consumming.
 * 
 * So, if you do not mind about conserving the order of the elements
 * in the vector, here is a `fast_remove` method that performs the
 * removal in O(1) time.
 */

#include <iostream>
#include <vector>
#include <algorithm>

//  A version using the index of the element to remove
template< typename T>
void fast_remove( std::vector<T>& p_vec, std::size_t p_idx ) 
{
    if ( p_idx < p_vec.size() ) 
    {
        std::swap( p_vec[p_idx], p_vec.back() );
        p_vec.pop_back();
    }
}

// A version using an iterator to the element to remove
template< typename T>
void fast_remove( std::vector<T>& p_vec, typename std::vector<T>::iterator p_it )
{
    if ( p_it != p_vec.end() ) 
    {
        *p_it = std::move( p_vec.back() );
        p_vec.pop_back();
    }
}

int main()
{
    std::vector<int> myVec = { 5, 172, -3, 17, 11, 3985, -112, 6 };
    int p_idx{5};

    std::cout << "Initial vector : ";
    for (auto &&elm : myVec) { std::cout << elm << " "; }
    std::cout << std::endl;

    fast_remove( myVec, p_idx );

    // The order changed but the operation was done in O(1) time.
    std::cout << "After removing the " << p_idx << " element : "; 
    for ( auto&& elm : myVec ) { std::cout << elm << " "; }
    std::cout << std::endl;

    fast_remove( myVec, std::find( std::begin(myVec), std::end(myVec), -3) );

    std::cout << "After removing the element by iterator :";
    for (auto &&elm : myVec) { std::cout << elm << " "; }
    std::cout << std::endl;

    return 0;
}