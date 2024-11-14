#ifndef IDLE_WIZARD_TIMER_H
#define IDLE_WIZARD_TIMER_H

#include <chrono>

struct Timer {
    std::chrono::high_resolution_clock::time_point start;

    void begin() {
        start = std::chrono::high_resolution_clock::now();
    }

    double getDuration() const {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        return duration.count();
    }
};

struct SystemTimer {
    std::chrono::high_resolution_clock::time_point begin() const {
        return std::chrono::high_resolution_clock::now();
    }

    double getDuration(std::chrono::high_resolution_clock::time_point& start) const {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        return duration.count();
    }
};

#endif
