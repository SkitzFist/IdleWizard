#ifndef IDLE_MINER_COMPONENT_UTIL_H
#define IDLE_MINER_COMPONENT_UTIL_H

#include "Component.h"

// Debug
#include <iostream>

//////////////////////////////////////////////
///             General                   ///
////////////////////////////////////////////

inline void resize(Component &c) {
    c.capacity *= 1.75;
    char *tmp = new char[c.capacity * c.dataTypeSize];
    std::size_t size = c.size * c.dataTypeSize;
    memcpy(tmp, c.data, size);
    delete[] c.data;
    c.data = tmp;
}

// this is a bit slower, but could be usefull when no type can be deducted (if that case ever arise...)
inline void add(Component &c, const int id, const void *itemData) {
    if (c.size == c.capacity) {
        resize(c);
    }

    std::size_t lastEmptyIndex = c.size * c.dataTypeSize;
    memcpy(c.data + lastEmptyIndex, itemData, c.dataTypeSize);
    ++c.size;

    c.entityIds.emplace_back(id);
}

// a tad faster then previous add
template <typename T>
inline void add(Component &c, const int id, const T &item) {
    if (c.size == c.capacity) {
        resize(c);
    }

    std::size_t lastEmptyIndex = c.size * c.dataTypeSize;
    memcpy(c.data + lastEmptyIndex, &item, c.dataTypeSize);
    ++c.size;

    c.entityIds.emplace_back(id);
}

// access data with posibility to modify it directly
template <typename T>
inline T &accessData(const Component &c, const int index) {
    std::size_t trueIndex = index * c.dataTypeSize;
    return *reinterpret_cast<T *>(c.data + trueIndex);
}

template <typename T>
inline T &accessData(const Component &c, const int index, const int subIndex) {
    std::size_t trueIndex = (index * c.dataTypeSize) + (sizeof(T) * subIndex);
    return *reinterpret_cast<T *>(c.data + trueIndex);
}

// read data without possibility to modify it.
template <typename T>
inline const T &readData(const Component &c, const int index) {
    std::size_t trueIndex = index * c.dataTypeSize;
    return *reinterpret_cast<const T *>(c.data + trueIndex);
}

template <typename T>
inline const T &readData(const Component &c, const int index, const int subIndex) {
    std::size_t trueIndex = (index * c.dataTypeSize) + (sizeof(T) * subIndex);
    return *reinterpret_cast<const T *>(c.data + trueIndex);
}

inline int getIndex(const Component &component, const int entityID) {
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

    std::cout << "ComponentUtils: could not find ID: " << entityID << " Returning -1\n";
    return -1;
}

//////////////////////////////////////////////
///        Moving / Sorting               ///
////////////////////////////////////////////

inline void swapData(Component &c, const int indexA, const int indexB) {
    void *tmp = malloc(c.dataTypeSize);
    std::size_t memPlaceA = c.dataTypeSize * indexA;
    std::size_t memPlaceB = c.dataTypeSize * indexB;

    memcpy(tmp, c.data + memPlaceA, c.dataTypeSize);
    memcpy(c.data + memPlaceA, c.data + memPlaceB, c.dataTypeSize);
    memcpy(c.data + memPlaceB, tmp, c.dataTypeSize);

    free(tmp);
}

inline void moveDataBackToIndex(Component &c, const int indexA) {
    std::size_t memPlaceA = c.dataTypeSize * indexA;
    std::size_t memPlaceB = c.dataTypeSize * c.size - c.dataTypeSize;
    memcpy(c.data + memPlaceA, c.data + memPlaceB, c.dataTypeSize);
}

inline void sortItem(Component &c, const int index) {

    int newIndex = index;

    // Move the element downwards if necessary
    while (newIndex > 0 && c.entityIds[newIndex] < c.entityIds[newIndex - 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex - 1]);
        swapData(c, newIndex, newIndex - 1);
        --newIndex;
    }

    // Move the element upwards if necessary
    while (newIndex < c.entityIds.size() - 1 && c.entityIds[newIndex] > c.entityIds[newIndex + 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex + 1]);
        swapData(c, newIndex, newIndex + 1);
        ++newIndex;
    }
}

//////////////////////////////////////////////
///          Deletion                     ///
////////////////////////////////////////////

// Both has component
inline bool swapDataThenPopBack(Component &c, const int id) {
    int index = getIndex(c, id);
    if (index == -1) {
        std::cerr << "SwapDataThenPopBack: could not find id\n";
        return false;
    }

    moveDataBackToIndex(c, id);
    --c.size; // no need to actually delete data as it's out of the span now.
    c.entityIds.pop_back();

    return true;
}

// Only A has component
inline bool swapDataAndIdThenPopBack(Component &c, const int id) {
    int index = getIndex(c, id);
    if (index == -1) {
        std::cerr << "SwapDataAndIdThenPopBack: could not find id\n";
        return false;
    }

    // swap data
    moveDataBackToIndex(c, id);
    --c.size;

    // swap id
    std::swap(c.entityIds[index], c.entityIds.back());
    c.entityIds.pop_back();

    sortItem(c, index);
    return true;
}

// Only B has component
inline bool switchId(Component &c, const int from, const int to) {
    int index = getIndex(c, from);

    if (index == -1) {
        std::cerr << "SwitchID: Could not find id\n";
        return false;
    }

    c.entityIds[index] = to;

    sortItem(c, index);

    return true;
}

//////////////////////////////////////////////
///          Printing                     ///
////////////////////////////////////////////

#endif