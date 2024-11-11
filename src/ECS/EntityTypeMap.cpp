#include "EntityTypeMap.h"

#include <cstring>

void EntityTypeMap::add(const EntityType type, const int id) {
    std::vector<int>& vec = typeMap[(int)type];
    vec.emplace_back(id);

    if (vec.size() > 1) {
        sortItem(vec, vec.size() - 1);
    }
}

void EntityTypeMap::remove(const EntityType type, const int id) {
    std::vector<int>& vec = typeMap[(int)type];

    if (vec.size() == 1) {
        vec.clear();
        return;
    }

    int index = getIndex(vec, id);
    memcpy(vec.data() + index, vec.data() + index + 1, (vec.size() - index - 1) * sizeof(int));
    vec.pop_back();
}

void EntityTypeMap::switchId(const EntityType type, const int from, const int to) {
    std::vector<int>& vec = typeMap[(int)type];
    int index = getIndex(vec, from);
    vec[index] = to;

    if (vec.size() > 1) {
        sortItem(typeMap[(int)type], index);
    }
}

int EntityTypeMap::getIndex(std::vector<int>& vec, int entityId) {
    int low = 0;
    int high = vec.size() - 1;
    int mid = 0;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (vec[mid] == entityId) {
            return mid;
        }

        if (vec[mid] < entityId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void EntityTypeMap::sortItem(std::vector<int>& vec, int index) {
    int newIndex = index;

    // move element up
    while (newIndex > 0 && vec[newIndex] < vec[newIndex - 1]) {
        std::swap(vec[newIndex], vec[newIndex - 1]);
        --newIndex;
    }

    // move element down
    while (newIndex < vec.size() - 1 && vec[newIndex] > vec[newIndex + 1]) {
        std::swap(vec[newIndex], vec[newIndex + 1]);
        ++newIndex;
    }
}
