#pragma once
#ifndef PCH
    #include "base.hpp"
#endif

class consumer: public base
{
public:
    using base::base;

protected:
    void execute() override
    {
        stdext::write_lock lock(mutex);
        buffer.pop_front();
    }
};
