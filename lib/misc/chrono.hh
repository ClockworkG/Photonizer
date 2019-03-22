#pragma once

#include <chrono>

template <typename Unit = std::chrono::milliseconds>
class Chrono
{
public:
    Chrono(double& output)
        : output_(output)
        , begin_(std::chrono::steady_clock::now())
    {}

    ~Chrono()
    {
        auto diff = std::chrono::steady_clock::now() - begin_;
        output_ = std::chrono::duration_cast<Unit>(diff).count();
    }

    Chrono(const Chrono&) = delete;
    Chrono(Chrono&&) = delete;
    Chrono& operator=(const Chrono&) = delete;
    Chrono& operator=(Chrono&&) = delete;

private:
    double& output_;
    std::chrono::steady_clock::time_point begin_;
};
