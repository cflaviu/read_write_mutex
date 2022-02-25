#pragma once
#ifndef PCH
    #include <chrono>
    #include <deque>
    #include <read_write_mutex.hpp>
    #include <thread>
#endif

using marker_t = std::uint8_t;
using buffer_t = std::deque<marker_t>;

class base
{
public:
    base(stdext::read_write_mutex& mutex, buffer_t& buffer, unsigned count, unsigned delay_ms):
        delay(delay_ms),
        buffer(buffer),
        mutex(mutex),
        count(count)
    {
    }

    virtual ~base() = default;

    void operator()()
    {
        for (auto c = count; c != 0u; --c)
        {
            execute();
            std::this_thread::sleep_for(delay);
        }
    }

protected:
    virtual void execute() = 0;

    std::chrono::milliseconds delay;
    buffer_t& buffer;
    stdext::read_write_mutex& mutex;
    unsigned count;
};
