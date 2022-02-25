#pragma once
#ifndef PCH
    #include "base.hpp"
#endif

class producer: public base
{
public:
    producer(stdext::read_write_mutex& mutex, buffer_t& buffer, marker_t marker, unsigned count, unsigned delay_ms):
        base(mutex, buffer, count, delay_ms),
        marker(marker)
    {
    }

protected:
    void execute() override
    {
        stdext::write_lock lock(mutex);
        buffer.push_back(marker);
    }

    marker_t marker;
};
