#ifndef IDLE_WIZARD_COMPONENT_H
#define IDLE_WIZARD_COMPONENT_H

#include <cstddef>
#include <cstring>
#include <vector>

class Component {
  public:
    Component(const size_t dataTypeSize, const size_t initCapacity) : m_dataTypeSize(dataTypeSize), capacity(initCapacity), m_size(0) {
        m_data = new std::byte[dataTypeSize * initCapacity];
        m_entityIds.reserve(initCapacity);
    }

    ~Component() {
        delete[] m_data;
    }

    // Disable copy semantics to prevent accidental copying, should maybe allow this for when world splitting
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    Component(Component&& other) noexcept
        : m_data(other.m_data),
          m_entityIds(std::move(other.m_entityIds)),
          m_dataTypeSize(other.m_dataTypeSize),
          capacity(other.capacity),
          m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.capacity = 0;
    }

    Component& operator=(Component&& other) noexcept {
        if (this != &other) {
            delete[] m_data;

            m_data = other.m_data;
            m_entityIds = std::move(other.m_entityIds);
            m_dataTypeSize = other.m_dataTypeSize;
            capacity = other.capacity;
            m_size = other.m_size;

            other.m_data = nullptr;
            other.m_size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    int operator[](const int index) {
        return m_entityIds[index];
    }

    void resize(size_t newCapacity) {
        capacity = newCapacity;

        std::byte* tmp = new std::byte[m_dataTypeSize * capacity];

        memcpy(tmp, m_data, m_dataTypeSize * m_size);

        delete[] m_data;
        m_data = tmp;
    }

    size_t getSize() const noexcept {
        return m_size;
    }

    size_t getCapacity() const noexcept {
        return capacity;
    }

    void add(void* item, int id) {
        if (m_size == capacity) {
            resize(capacity * 2);
        }

        memcpy(&m_data[m_dataTypeSize * m_size], item, m_dataTypeSize);
        m_entityIds.emplace_back(id);
        ++m_size;
    }

    template <typename T>
    T& get(size_t index) {
        return reinterpret_cast<T&>(m_data[index * m_dataTypeSize]);
    }

    template <typename T>
    const T& get(size_t index) const {
        return reinterpret_cast<const T&>(m_data[index * m_dataTypeSize]);
    }

    template <typename T>
    T& getFromId(size_t id) {
        int index = getIndex(id);
        return reinterpret_cast<T&>(m_data[index * m_dataTypeSize]);
    }

    template <typename T>
    const T& getFromId(size_t id) const {
        int index = getIndex(id);
        return reinterpret_cast<const T&>(m_data[index * m_dataTypeSize]);
    }

    int getIndex(int entityID) const {
        int low = 0;
        int high = m_entityIds.size() - 1;
        int mid = 0;

        while (low <= high) {
            mid = low + (high - low) / 2;
            if (m_entityIds[mid] == entityID) {
                return mid;
            }

            if (m_entityIds[mid] < entityID) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }

    /////////////////////////////////
    ///       Deletion          ////
    ///////////////////////////////

    // both has component
    void swapDataPopBack(const int entityId) {
        const int index = getIndex(entityId);
        if (index == -1) {
            return;
        }

        // moves last data to index
        memcpy(m_data + (index * m_dataTypeSize), m_data + ((m_size - 1) * m_dataTypeSize), m_dataTypeSize);

        --m_size;
        m_entityIds.pop_back();
    }

    // Only A has Component
    void swapDataAndIdPopBack(const int entityId) {

        /*
          todo, coudl make this more effective by just moving the entire thing
          say [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            remove 2
                  [3, 4, 5, 6, 7, 8, 9]
            [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            that would just overwrite the values, and keeping the entire thing sorted at the same time.
            using the sort function is some overhead as the value is swapped for each position.
            look into if similar can be done to the entityID:S
        */
        int index = getIndex(entityId);
        if (index == -1) {
            return;
        }

        // moves last data to index
        memcpy(m_data + (index * m_dataTypeSize), m_data + ((m_size - 1) * m_dataTypeSize), m_dataTypeSize);
        // swap id
        std::swap(m_entityIds[index], m_entityIds.back());
        m_entityIds.pop_back();

        --m_size;

        if (m_size > 1) {
            sortItem(index);
        }
    }

    // only B has component
    void switchId(const int from, const int to) {
        const int index = getIndex(from);

        if (index == -1) {
            return;
        }

        m_entityIds[index] = to;
        if (m_size > 1) {
            sortItem(index);
        }
    }

  private:
    std::byte* m_data;
    std::vector<int> m_entityIds;
    size_t m_dataTypeSize;
    size_t capacity;
    size_t m_size;

  private:
    ////////////////////////////////
    ///    Moving / sorting     ///
    //////////////////////////////
    void swapData(const int indexA, const int indexB, void* tmp) {
        std::size_t memPlaceA = m_dataTypeSize * indexA;
        std::size_t memPlaceB = m_dataTypeSize * indexB;

        memcpy(tmp, m_data + memPlaceA, m_dataTypeSize);
        memcpy(m_data + memPlaceA, m_data + memPlaceB, m_dataTypeSize);
        memcpy(m_data + memPlaceB, tmp, m_dataTypeSize);
    }

    void sortItem(const int index) {
        int newIndex = index;

        void* tmp = malloc(m_dataTypeSize);

        // move element up
        while (newIndex > 0 && m_entityIds[newIndex] < m_entityIds[newIndex - 1]) {
            std::swap(m_entityIds[newIndex], m_entityIds[newIndex - 1]);
            swapData(newIndex, newIndex - 1, tmp);
            --newIndex;
        }

        // move element down
        while (newIndex < m_size && m_entityIds[newIndex] > m_entityIds[newIndex + 1]) {
            std::swap(m_entityIds[newIndex], m_entityIds[newIndex + 1]);
            swapData(newIndex, newIndex + 1, tmp);
            ++newIndex;
        }

        free(tmp);
    }
};

#endif
