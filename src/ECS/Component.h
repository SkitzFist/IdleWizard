#ifndef IDLE_WIZARD_COMPONENT_H
#define IDLE_WIZARD_COMPONENT_H

#include <cstddef>
#include <cstring>
#include <vector>

//debug
#include <iostream>


class Component{
public:
  Component(const size_t dataTypeSize, const size_t initCapacity) : dataTypeSize(dataTypeSize), capacity(initCapacity), size(0){
    std::cout << "Normal ctr\n";
    try{
      data = new std::byte[dataTypeSize * initCapacity];
    } catch(...){
      std::cerr << "Component bad_alloc\n";
    }
    
  }

  ~Component(){
    delete[] data;
  }

  // Disable copy semantics to prevent accidental copying
  Component(const Component &) = delete;
  Component &operator=(const Component &) = delete;

  // Enable move semantics if needed
  Component(Component &&other) noexcept
      : data(other.data), dataTypeSize(other.dataTypeSize), capacity(other.capacity), size(other.size) {
        std::cout << "Move constructor\n";
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
  }

  Component &operator=(Component &&other) noexcept {
    std::cout << "Move operator\n";
    if (this != &other) {
        delete[] data;

        data = other.data;
        dataTypeSize = other.dataTypeSize;
        capacity = other.capacity;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
  }

  void resize(size_t newCapacity){
    capacity = newCapacity;

    std::byte* tmp = new std::byte[dataTypeSize * capacity];

    memcpy(tmp, data, dataTypeSize * size);
    
    delete[] data;
    data = tmp;
  }

  size_t getSize() const noexcept{
    return size;
  }

  size_t getCapacity() const noexcept{
    return capacity;
  }

  void add(void* item){
    if(size == capacity){
      std::cout << "SHOULD RESIZE\n";
      //resize();
    }

    memcpy(&data[dataTypeSize * size], item, dataTypeSize);
    ++size;
  }

  template<typename T>
  T& get(size_t index){
    return reinterpret_cast<T&>(data[index * dataTypeSize]);
  }

  template <typename T>
  const T &get(size_t index) const {
    return reinterpret_cast<const T &>(data[index * dataTypeSize]);
  }

private:
  std::byte* data;
  size_t dataTypeSize;
  size_t capacity;
  size_t size;
};

#endif
