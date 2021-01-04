/************************************************************
 *                       REGEX BASICS                       *
 ************************************************************/

/*!
 * @brief C++11 introduced the <regex> header in the standard
 *        library, that allows you to perform multiple
 *        operations on string using regular expressions.
 * 
 *      - MATCH a whole input against a regexe.
 *        See https://en.cppreference.com/w/cpp/regex/regex_match
 * 
 *      - SEARCH for patterns in input that match a regexe.
 *        See https://en.cppreference.com/w/cpp/regex/regex_search
 * 
 *      - TOKENIZE a string according to a separator specified
 *        as a regexe.
 *        See https://en.cppreference.com/w/cpp/regex/regex_token_iterator
 * 
 *      - REPLACE in the first or all subsequences that match 
 *        a regexe.
 *        See https://en.cppreference.com/w/cpp/regex/regex_replace
 * 
 * See https://en.cppreference.com/w/cpp/regex
 * for more details.
 * 
 * You may also want to take a look at Hana Dusíková on compile-time 
 * regular expressions at 'CppCon 2019 talk' :
 *   - https://www.youtube.com/watch?v=8dKWdJzPwHw
 * 
 * It gives a really interesting insight on the Compile Time Regular 
 * EXPRESSION (CTRE) library that gives a fast compile time on 
 * regular expressions.
 * More infos here : 
 *   - https://github.com/hanickadot/compile-time-regular-expressions
 *   - https://compile-time.re/
 */

#include <iostream>
#include <string>
#include <regex>

//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::string myStr { "Hello, beautiful world of regular expressions !" };
    std::regex myRegex( "REGULAR EXPRESSIONS",
                        std::regex_constants::ECMAScript |
                        std::regex_constants::icase ); // syntax rules and options
    std::regex myWrdParser    ( "(\\w+)"    );
    std::regex longWordsParser( "(\\w{8,})" );
    auto       matchRes = std::smatch{};

    {
        std::cout << "\nSEARCHING for a regex (std::regex_search)\n";
        std::cout << "\tInput string " 
                  << ( std::regex_search( myStr, matchRes, myRegex )  ? "contains " :
                  "does not contain " ) << "REGULAR EXPRESSIONS" << "\n";
        
        /*!
         * std::match_result is a container-like class that
         * stores matches found on the target sequence of chars after
         * a regex matching operation.
         * 
         * Therefore, it provides us with a lot of infos and methods
         * regarding capacity/iterators/formatting...
         */
        std::cout << "\tThere is " << matchRes.size() << " match.\n";
        std::cout << "\t" << matchRes.prefix() << " (length " 
                  << matchRes.length() << ") is the text before the match.\n";
    }

    {
        std::cout << "\nTOKENIZE a string using regex (std::sregex_iterator)\n";
        auto words_begin =
            std::sregex_iterator( std::begin(myStr), std::end(myStr), myWrdParser );
        auto words_end = std::sregex_iterator();

        std::cout << "\tInput string contains " 
                  << std::distance( words_begin, words_end )
                  << " words\n";
        
        const int WD_SIZE { 7 };
        auto nbOfLongWords = std::count_if(words_begin,
                                           words_end,
                                           [WD_SIZE](const std::smatch &it) { return it.str().size() > WD_SIZE; });

        std::cout << "\t" << nbOfLongWords << " of them have a size > " << WD_SIZE << "\n";
    }

    {
        std::cout << "\nREPLACE a string using regex (std::regex_replace)\n";
        std::string myResStr = std::regex_replace( myStr, longWordsParser, "[$&]");
        std::cout << "\tHere is the result of replacing 'long words' "
                     "(size > 7) by [long words] : " << myResStr << "\n";         
    }

    return EXIT_SUCCESS;
}

/*
SEARCHING for a regex (std::regex_search)
        Input string contains REGULAR EXPRESSIONS
        There is 1 match.
        Hello, beautiful world of  (length 19) is the text before the match.

TOKENIZE a string using regex (std::sregex_iterator)
        Input string contains 6 words
        2 of them have a size > 7

REPLACE a string using regex (std::regex_replace)
        Here is the result of replacing 'long words' (size > 7) by [long words] : Hello, [beautiful] world of regular [expressions] !
*/