/************************************************************
 *        STD::OPTIONAL : SAFELY SIGNALIZING FAILURE        *
 ************************************************************/
/*!
 * Before C++17, if you wanted a function that
 * could possibly fail to return/compute a value
 * without it being an error, you had several options
 *      - You could use a success indicating value
 *        as return or output param
 * Ex / bool get_string(std::string&);
 *      - You could return a pointer (or smart ptr)
 *        that would be nullptr in case of failure.
 * Ex / std::string* get_string();
 *      - Throw an exception and deal with it
 */

#include <iostream>
#include <string>
#include <optional>
#include <map>

/*!
 * C++17 solution
 */
template <typename T>
std::optional<T> maybe_get(
    const std::map<std::string, T>& p_map,
    const std::string&              p_val)
{
    if (p_map.find(p_val) != p_map.end())
        return p_map.at(p_val);

    return std::nullopt;
}

int main()
{
    std::map<std::string, std::string> myMap =
    {
            {"Hello", "World!"},
            {"CWD", "/home/foo/bar"}
    };

    std::cout << maybe_get<std::string>(myMap, "CWD" ).value_or("(None)") << "\n";
    std::cout << maybe_get<std::string>(myMap, "TEST").value_or("(None)") << "\n";

    return EXIT_SUCCESS;
}