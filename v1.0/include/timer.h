#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <iostream>
#include <chrono>
#include <vector>

class Timer {
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;
private:
    std::chrono::time_point<hrClock> start;
public:
    Timer() : start{ hrClock::now() } {}
    void reset() {
        start = hrClock::now();
    }
    double elapsed() const {
        return durationDouble(hrClock::now() - start).count();
    }
};

#endif