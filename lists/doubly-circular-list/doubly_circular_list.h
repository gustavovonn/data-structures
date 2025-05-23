#include <iostream>

namespace structures {


template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList() {  // Constructor
        size_ = 0;
        head = nullptr;
    }

    ~DoublyCircularList() {  // Destructor
        clear();
    }

    void clear() {  // Clear the elements and free memory
        if (empty())
            throw std::out_of_range("The list is empty!");

        while(!(empty())) {
            pop_front();
        }
    }

    void push_back(const T& data) {  // Insert data in last position
        Node* new_element = new Node(data, nullptr);  // Locating memory
    
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");
        
        Node* element = head;  // First element

        for(std::size_t i = 0; i < size()-1; i++) {
            element = element->next();  // Pass thru elements
        }

        element->next(new_element);  // New element is the next of the pv. last
    
        new_element->prev(element);
    
        new_element->next(head);  // Circularity
    
        size_++;
    }

    void push_front(const T& data) {  // Insert data in the first index
        Node* new_element = new Node(data);
    
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");

        if (empty()) {
            head = new_element;
            head->prev(head);
            head->next(head);
        } else {
            new_element->next(head);
            new_element->prev(head->prev());  // Linkin the tail
            new_element->prev()->next(new_element);
            head->prev(new_element);  // Linkin the old head
            head = new_element;
        }
        size_++;
    }

    void insert(const T& data, std::size_t index) {  // Insert data in index
        if (index > size() || index < 0)
            throw std::out_of_range("Invalid index!");
        
        Node* new_element = new Node(data);
    
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");
            
        if (index == 0) {
            push_front(data);
        } else if (index == size()) {
            push_back(data);
        } else {
            Node* prev_element = circular_iterating(head, index-1);
    
            new_element->prev(prev_element);  // Linkin the left part
            new_element->next(prev_element->next());  // Linkin the right part

            new_element->next()->prev(new_element);
            new_element->prev()->next(new_element);

            size_++;
        }
    }
    void insert_sorted(const T& data) {  // Insert data respecting order
        Node* new_element = new Node(data);

        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");
        
        std::size_t index = size();

        Node* element = head;

        for(std::size_t i = 0; i < size()-1; i++) {
            if (element->data > data)
                index = i;
            element = element->next();
        }
        insert(data, index);
    }

    T pop(std::size_t index) {  // Remove element in index
        if (empty())
            throw std::out_of_range("The list is empty!");

        if (index == 0) {
            return pop_front();
        } else if (index == size()-1) {
            return pop_back();
        } else {
            Node* to_remove = circular_iterating(head, index);

            to_remove->prev()->next(to_remove->next());
            to_remove->next()->prev(to_remove->prev());

            T data = to_remove->data();
            delete to_remove;
            size_--;
            return data;
        }
    }

    T pop_back() {  // Remove the last element
        if (empty())
            throw std::out_of_range("The list is empty!");

        Node* to_remove;

        if (size() == 1) {
            to_remove = head;
        } else {
            to_remove = head->prev();  // Tail
            to_remove->prev()->next(head);
            head->prev(to_remove->prev());
        }
        T data = to_remove->data();
        delete to_remove;
        size_--;
        return data;
    }

    T pop_front() {  // Remove the first element
        if (empty())
            throw std::out_of_range("The list is empty!");
    
        Node* to_remove = head;
        T data = to_remove->data();

        if (size() == 1) {
            to_remove->next(nullptr);
            to_remove->prev(nullptr);
        } else {
            head->next()->prev(head->prev());
            head->prev()->next(head->next());
        }

        delete to_remove;
        size_--;
        return data;
    }

    void remove(const T& data) {  // Remove first appearence of data
        if(empty())
            throw std::out_of_range("The list is empty!");
            
        Node* element = head;

        for(std::size_t i = 0; i < size()-1; i++) {
            if (element->data() == data)
                pop(i);
            element = element->next();
        }
    }

    bool empty() {  // Verify emptiness
        return !(size_);
    }

    bool contains(const T& data) const {  // Verify existence of data
        if (empty()) {
            return false;
        } else {
            Node* element = head;
            for (std::size_t i = 0; i < size()-1; i++) {
                if (element->data() == data)
                    return true;
                element = element->next();
            }
            return false;
        }
    }

    T& at(std::size_t index) {  // Return address of element at index
        if (index >= size() || index < 0)
            throw std::out_of_range("Index out of range!");
        
        Node* element = circular_iterating(head, index);

        return element->data();
    }

    const T& at(std::size_t index) const {  // Const version of above
        if (index >= size() || index < 0)
            throw std::out_of_range("Index out of range!");
        
        Node* element = circular_iterating(head, index);

        return element->data();    
    }

    std::size_t find(const T& data) const {  // Find the index of data
        if (empty())
            throw std::out_of_range("The list is empty!");
        
        Node* element = head;
        for(std::size_t i = 0; i < size()-1; i++) {
            if (element->data() == data)
                return i;
            element = element->next();
        }
        return size();  // Default output if doesn't find
    }

    std::size_t size() const {  ;  // Returns the size of the list
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data);  // Explicit construtctor

        Node(const T& data, Node* next) {  // Constructor with next pointer
            data_ = data;
            next_ = next;
        }

        Node(const T& data, Node* prev, Node* next) {  // Complete constructor
            data_ = data;
            prev_ = prev;
            next_ = next;
        }
    
        T& data() {  // Return the address of the data in the node
            return &data;
        }

        const T& data() const {  // Const version
            return &data;
        }
    
        Node* prev() {  // Previous node getter
            return prev_;
        }

        const Node* prev() const {  // Const version
            return prev_;
        }
    
        void prev(Node* node) {  // Previous node setter
            prev_ = node;
        }
    
        Node* next() {  // Next node getter
            return next_;
        }

        const Node* next() const {  // Const version
            return next_;
        }

        void next(Node* node) {  // Next node setter
            next_ = node;
        }
    
        Node* circular_iterating(Node* head, std::size_t index) {
            bool reverse_flux;

            if (index > (size()/2 + 1))
                reverse_flux = true;
            else
                reverse_flux = false;

            Node* element = head;
            if (reverse_flux) {  // If its easier to run thru the previous
                for(std::size_t i = 0; i < size() - index; i++) {
                    element = element->prev();
                }
            } else {
                for(std::size_t i = 0; i < index; i++) {
                    element = element->next();
                }
            }
            return element;
        }


     private:
        T data_;  // Respective data
        Node* prev_;  // Pointer to the previous node
        Node* next_;  // Pointer to the next node
    };

    Node* head;  // First element
    std::size_t size_;  // List size

};

}  // namespace structures
