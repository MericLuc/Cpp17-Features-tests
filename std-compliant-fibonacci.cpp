/************************************************************
 *             STD COMPLIANT FIBONACCI ITERATORS            *
 ************************************************************/

/*!
 * @brief We have implemented the Fibonacci's sequence
 *        algorithm in terms of std compliant iterators.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

/*!
 * @brief fibonacci_IT
 *        Iterator class that should only
 *        be used by fibonacci_range.
 */
class fibonacci_IT {
    public:
        fibonacci_IT()          = default;
        virtual ~fibonacci_IT() = default;

    public:
        size_t operator*() const { return m_cur; }
        fibonacci_IT& operator++() {
            std::swap( m_prev, m_cur );
            m_cur += m_prev;
            m_idx++;

            return *this;
        }
        fibonacci_IT& operator--() {
            if ( !m_idx ) return *this; 
            const size_t tmp_val { m_prev };
            m_prev = m_cur - m_prev;
            m_cur  = tmp_val;
            m_idx--;

            return *this;
        }
        bool operator!=(const fibonacci_IT& o) const { return m_idx != o.m_idx;     }
        bool operator< (const fibonacci_IT& o) const { return m_idx <  o.m_idx;     }
        bool operator<=(const fibonacci_IT& o) const { return m_idx <= o.m_idx;     }
        bool operator==(const fibonacci_IT& o) const { return !this->operator!=(o); }
        bool operator> (const fibonacci_IT& o) const { return !this->operator<=(o); }
        bool operator>=(const fibonacci_IT& o) const { return !this->operator< (o); }
    
    private:
        explicit fibonacci_IT( size_t p_idx ) : m_idx(p_idx) {}

    private:
        size_t m_idx {0}; /*!< Index of the current element  */
        size_t m_prev{0}; /*!< Previous value ( F(m_idx-1) ) */
        size_t m_cur {1}; /*!< Current value  ( F(m_idx)   ) */

    friend class fibonacci_range;
};

/*!
 * @brief Enables compliance with std
 *        algorithms.
 */
namespace std {
    template<>
    struct iterator_traits<fibonacci_IT> {
        using iterator_category = forward_iterator_tag;
        using value_type        = size_t;
    };
}

/*!
 * @brief fibonacci_range
 *        Declares a range in the range [0..p_end]
 *        and allows to iterate over it.
 */
class fibonacci_range {
    public:
        fibonacci_range() = delete;
        fibonacci_range( const size_t& p_end ) : m_end(p_end) {}

        fibonacci_IT        begin () const { return m_begin; }
        fibonacci_IT        end   () const { return m_end;   }
        const fibonacci_IT& cbegin() const { return m_begin; }
        const fibonacci_IT& cend  () const { return m_end;   }

    private:
        const fibonacci_IT m_begin{};
        fibonacci_IT       m_end;
};

int main()
{
    constexpr size_t    ELMS {20};
    fibonacci_range     myRange{ELMS};
    std::vector<size_t> myResults;

    // -> We can use it in auto for range loops
    std::cout << "Here are the first " << ELMS << " of the Fibonacci sequence:\n\t";
    for ( const auto& fibElm : fibonacci_range(ELMS) ) { std::cout << fibElm << " "; }
    std::cout << "\n";

    // -> We can also apply every std algorithms
    //    to it !
    std::cout << "Applying some std algorithms...\n";
    std::cout << "\tstd::minmax_element - ";
    auto [min_elm, max_elm] = std::minmax_element( std::begin(myRange), 
                                                   std::end  (myRange) );
    std::cout << "[ " << *min_elm << " , " << *max_elm << " ]\n";

    std::cout << "\tstd::copy range into std::vector - ";
    std::copy( std::begin(myRange), std::end(myRange), std::back_inserter(myResults) );
    std::copy( std::begin(myResults), 
               std::end  (myResults), 
               std::ostream_iterator<size_t>(std::cout, " ") );
    std::cout << "\n";

    return EXIT_SUCCESS;
}

/*
Here are the first 20 of the Fibonacci sequence:
        1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765
Applying some std algorithms...
        std::minmax_element - [ 1 , 6765 ]
        std::copy range into std::vector - 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765
*/