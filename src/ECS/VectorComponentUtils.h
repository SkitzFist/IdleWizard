#ifndef IDLE_MINER_VECTOR_COMPONENT_UTILS_H
#define IDLE_MINER_VECTOR_COMPONENT_UTILS_H

#include "VectorComponent.h"

int getIndex(const VectorComponent &component, const int entityID);

void putHighestEntityAtBack(VectorComponent &c);

// both have component
bool swapDataThenPop(VectorComponent &c, int id);
// only A has component
bool swapDataAndIdThenPop(VectorComponent &c, int id);
// only b has component
bool switchId(VectorComponent &c, int from, int to);

#endif
