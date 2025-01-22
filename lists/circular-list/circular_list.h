// Copyright <2024> - <Gustavo Rodrigues Alves D'Angelo>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList() {  // Constructor
        head = nullptr;
        size_ = 0u;
    }

    ~CircularList() {  // Destructor
        clear();
    }

    void clear() {  // Clear list
        while (!(empty()))
            pop_front();
    }

    void push_back(const T& data) {  // Insert element in the final
        if (empty())
            return push_front();
        
        Node* new_element = new Node(data, head);
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");

        Node* last_element = circular_iterating(head, size()-1);

        last_element->next(new_element);

        size_++;
    }
    
    void push_front(const T& data) {  // Insert element in the beginning
        Node* new_element = new Node(data, nullptr);
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");

        if (empty()) {
            head = new_element;
            head->next(head);
        } else {
            Node* last_element = circular_iterating(head, size()-1);
            new_element->next(head);
            last_element->next(new_element);
        }
        size_++;
    }
    
    void insert(const T& data, std::size_t index) {  // Insert data in index
        if (index > size())
            throw std::out_of_range("Index out of range!");

        if (index == 0) {
            return push_front(data);
        } else if (index == size()) {
            return push_back(data);
        } else {
            Node* new_element = new Node(data, nullptr);

            if (new_element == nullptr)
                throw std::out_of_range("No memory available!");

            Node* prev_element = circular_iterating(head, index-1);
            new_element->next(prev_element->next());
            prev_element->next(new_element);
        }
        size_++;
    }
    
    void insert_sorted(const T& data) {  // Insert data respecting order
        Node* current = head;
        std::size_t index = size();
        for (std::size_t i = 0; i < size(); i++) {
            if (current->data() > data) {
                index = i;
                break;
            }
            current = current->next();
        }
        insert(data, index);
    }

    T& at(std::size_t index) {  // Return address to the element in index
        if (empty())
            throw std::out_of_range("The list is empty!");

        if (index > size()-1)
            throw std::out_of_range("Index out of range!");

        Node* element = circular_iterating(head, index);
        return element->data();
    }
    
    const T& at(std::size_t index) const {  // Const version of at
        if (empty())
            throw std::out_of_range("The list is empty!");

        if (index > size()-1)
            throw std::out_of_range("Index out of range!");

        Node* element = circular_iterating(head, index);
        return element->data();
    }

    T pop(std::size_t index) {  // Remove at index
        if (empty())
            throw std::out_of_range("The list is empty!");

        if (index == 0) {
            return pop_front();
        } else if (index == size()-1) {
            return pop_back();
        } else {
            Node* prev_element = circular_iterating(head, index-1);
            Node* to_remove = prev_element->next();
            T data = to_remove->data();
            prev_element->next(to_remove->next());
            delete to_remove;
            size_--;
            return data;
        }
    }
    
    T pop_back() {  // Remove the last element
        if (empty())
            throw std::out_of_range("The list is empty!");

        if (size() == 1) {
            return pop_front();
        } else {
            Node* prev_element = circular_iterating(head, size()-2);
            Node* to_remove = prev_element->next();
            T data = to_remove->data();
            prev_element->next(head);
            delete to_remove;
            size_--;
            return data;
        }
    }
    
    T pop_front() {  // Remove the first element
        if (empty())
            throw std::out_of_range("The list is empty!");

        T data = head->data();
        if (size() == 1) {
            head = nullptr;
        } else {
            head = head->next();
            Node* last_element = circular_iterating(head, size()-1);
            last_element->next(head);
        }
        size_--;
        return data;
    }
    
    void remove(const T& data) {  // Remove the first appearence of data
        if (empty())
            throw std::out_of_range("The list is empty!");

        Node* current = head;
        for (std::size_t i = 0; i < size(); i++) {
            if (current->data == data) {
                pop(i);
                break;
            }
            current = current->next();
        }
    }

    bool empty() const {  // Verify emptiness
        return !(size_);
    }
    
    bool contains(const T& data) {  // Verify existence of data
        Node* current = head;
        for (std::size_t i = 0; i < size(); i++) {
            if (current->data() == data)
                return true;
            current = current->next();
        }
    }
    
    std::size_t find(const T& data) const {  // Find the position of data
        Node* current = head;
        std::size_t index = size();
        for (std::size_t i = 0; i < size(); i++) {
            if (current->data() == data) {
                index = i;
                break;
            }
            current = current->next();
        }
        return index;
    }

    std::size_t size() const {  // Returns the size
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data) {data_ = data;}  // Explicit constructor

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* new_next) {
            next_ = new_next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* circular_iterating(Node* head, std::size_t index) {
        bool reverse_flux;

        if (index > (size()/2 + 1))
            reverse_flux = true;
        else
            reverse_flux = false;

        Node* current = head;

        if (reverse_flux) {
            for (std::size_t i = 0; i < size() - index; i++) {
                current = current->next();
            }
        } else {
            for (std::size_t i = 0; i < index; i++) {
                current = current->next();
            }
        }
        return current;
    }

    Node* head;
    std::size_t size_;
};


}  // namespace structures

#endif