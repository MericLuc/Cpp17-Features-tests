/************************************************************
 *                 STD::OPTIONAL : EXAMPLE(s)               *
 ************************************************************/

#include <iostream>
#include <string>
#include <optional>

/*!
 * Exceptions are converted into optional
 * without value.
 */
std::optional<int> ParseInt(const char* p_arg) {
    try {
        return std::stoi( std::string(p_arg) );
    }
    catch (...) {
        std::cerr << "Cannot convert '" << p_arg << "' to int!\n";
    }

    return {};
}

int main(int argc, const char* argv[])
{
    if ( argc >= 3 ) {
        // Garanteed copy ellisions
        auto o1 = ParseInt(argv[1]);
        auto o2 = ParseInt(argv[2]);

        if ( o1 && o2 )
            std::cout << *o1 << " + " << *o2 << " = " << *o1 + *o2 << "\n";
        return EXIT_SUCCESS;
    }

    std::cout << "You did not enter two valid integers\n";
    return -1;
}