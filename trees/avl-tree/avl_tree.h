// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>


/* Adelson-Velskii/Landis */



/* AVL properties/particularities

-> Each node has your height attribute to after we verify the balance
-> Its AVL balanced if the difference between the two subtress are
in max. of 1.
-> All nodes may have this AVL property about the heights difference
between subtress to the tree be considered an AVL 

*/

/* Insertion

The beginning is the same as in a common Search Tree:
-> Explore the tree to find the right position to insert;
-> Allocate memory and insert the node/data in the tree.

Differently from the Search Tree, in the AVL after a insert, we
need to verify the balance to confirm that the AVL property was
not losted. So, the next step is:
->

*/







#include "array_list.h"  // Array list local import

namespace structures {

template<typename T>
class AVLTree {
 public:
    ~AVLTree();  // Destructor

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;  // Explore the subtree and verify the height

    ArrayList<T> pre_order() const;

    ArrayLIst<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        Node(const T& data);
    
        T data;  // Data
        int height_;  // Height of the subtree started here
        Node* left;  // Left child pointer
        Node* right;  // Right child pointer

        void insert(const T& data_);
    
        bool remove(const T& data_);
    
        bool contains(const T& data_):
    
        void update_height();
    
        Node* simple_left();
    
        Node* simple_right();
    
        Node* double_left();
    
        Node* double_right();
    
        void pre_order(ArrayList<T>& v) const;
    
        void in_order(ArrayList<T>& v) const;
    
        void post_order(ArrayList<T>& v) const;
    
        int height() {  // Height getter
            return height_;
        }
    };

    // AVLTree attributes
    Node* root;
    std::size_t size_;
};

}  // namespace structure

