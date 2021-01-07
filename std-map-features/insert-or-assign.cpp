/************************************************************
 *                STD::MAP::insert_or_assign                *
 ************************************************************/

/*!
 * @brief 
 * 
 * C++17 added some usefull features for std::map, and
 * std::map::insert_or_assign is one of them.
 * 
 * - insert_or_assign() inserts a new object in the map or
 * assigns the new value.
 * 
 * - unlike operator[], insert_or_assign() works with non
 * default-constructible types. It also returns more informations.
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/container/map/insert_or_assign
 */

#include <iostream>
#include <string>
#include <map>

template < typename Key, typename Val >
void printMap( const std::map<Key, Val>& p_map ) {
    for ( const auto &[key, val] : p_map )
        std::cout << key << "->" << val << "\n";
    std::cout << "\n";
}

/*!
 * @brief MyClass
 *        Non default constructible class.
 */
class MyClass 
{
public:
    MyClass( const std::string& p_name ) : m_name(p_name) {}
    std::string getName(void) const { return m_name; }

    // To be usable in a std::map
    friend bool operator<( const MyClass& c1, const MyClass& c2 ) {
        return c1.m_name < c2.m_name;
    }

private:
    std::string m_name;
};

int main()
{
    {
        std::map<std::string, std::string> myMap;
        
        myMap.insert_or_assign("Hello", "bonjour");
        myMap.insert_or_assign("beautiful", "magnifique");

        auto [it1, insert1] = myMap.insert_or_assign("world", "monde");

        std::cout << it1->first  << " - " 
                  << it1->second << " : " 
                  << ( insert1 ? "inserted" : "replaced" ) << "\n";

        auto [it2, insert2] = myMap.insert_or_assign("world", "MONDE");

        std::cout << it2->first  << " - "
                  << it2->second << " : " 
                  << ( insert2 ? "inserted" : "replaced" ) << "\n";

        // Note that iterators or reference are not invalidated !
        std::cout << "\n";
        printMap(myMap);
    }

    {
        std::map<std::string, MyClass> myMap;

        // Since MyClass is not default constructible
        // this is illegal to write
        // myMap["Class1"] = MyClass("Class1");

        auto [it1, insert1] = myMap.insert_or_assign( "Class1", MyClass("Class1") );
        std::cout << it1->first << " - "
                  << it1->second.getName() << " : " 
                  << ( insert1 ? "inserted" : "replaced" ) << "\n";

        auto [it2, insert2] = myMap.insert_or_assign( "Class1", MyClass("CLASS1") );
        std::cout << it2->first << " - "
                  << it2->second.getName() << " : " 
                  << ( insert2 ? "inserted" : "replaced" ) << "\n";
    }


    return EXIT_SUCCESS;
}

/*
    world - monde : inserted
    world - MONDE : replaced

    Hello->bonjour
    beautiful->magnifique
    world->MONDE

    Class1 - Class1 : inserted
    Class1 - CLASS1 : replaced
*/