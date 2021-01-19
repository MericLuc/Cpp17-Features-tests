/************************************************************
 *           REDIRECT OR IGNORE SPECIFIC OUTPUTS            *
 *                  TO FILES (RAII STYLE)                   * 
 ************************************************************/

#include <iostream>
#include <fstream>
#include <ios>
#include <string>

class cout_redirect {
    public:
        explicit cout_redirect( const std::string& p_fileName = ""):
            m_ofs{p_fileName},
            m_backup{ std::cout.rdbuf( m_ofs.rdbuf() ) }
        {}

        ~cout_redirect() { std::cout.rdbuf( m_backup ); }

    private:
        std::ofstream   m_ofs;
        std::streambuf* m_backup;
};


int main()
{
    std::cout << "This is printed to the standard output stream\n";
    std::cout << "Next comments will be ignored\n";

    {
        cout_redirect _{};
        std::cout << "This is ignored\n";
        std::cout << "This is also ignored\n";
    }

    std::string l_fileName{ "toto.txt" };
    std::cout << "Next comments will be printed into the file : " 
              << l_fileName << "\n";
    {
        cout_redirect _{ l_fileName };
        std::cout << "Into the file\n";
        std::cout << "Also into the file\n";

        // Can be stacked
        {
            cout_redirect _{};
            std::cout << "Comment ignored\n";
        }
    }

    return EXIT_SUCCESS;
}

/*
// In console
This is printed to the standard output stream
Next comments will be ignored
Next comments will be printed into the file : toto.txt

// In "toto.txt" file
Into the file
Also into the file
*/