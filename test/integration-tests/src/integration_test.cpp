#include "consumer.hpp"
#include "producer.hpp"
#include "viewer.hpp"
#include <vector>

int main()
{
    stdext::read_write_mutex mutex {};
    std::mutex cout_mutex {};
    buffer_t buffer {};
    std::vector<std::thread> threads {};

    constexpr unsigned delay_ms = 30u;

    threads.reserve(12u);

    threads.emplace_back(producer {mutex, buffer, 0xAAu, 20u, delay_ms});
    threads.emplace_back(producer {mutex, buffer, 0xBBu, 20u, delay_ms});
    threads.emplace_back(producer {mutex, buffer, 0xCCu, 50u, delay_ms});
    threads.emplace_back(producer {mutex, buffer, 0xDDu, 20u, delay_ms});
    threads.emplace_back(producer {mutex, buffer, 0xEEu, 50u, delay_ms});
    threads.emplace_back(producer {mutex, buffer, 0xFFu, 20u, delay_ms});

    threads.emplace_back(viewer {'A', cout_mutex, mutex, buffer, 60u, delay_ms});
    threads.emplace_back(viewer {'B', cout_mutex, mutex, buffer, 60u, delay_ms});
    threads.emplace_back(viewer {'C', cout_mutex, mutex, buffer, 61u, delay_ms});

    threads.emplace_back(consumer {mutex, buffer, 60u, delay_ms});
    threads.emplace_back(consumer {mutex, buffer, 60u, delay_ms});
    threads.emplace_back(consumer {mutex, buffer, 60u, delay_ms});

    for (auto& thread: threads)
    {
        thread.join();
    }

    std::cout << "done\n";
    return 0;
}
