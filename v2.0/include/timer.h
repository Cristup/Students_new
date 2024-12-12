#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <iostream>
#include <chrono>
#include <vector>

/**
 * @class Timer
 * @brief A simple class to measure elapsed time.
 *
 * The `Timer` class allows measuring elapsed time using the system's high resolution clock.
 * It provides functionality to start, reset, and get the elapsed time in seconds.
 */
class Timer {
    using hrClock = std::chrono::high_resolution_clock; /**< High resolution clock type for time measurement */
    using durationDouble = std::chrono::duration<double>; /**< Duration type to represent time in seconds (as a double) */
private:
    std::chrono::time_point<hrClock> start; /**< Time point when the timer is started */
public:

    /**
     * @brief Default constructor that initializes the timer.
     *
     * The timer is started immediately upon construction.
     */
    Timer() : start{ hrClock::now() } {}

    /**
     * @brief Resets the timer to the current time.
     *
     * This function resets the internal start time to the current time, effectively
     * restarting the timer.
     */
    void reset() {
        start = hrClock::now();
    }

    /**
     * @brief Gets the elapsed time in seconds.
     *
     * This function calculates the time that has passed since the timer was started (or last reset),
     * and returns the result in seconds as a double value.
     *
     * @return The elapsed time in seconds.
     */
    double elapsed() const {
        return durationDouble(hrClock::now() - start).count();
    }
};

#endif