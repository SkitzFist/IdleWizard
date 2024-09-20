#ifndef IDLE_WIZARD_RANDOM_H
#define IDLE_WIZARD_RANDOM_H

#include <random>

namespace Random {

inline int randomInt(int min, int max) {
    return std::rand() % ((max + 1) - min);
}

} // namespace Random

#endif
