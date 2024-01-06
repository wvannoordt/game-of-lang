#pragma once

#include <chrono>

namespace gola
{
    struct timer_t
    {
        using time_t = decltype(std::chrono::steady_clock::now());
        
        time_t t0, t1;
        
        
        void start()
        {
            t0 = std::chrono::steady_clock::now();
        }
        
        void stop()
        {
            t1 = std::chrono::steady_clock::now();
        }
        
        double elapsed_seconds() const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()*1.0e-6;
        }
    };
}