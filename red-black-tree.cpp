#include "red-black-tree.hpp"

template<typename T>
RedBlackTree::RedBlackTree(const RedBlackTree &copy) {
    // Implementation of copy constructor
}

template<typename T>
RedBlackTree::RedBlackTree(Node<T> *root) {
    // Implementation of constructor with root node
}

template<typename T>
void RedBlackTree<T>::insert(int data) {
    // Implementation of insert function
}

template<typename T>
void RedBlackTree::insert(Node* node);

void RedBlackTree<T>::remove(int data);

template<typename T>
void RedBlackTree<T>::remove(Node* node);

template<typename T>
void RedBlackTree<T>::inorder() {
    // Implementation of inorder traversal
}

template<typename T>
Node<T>* RedBlackTree<T>::find(Node<T>* root, int data) {
    Node* current = root;/ Implementation of remove function
    if (current == nullptr) {
        return nullptr; // Base case: node not found
    }

    if (data == current->data) {
        return current; // Node found, return pointer to data
    } else if (data < current->data) {
        return find(current->left, data); // Search in the left subtree
    } else {
        return find(current->right, data); // Search in the right subtree
    }
}

template<typename T>
Node* RedBlackTree<T>::find(int data){
        return find(this->root, data);
}

template<typename T>
void RedBlackTree<T>::deinitialize() {
    // Implementation of deinitialization
    //For each node, delete the node and set its pointer to nullptr, freeing up memory and preventing memory leaks.
    
}

template<typename T>
void RedBlackTree<T>::leftRotate(Node *&root, Node *&x) {

}

template<typename T>
void RedBlackTree::rightRotate(Node *&root, Node *&x) {
    if (x == nullptr){
        return;
    }

    if (x->left == nullptr && pt->right == nullptr){
        return;
    }

    Node *y = x->right;
    x->left = y->right;
    y->right = x;
    if (x->parent == nullptr){

    }
    x->parent = y;
}