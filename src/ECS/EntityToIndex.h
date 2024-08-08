#ifndef IDLE_MINER_ENTITY_TO_INDEX_H
#define IDLE_MINER_ENTITY_TO_INDEX_H

#include <vector>

struct EntityIndexPair {
    int entity;
    int index;

    EntityIndexPair(int entity, int index) : entity(entity), index(index) {}
};

#endif
