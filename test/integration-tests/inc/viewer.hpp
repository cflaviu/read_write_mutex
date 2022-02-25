#pragma once
#ifndef PCH
    #include "base.hpp"
    #include <iostream>
    #include <mutex>
#endif

class viewer: public base
{
public:
    viewer(marker_t marker, std::mutex& cout_mutex, stdext::read_write_mutex& mutex, buffer_t& buffer, unsigned count, unsigned delay_ms):
        base(mutex, buffer, count, delay_ms),
        cout_mutex(cout_mutex),
        marker(marker)
    {
    }

protected:
    void execute() override
    {
        stdext::read_lock read_lock(mutex);
        std::unique_lock write_lock(cout_mutex);
        std::cout << marker << ": ";
        for (int item: buffer)
        {
            std::cout << std::hex << item << ' ';
        }

        std::cout << '\n';
    }

    std::mutex& cout_mutex;
    marker_t marker;
};
