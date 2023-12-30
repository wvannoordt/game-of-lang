#pragma once

namespace gola
{
    struct frame_rate_t
    {
        double rate;
        frame_rate_t(const double& rate_in) : rate{rate_in} {}
        
        double fps() const
        {
            return rate;
        }
    };
}