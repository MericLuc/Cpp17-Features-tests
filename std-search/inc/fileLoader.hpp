
#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <string>
#include <fstream>
#include <streambuf>
#include <optional>

//////////////////////////////////////////////////////////////////////////////////////////
std::optional<std::string> loadFile( const std::string& p_file )
{
    std::ifstream ifs ( p_file );
    std::string   res;

    if ( ifs.fail() ) return std::nullopt;

    // Do not rely on std::string automatic reallocation
    // See https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    // for more informations.
    ifs.seekg  ( 0, std::ios::end );
    res.reserve( ifs.tellg()      );
    ifs.seekg  ( 0, std::ios::beg );

    res.assign( (std::istreambuf_iterator<char>(ifs)),
                 std::istreambuf_iterator<char>() );
    
    return res;
}

#endif // FILELOADER_HPP