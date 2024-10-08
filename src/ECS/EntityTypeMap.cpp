#include "EntityTypeMap.h"

 #include <cstring>

void EntityTypeMap::remove(const EntityType type, const int id){
  std::vector<int>& vec = typeMap[(int)type];
  int index = getIndex(vec, id);
  memcpy(vec.data() + index, vec.data() + index + 1, (vec.size() - index - 1) * sizeof(int));
  vec.pop_back();
}

void EntityTypeMap::switchId(const EntityType type, const int from, const int to){
  int index = getIndex(typeMap[(int)type], from);
  typeMap[(int)type][index] = to;

  sortItem(typeMap[(int)type], to);
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

void EntityTypeMap::sortItem(std::vector<int>& vec, int entityId){
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
