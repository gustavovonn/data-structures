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

    void clear();  // Clear the elements and free memory

    void push_back(const T& data) {  // Insert data in last position
        Node* new_element = new Node(data);  // Locating memory
    
        if (new_element == nullptr)
            throw std::out_of_range("No memory available!");
        
        
    }
    void push_front(const T& data);  // Insert data in the first index
    void insert(const T& data, std::size_t index);  // Insert data in index
    void insert_sorted(const T& data);  // Insert data respecting order

    T pop(std::size_t index);  // Remove element in index
    T pop_back();  // Remove the last element
    T pop_front();  // Remove the first element
    void remove(const T& data);  // Remove first appearence of data

    bool empty();  // Verify emptiness
    bool contains(const T& data) const;  // Verify existence of data

    T& at(std::size_t index);  // Return address of element at index
    const T& at(std::size_t index) const;  // Const version of above

    std::size_t find(const T& data) const;  // Find the index of data

    std::size_t size() const;  // Returns the size of the list

 private:
    class Node {
     public:
        explicit Node(const T& data);  // Explicit construtctor
        Node(const T& data, Node* next);  // Constructor with next pointer
        Node(const T& data, Node* prev, Node* next);  // Complete constructor
    
        T& data();  // Return the address of the data in the node
        const T& data() const;  // Const version
    
        Node* prev();  // Previous node getter
        const Node* prev() const;  // Const version
    
        void prev(Node* node);  // Previous node setter
    
        Node* next();  // Next node getter
        const Node* next() const;  // Const version

        void next(Node* node);  // Next node setter
    
     private:
        T data_;  // Respective data
        Node* prev_;  // Pointer to the previous node
        Node* next_;  // Pointer to the next node
    };

    Node* head;  // First element
    std::size_t size_;  // List size

}

}  // namespace structures
