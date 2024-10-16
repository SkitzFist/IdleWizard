#include "EntityTypeMap.h"

#include <cstring>

// debug
#include <iostream>

void EntityTypeMap::add(const EntityType type, const int id) {
    std::vector<int> &vec = typeMap[(int)type];
    vec.emplace_back(id);
    std::cout << "Adding: " << toString(type) << "  ID: " << id << "   Vec size: " << vec.size() << '\n';
}

void EntityTypeMap::remove(const EntityType type, const int id) {
    std::cout << "Removing " << toString(type) << "  ID: " << id << "\n";
    std::vector<int> &vec = typeMap[(int)type];
    std::cout << "\ttypeMapSize before: " << vec.size() << '\n';
    int index = getIndex(vec, id);
    if (vec.size() > 1) {
        memcpy(vec.data() + index, vec.data() + index + 1, (vec.size() - index - 1) * sizeof(int));
    }

    vec.pop_back();
    std::cout << "\ttypeMapSize after: " << vec.size() << "\n";
}

void EntityTypeMap::switchId(const EntityType type, const int from, const int to) {
    std::cout << "Switching Id: " << toString(type) << "  from: " << from << "   to: " << to << '\n';
    std::vector<int>& vec = typeMap[(int)type];
    std::cout << "\tSize before: " << vec.size() << '\n';
    int index = getIndex(vec, from);
    vec[index] = to;

    if(vec.size() > 1){
        std::cout << "\tNeeds sorting\n";
        sortItem(typeMap[(int)type], to);
    }

    std::cout << "\tSize after: " << vec.size() << '\n';
}

int EntityTypeMap::getIndex(std::vector<int> &vec, int entityId) {
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

void EntityTypeMap::sortItem(std::vector<int> &vec, int entityId) {
    int newIndex = entityId;

    // move element up
    while (newIndex > 0 && vec[newIndex] < vec[newIndex - 1]) {
        std::swap(vec[newIndex], vec[newIndex - 1]);
        --newIndex;
    }

    // move element down
    while (newIndex < vec.size() && vec[newIndex] > vec[newIndex + 1]) {
        std::swap(vec[newIndex], vec[newIndex + 1]);
        ++newIndex;
    }
}
