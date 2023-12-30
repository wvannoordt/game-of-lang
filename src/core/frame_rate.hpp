#pragma once

#include <chrono>

namespace gola
{
    struct frame_rate_t
    {
        double rate;
        std::size_t nframes;
        double totaltime;
        
        using time_t = decltype(std::chrono::steady_clock::now());
        time_t t0, t1;
        
        frame_rate_t(const double& rate_in) : rate{rate_in}, nframes{0}, totaltime{0.0} { }
        
        void start()
        {
            t0 = std::chrono::steady_clock::now();
        }
        
        auto get_pause_duration() const
        {
            auto t00 = std::chrono::steady_clock::now();
            auto diff = t00 - t0;
            std::size_t micros   = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
            std::size_t required = 1e6/rate;
            if (micros > required) return std::chrono::microseconds(0);
            return std::chrono::microseconds(required - micros);
        }
        
        void stop()
        {
            t1 = std::chrono::steady_clock::now();
            auto diff = t1 - t0;
            totaltime += std::chrono::duration_cast<std::chrono::microseconds>(diff).count()/1e6;
            nframes++;
        }
        
        double fps() const
        {
            return nframes/totaltime;
        }
    };
}