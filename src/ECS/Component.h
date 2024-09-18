#ifndef IDLE_MINER_COMPONENT_H
#define IDLE_MINER_COMPONENT_H

#include <vector>

//debug
#include <iostream>

/*
    HEAD MY WARNING. This datatype DOES NOT have any typesafety or security.
    It's up to you the programmer to use it in a safe way. No hand holding.

    You can store any type of data in a component, use accessData<T> and readData<T> to interpret 
    the bits as you like. 
*/

struct Component {
    std::vector<int> entityIds;
    const std::size_t dataTypeSize;
    char *data;
    int capacity;
    int size;

    Component(std::size_t dataTypeSize, int capacity = 100) : dataTypeSize(dataTypeSize),
                                                              capacity(capacity),
                                                              size(0) {
        data = new char[capacity * dataTypeSize];
        entityIds.reserve(capacity);
    }

    Component() : dataTypeSize(sizeof(int)), capacity(100), size(0){
        std::cerr << "Component.h, error: DEFAULT CONSTRUCTED!\n";
        data = new char[capacity * dataTypeSize];
        entityIds.reserve(capacity);
    } 

    ~Component() {
        delete[] data;
    }
};

#endif
