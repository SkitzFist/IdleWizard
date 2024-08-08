#ifndef IDLE_MINER_RANDOM_H
#define IDLE_MINER_RANDOM_H

#include <random>

namespace Random {

inline int randomInt(int min, int max) {
    return std::rand() % ((max + 1) - min);
}

} // namespace Random

#endif
