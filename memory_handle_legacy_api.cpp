/************************************************************
 *              MEMORY HANDLING OF LEGACY APIS              *
 *                   USING SMART POINTERS                   *
 ************************************************************/

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

/*!
 * @brief LegacyAPI
 *        Simulates a third-party legacy API which :
 *          - Hides constructors/destructor implementations
 *          - Only provides static methods for object creation/destruction
 *            based on raw pointers.
 *          - Cannot be constructed/deleted with new or delete and therefore
 *            not "smart_ptr" compatible.
 */
namespace LegacyAPI {

    class APIClass {
        // Methods using raw pointers (C API for example)
        public:
            static APIClass* createAPIClass( const std::string& p_name ) {
                return new APIClass(p_name);
            }
            static void deleteAPIClass( APIClass* p_inst ) { delete p_inst; }

            void doJob(void) const {
                std::cout << "APIClass object doing its job...";

                std::this_thread::sleep_for( std::chrono::milliseconds(2000) );

                std::cout << "Done!\n";
            }

        // Hidden
        private:
            APIClass(const std::string &p_name) : m_name(p_name) {
                std::cout << "APIClass(\"" << m_name << "\")\n";
            }
            ~APIClass() { std::cout << "~APIClass(\"" << m_name << "\")\n"; }

            std::string m_name;
    };

}

using namespace LegacyAPI;

/*!
 * @brief In order to make our ressources managable
 *        with smart_ptr, we need to provide the smart_ptr
 *        with custom deleters (because the default deleter
 *        would do it wrong - APIClass cannot be allocated or
 *        deleted using new or delete).
 */
static std::unique_ptr< APIClass, void (*)(APIClass*) > 
make_unique_APIClass( const std::string& p_name ) {
    return { APIClass::createAPIClass(p_name), APIClass::deleteAPIClass };
}

static std::shared_ptr<APIClass>
make_shared_APIClass( const std::string& p_name ) {
    return { APIClass::createAPIClass(p_name), APIClass::deleteAPIClass };
}


int main()
{
    {
        std::cout << "----- Basic usage with raw pointers -----\n";
        APIClass* myClass { APIClass::createAPIClass("RAW POINTER") };

        myClass->doJob();

        // Of course, it would be easy to leak if we do not
        // call the static destruction method before the
        // scope ends.
        APIClass::deleteAPIClass(myClass);
    }

    {
        std::cout << "----- Improved usage with smart pointers -----\n";
        auto myClass = make_unique_APIClass("UNIQUE POINTER");

        myClass->doJob();

        auto myClass2 = make_shared_APIClass("SHARED POINTER");

        myClass2->doJob();

        // No need to manage its destruction :)
    }

    return EXIT_SUCCESS;
}