// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>

namespace structures {

template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() {  // Constructor
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    ~LinkedQueue() {  // Destructor
        clear();  // Clear/destroy queue
    }

    void clear() {  // Clear the queue
        while (!empty()) {  // Dequeue till empty
            dequeue();  // Dequeue
        }
    }

    void enqueue(const T& data) {  // Enqueue elements
        Node* new_element = new Node(data, nullptr);  // Memory allocation

        if (new_element == nullptr)
            throw std::out_of_range("Without memory!");

        if (empty()) {  // If queue empty
            head = new_element;  // New element would be the head
            tail = new_element;  // and the tail in the same time
        } else {
            tail->next(new_element);  // Adresses the new element
            tail = new_element;  // Att the new tail
        }
        size_++;
    }

    T dequeue() {  // Dequeue elements
        if (empty())
            throw std::out_of_range("Queue empty!");
        T data = head->data();  // Element data

        Node* element = head;  // Element to be removed

        if (size() == 1) {  // If had only one element in the queue
            head = nullptr;
            tail = nullptr;
        } else {  // In case the queue have 2 or more elements
            head = head->next();  // Nested in the queue
        }

        delete element;  // Free memory
        size_--;
        return data;
    }

    T& front() const {  // First element
        if (empty())
            throw std::out_of_range("Queue empty!");

        return head->data();  // First element data
    }

    T& back() const {  // Last element
        if (empty())
            throw std::out_of_range("Queue empty!");

        return tail->data();  // Last element data
    }

    bool empty() const {  // Verify queue empty
        return !(size());
    }

    std::size_t size() const {  // Returns queue size
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

    Node* head;  // First node
    Node* tail;  // Last node
    std::size_t size_;  // Size attribute
};

}  // namespace structures
