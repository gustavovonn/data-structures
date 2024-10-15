// Copyright <2024> - <Gustavo Rodrigues Alves D'Angelo>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList();  // Constructor
    ~CircularList();  // Destructor

    void clear();  // Clear list

    void push_back(const T& data);  // Insert element in the final
    void push_front(const T& data);  // Insert element in the beginning
    void insert(const T& data, std::size_t index);  // Insert data in index
    void insert_sorted(const T& data);  // Insert data respecting order

    T& at(std::size_t index);  // Return address to the element in index
    const T& at(std::size_t index) const;  // Const version of at

    T pop(std::size_t index);  // Remove at index
    T pop_back();  // Remove the last element
    T pop_front();  // Remove the first element
    void remove(const T& data);  // Remove the first appearence of data

    bool empty() const;  // Verify emptiness
    bool contains(const T& data);  // Verify existence of data
    std::size_t find(const T& data) const;  // Find the position of data

    std::size_t size() const;  // Returns the size
};


}  // namespace structures

#endif