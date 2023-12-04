#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds
{
    class Timer
    {
        std::chrono::steady_clock::time_point m_startTime;
    public:
        void start();
        long long stop();
    };
}

#endif
