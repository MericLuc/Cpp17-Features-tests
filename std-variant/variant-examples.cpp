/************************************************************
 *                  STD::VARIANT EXAMPLES                   *
 ************************************************************/

/*!
 * @note Here is a great video
 *       in which Nick Sarten presents "type safe
 *       state machines with C++17 std::variant".
 *
 * https://www.youtube.com/watch?v=4v-pPkVaFA4&feature=youtu.be
 */

/*!
 * @note Here is an interesting blog article
 *       on "modernes C++" that deals with
 *       the usage of Visitor and std::visit
 *       for std::variant.
 *
 * http://www.modernescpp.com/index.php/c-17-constructed-in-place
 */

/*!
 * @note Here is a great comparaison between
 *       inheritance and std::variant + std::visit !
 * 
 * http://cpptruths.blogspot.com/2018/02/inheritance-vs-stdvariant-based.html
 */

#include <variant>
#include <iostream>
#include <string>
#include <vector>

#define EXAMPLE_1 1 // Polymorphism of unrelated objects
#define EXAMPLE_2 1 // Roots of an equation

#ifdef EXAMPLE_1
    class Triangle
    {
    public:
        void Render() { std::cout << "Drawing a triangle!\n"; }
    };

    class Polygon
    {
    public:
        void Render() { std::cout << "Drawing a polygon!\n"; }
    };

    class Sphere
    {
    public:
        void Render() { std::cout << "Drawing a sphere!\n"; }
    };
#endif

#ifdef EXAMPLE_2
    #include <cmath>

    using DoublePair    = std::pair<double, double>;
    using EquationRoots = std::variant<DoublePair, double, std::monostate>; 

    EquationRoots FindRoots(double a, double b, double c)
    {
        auto d = b*b-4*a*c;

        if (d > 0.0)
        {
            auto p = sqrt(d) / (2*a);
            return std::make_pair(-b + p, -b - p);
        }
        else if (d == 0.0)
            return (-1*b)/(2*a);

        return std::monostate();
    }

    struct RootPrinterVisitor
    {
        void operator()(const DoublePair& arg) 
        { 
            std::cout << "2 roots: " << arg.first << " " << arg.second << '\n'; 
        }
        void operator()(double arg) 
        { 
            std::cout << "1 root: " << arg << '\n'; 
        }
        void operator()(std::monostate) 
        { 
            std::cout << "No real roots found.\n";
        }
    };
#endif

int main()
{
    #ifdef EXAMPLE_1
    {
        // std::visit used for polymorphism
        // without vtables nor common base class.

        // From the book "C++17 in details" (Bartlomiej Filipek)
        std::vector< std::variant<Triangle, Polygon, Sphere> > objects
        {
            Polygon(), Triangle(), Sphere(), Triangle() 
        };

        auto CallRender = [](auto &obj) { obj.Render(); };

        for ( auto &obj : objects )
            std::visit( CallRender, obj );
    }
    #endif

    #ifdef EXAMPLE_2
    {
        // std::visit to wrap every possibility of
        // equation roots finding.

        // From the book "C++17 in details" (Bartlomiej Filipek)
        std::visit(RootPrinterVisitor{}, FindRoots(10, 0, -2));
        std::visit(RootPrinterVisitor{}, FindRoots( 2, 0, -1));
    }
    #endif
}