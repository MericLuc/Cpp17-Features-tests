/************************************************************
 *                   STD::MAP::try_emplace                  *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 added some usefull features for std::map, and
 * std::map::try_emplace is one of them - and consists of an
 * improvement of std::map::emplace().
 * 
 * - try_emplace() does not move from rvalue arguments if the insertion 
 * does not happen. This is useful when manipulating maps whose values 
 * are move-only types, such as std::unique_ptr or with std::move.
 * 
 * - try_emplace() also treats the key and the args to the mapped_type
 * separately, so it does not require the arguments to construct a 
 * value_type ( i.e. a std::pair ).
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/container/map/try_emplace
 */

#include <iostream>
#include <string>
#include <map>
#include <memory>

template < typename Key, typename Val >
void printMap( const std::map<Key, Val>& p_map ) {
    for ( const auto &[key, val] : p_map )
        std::cout << key << "->" << val << "\n";
    std::cout << "\n";
}

int main()
{
    std::map< std::string, std::string  > m1;
    std::map< int, std::unique_ptr<int> > m2;

    m1["Hello"] = "Bonjour";
    m2[42]      = std::make_unique<int>(42);

    // C++11 VS C++17
    {
        // C++11 way to emplace 
        // double look-up for "beautiful" key...
        if ( m1.find("beautiful") == std::end(m1) )
        {
            m1["beautiful"] = "magnifique";
        }

        // C++17 way
        m1.try_emplace("world!", "monde!");
        // Will not emplace as the key already exists
        m1.try_emplace("Hello", "Guten tag");

        printMap(m1);
    }

    // Now suppose you want to insert a move-only value
    // 1 - using std::move
    {
        std::string myMvStr1 {"Buenas dias"};

        // What happens in C++11

        // myMvStr1 value is not inserted because the key "Hello" 
        // already exists but it has been moved so it is not in 
        // myMvStr1 either !
        std::cout << "-- C++11 emplace with std::move(" 
                  << myMvStr1 << ") --\n";
        
        m1.emplace( std::make_pair("Hello", std::move(myMvStr1)) );

        std::cout << "MyMvStr1 = "   << myMvStr1    << "\n";
        std::cout << "m1[Hello] -> " << m1["Hello"] << "\n\n";

        // What happens in C++17
        std::string myMvStr2{"Buenas dias"};
        std::cout << "-- C++17 try_emplace with std::move("
                  << myMvStr2 << ") --\n";
        m1.try_emplace( "Bonjour", std::move(myMvStr2) );

        // myMvStr2 is still not inserted (because the key already
        // exists in m1) BUT it has not been moved and is still
        // accessible !
        std::cout << "MyMvStr2 = " << myMvStr2 << "\n";
        std::cout << "m1[Hello] -> " << m1["Hello"] << "\n\n";
    }

    // 2 - A std::unique_ptr (for example)
    {
        std::unique_ptr<int> myPtr1 = std::make_unique<int>(99);
        std::unique_ptr<int> myPtr2 = std::make_unique<int>(99);

        // What happens in C++11
        m2.emplace( std::make_pair(42, std::move(myPtr1)) );

        std::cout << "-- C++11 emplace with std::unique_ptr<int>(99) --\n";
        std::cout << "myPtr = "   << myPtr1 .get() << "\n";
        std::cout << "m2[42] -> " << *m2[42].get() << "\n\n";

        // What happens in C++17
        m2.try_emplace( 42, std::move(myPtr2) );

        std::cout << "-- C++17 try_emplace with std::unique_ptr<int>(99) --\n";
        std::cout << "myPtr = "   << *myPtr2.get() << "\n";
        std::cout << "m2[42] -> " << *m2[42].get() << "\n\n";

        // Once again, myPtr1 and myPtr2 are not inserted
        // because the key already exists in m2, but
        // with std::map::try_emplace, myPtr2 is not moved
        // and therefore not lost :)
    }

    return EXIT_SUCCESS;
}

/*
 Hello->Bonjour
 beautiful->magnifique
 world!->monde!
 
 -- C++11 emplace with std::move(Buenas dias) --
 MyMvStr1 = 
 m1[Hello] -> Bonjour
 
 -- C++17 try_emplace with std::move(Buenas dias) --
 MyMvStr2 = Buenas dias
 m1[Hello] -> Bonjour
 
 -- C++11 emplace with std::unique_ptr<int>(99) --
 myPtr = 0
 m2[42] -> 42
 
 -- C++17 try_emplace with std::unique_ptr<int>(99) --
 myPtr = 99
 m2[42] -> 42
*/