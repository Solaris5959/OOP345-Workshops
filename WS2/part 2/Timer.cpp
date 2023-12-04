#include <chrono>
#include "Timer.h"

using namespace std::chrono;

namespace sdds
{
    void Timer::start()
    {
        this->m_startTime = steady_clock::now();
    }

    long long Timer::stop()
    {
        auto now = steady_clock::now();
        auto duration = duration_cast<nanoseconds>(now - this->m_startTime);
        return duration.count();
    }
}