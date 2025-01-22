// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>

#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
    BinaryTree();  // Constructor
    ~BinaryTree();  // Destructor

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data_) {  // Node constructor
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;  // Data stored in the node
        Node* left;  // Pointer to the left son
        Node* right;  // Pointer to the right son

        void insert(const T& data_) {
            if (data_ < data) {  // Key is smaller than the current node
                if (left == nullptr) {  // Doesn't have a left son
                    Node* new_node = new Node(data_);
                    if (new_node == nullptr)
                        throw std::out_of_range("No memory available!");
                    left = new_node;
                } else {  // Already had, continue handling by the left
                    left->insert(data_);
                }
            } else {  // Key is bigger than the current node
                if (right == nullptr) {  // Doesn't have a right son
                    Node* new_node = new Node(data_);
                    if (new_node == nullptr)
                        throw std::out_of_range("No memory available!");
                    right = new_node;
                } else {  // Already had, continue handling by the right
                    right->insert(data_);
                }
            }
        }

/* Cases of remove when the node:
1. Dont have childs
    -> The node is removed directly. Free the memory and decrement the size

2. Have one child
    -> The left or right child turns into the child of the 
    father of the node to be removed

3. Have two childs
    -> Exchange the key of the node to be removed for the smallest
    key in the right subtree

*/
        bool remove(const T& data_, Node* parent) {
            if (data_ < data) {
                if (left != nullptr) {
                    return left->remove(data_, this);
                }
                return false;
            } else if (data_ > data) {
                if (right != nullptr) {
                    return right->remove(data_, this);
                }
                return false;
            } else {  // Data finded
                if (left != nullptr && right != nullptr) {  // 2 childs
                    Node* aux = right;

                    // Smallest of the right subtree:
                    while (aux->left != nullptr)
                        aux = aux->left;

                    data = aux->data;
                    return right->remove(aux->data, this);
                } else {  // 1 or 0 childs
                    // Choose the child, if theres one
                    Node* temp = (left != nullptr) ? left : right;

                    if (temp != nullptr) {  // 1 child
                        data = temp->data;
                        left = temp->left;
                        right = temp->right;
                        delete temp;
                    } else {  // Zero child (leaf case)
                        if (parent != nullptr) {
                            if (parent->left == this) {  // A left leaf
                                parent->left = nullptr;
                            } else if (parent->right == this) {  // A right leaf
                                parent->right = nullptr;
                            }
                        }
                        delete this;
                        return true;
                    }
                    return true;
                }
            }
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);  // Put the root/father data (depends of context)

            if (left != nullptr) {  // Puts the left sons
                left->pre_order(v);
            }

            if (right != nullptr) {  // Puts the right sons
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }

            v.push_back(data);

            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }

            if (right != nullptr) {
                right->post_order(v);
            }

            v.push_back(data);
        }

        Node* min_node(Node* node) {
            Node* current_node = node;
            while (current_node->left != nullptr) {
                current_node = current_node->left;
            }
            return current_node;
        }
    };

    Node* root;  // Tree root
    std::size_t size_;  // Elements

    void clear(Node* node) {  // To use in the destructor
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

}  // namespace structures



template<typename T>
structures::BinaryTree<T>::BinaryTree() {  // Default initialization
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    clear(root);
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        Node* new_node = new Node(data);

        if (new_node == nullptr)
            throw std::out_of_range("No memory available!");

        root = new_node;

    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty())  // Verify if theres something to remove
        throw std::out_of_range("The tree is empty");

    if (root->remove(data, root))
        size_--;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

// These methods below only handles the initial point to the route
// Actually, is the methods defineds in the Node class that brings the data

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->pre_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> elements;
    if (root != nullptr) {
        root->in_order(elements);
    }
    return elements;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> elements;
    if (root != nullptr) {
        root->post_order(elements);
    }
    return elements;
}
