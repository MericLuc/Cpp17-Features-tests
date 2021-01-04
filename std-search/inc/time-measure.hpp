
#ifndef TIME_MEASURE_HPP
#define TIME_MEASURE_HPP

#include <iomanip>
#include <string>
#include <chrono>
#include <thread>

//////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief A stopwatch class to perform measures
 */
template <typename Clock = std::chrono::high_resolution_clock>
class stopwatch
{
private:
    const std::string                m_title;
    const typename Clock::time_point m_start;

public:
    stopwatch(const std::string &p_title = "") : m_title(p_title), m_start(Clock::now()) {}
    ~stopwatch()
    {
        std::cout << m_title << " performed in "
                  << elapsed_time<unsigned int, std::chrono::milliseconds>() << " ms\n";
    }

    template <typename Rep = typename Clock::duration::rep,
              typename Units = typename Clock::duration>
    Rep elapsed_time(void) const
    {
        std::atomic_thread_fence(std::memory_order_relaxed);
        auto l_time = std::chrono::duration_cast<Units>(Clock::now() - m_start).count();
        std::atomic_thread_fence(std::memory_order_relaxed);

        return static_cast<Rep>(l_time);
    }
};

using precise_stopwatch   = stopwatch<>;
using system_stopwatch    = stopwatch<std::chrono::system_clock>;
using monotonic_stopwatch = stopwatch<std::chrono::steady_clock>;

#endif //TIME_MEASURE_HPP