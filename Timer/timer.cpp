#include <chrono>
#include <iostream>

struct Timer
{
    std::chrono::_V2::system_clock::time_point start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        //std::cout << "Timer took " << duration.count() * 1000.0f << " ms\n";
    }

    std::chrono::duration<float> getTime()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        return duration;
    }
};
