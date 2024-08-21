#include "VectorComponentUtils.h"

int getIndex(const VectorComponent &component, const int entityID) {

    int low = 0;
    int high = component.entityIds.size() - 1;
    int mid = 0;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (component.entityIds[mid] == entityID) {
            return mid;
        }

        if (component.entityIds[mid] < entityID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    TraceLog(LOG_ERROR, "VectorComponentUtils: Could not find index!");

    return -1;
}

void sortElement(VectorComponent &c, int index) {
    if (index < 0 || index >= c.entityIds.size())
        return;

    int newIndex = index;

    // Move the element downwards if necessary
    while (newIndex > 0 && c.entityIds[newIndex] < c.entityIds[newIndex - 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex - 1]);
        std::swap(c.data[newIndex], c.data[newIndex - 1]);
        --newIndex;
    }

    // Move the element upwards if necessary
    while (newIndex < c.entityIds.size() - 1 && c.entityIds[newIndex] > c.entityIds[newIndex + 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex + 1]);
        std::swap(c.data[newIndex], c.data[newIndex + 1]);
        ++newIndex;
    }
}

// both have component
bool swapDataThenPop(VectorComponent &c, int id) {

    // in order to avoid ID confusion, the entity with the highest id must be pushed to the back,
    // as we always delete from the bottom.
    // putHighestEntityAtBack(c);

    int index = getIndex(c, id);

    if (index == -1) {
        TraceLog(LOG_ERROR, "VectorComponentUtils: SWAP DATA Could not find ID");
        return false;
    }

    std::swap(c.data[index], c.data.back());
    c.data.pop_back();

    // std::cout << "\tAindex: " << aIndex << "  BIndex: " << bIndex << '\n';
    return true;
}

// only A has component
bool swapDataAndIdThenPop(VectorComponent &c, int id) {

    int index = getIndex(c, id);
    if (index == -1) {
        TraceLog(LOG_ERROR, "VectorComponentUtils: SWAP DATA & ID Could not find ID");
        return false;
    }

    std::swap(c.data[index], c.data.back());
    c.data.pop_back();

    std::swap(c.entityIds[index], c.entityIds.back());
    c.entityIds.pop_back();

    sortElement(c, index);

    return true;
}

bool switchId(VectorComponent &c, int fromId, int toId) {

    int index = getIndex(c, fromId);

    if (index == -1) {
        TraceLog(LOG_ERROR, "VectorComponentUtils: Switch Id could not find id");
        return false;
    }

    c.entityIds[index] = toId;

    sortElement(c, index);

    // std::cout << "Switch Id could not find id\n";
    return true;
}
