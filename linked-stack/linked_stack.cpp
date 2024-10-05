// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>

namespace structures {

template<typename T>

class LinkedStack {
 public:
    LinkedStack() {  // Constructor
        top_ = nullptr;  // Init with no element
        size_ = 0;
    }

    ~LinkedStack() {  // Destructor
        clear();  // Clear/destroy the stack
    }

    void clear() {  // Clear stack
        Node* element_below;  // Previous element in the stack
        while (top_ != nullptr) {  // Travel to the bottom
            element_below = top_->next();  // Below element
            delete top_;  // Free element memory
            top_ = element_below;  // Att to the new top
        }
        size_ = 0;  // Zero
    }
    void push(const T& data) {  // Push new element
        Node* new_element = new Node(data, top_);  // Allocate memory

        if (new_element == nullptr)
            throw std::out_of_range("Without memory!");

        top_ = new_element;  // New top
        size_++;
    }

    T pop() {  // Remove element
        if (empty())
            throw std::out_of_range("The stack is empty!");

        T data = top();  // top() returns data in the last node

        Node* element_below = top_->next();  // Previous element

        delete top_;  // Remove past top

        top_ = element_below;  // Att new top

        size_--;

        return data;
    }

    T& top() const {  // Data in the top (by reference)
        if (empty())
            throw std::out_of_range("The stack is empty");
        return top_->data();  // Return top element data
    }

    bool empty() const {  // Verify if stack is empty
        return !(size_);
    }

    std::size_t size() const {  // Return the stack size
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data) {data_ = data;}  // Constructor with data

        Node(const T& data, Node* next) {  // Construtor data + next pointer
            data_ = data;
            next_ = next;
        }

        T& data() {  // Getter (by reference)
            return data_;
        }

        const T& data() const {  // Getter (by reference) constant
            return data_;
        }

        Node* next() {  // Gets the next element in stack
            return next_;
        }

        const Node* next() const {  // Gets the next element (constant)
            return next_;
        }

        void next(Node* next) {  // Sets new next node pointer
            next_ = next;
        }

     private:
        T data_;  // Generic data attribute
        Node* next_;  // Next element/node pointer
    };

    Node* top_;  // The element in the top (stack pointer)
    std::size_t size_;  // Size of the stack in elements
};
}  // namespace structures
