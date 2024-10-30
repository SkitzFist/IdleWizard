#ifndef IDLE_WIZARD_TYPE_MAP_H
#define IDLE_WIZARD_TYPE_MAP_H

#include <array>
#include <vector>

#include "EntityType.h"

struct EntityTypeMap {
    std::array<std::vector<int>, (int)EntityType::COUNT> typeMap;

    void add(const EntityType type, const int id);
    void remove(const EntityType type, const int id);
    void switchId(const EntityType type, const int from, const int to);

    std::vector<int>& operator[](std::size_t index) {
        return typeMap[index];
    }

    std::vector<int>& operator[](EntityType type) {
        return typeMap[(int)type];
    }

  private:
    int getIndex(std::vector<int>& vec, int entityId);
    void sortItem(std::vector<int>& vec, int entityId);
};

#endif
