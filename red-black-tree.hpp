#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <vector>


enum Color { RED, BLACK };

template<typename T>
struct Node{
    T data;
    Color color;
    Node *left, *right, *parent;
    Node(const T& data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(const T& data, Color color) : data(data), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class RedBlackTree {
    public:
        Node<T> *root;
        RedBlackTree();
        RedBlackTree(const RedBlackTree&);
        RedBlackTree(Node<T>*);
        int size();
        int height();

        void insert(T);
        void insert(Node<T>*);

        void remove(T);
        void remove(Node<T>*);

        std::vector<T> getVector();
        Node<T>* find(T);
        void deinitialize();
        
    private:
        int numberOfNodes;
        int heightOfTree;

        void leftRotate(Node<T>*&, Node<T>*&);
        int findHeight();
        void rightRotate(Node<T>*&, Node<T>*&);
        void fixViolation(Node<T>*&, Node<T>*&);
        Node<T>* find(Node<T>*, T);
        void inorder(Node<T>*, std::vector<T>&) const;

};

/* -------- CONSTRUCTORS --------*/
template<typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr), numberOfNodes(0), heightOfTree(0) {}

template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &copy) {
    // Implementation of copy constructor
}
template<typename T>
RedBlackTree<T>::RedBlackTree(Node<T> *root) {
    // Implementation of constructor with root node
}

/* -------- SIZE FUNCTION --------*/
template<typename T>
int RedBlackTree<T>::size(){ return this->numberOfNodes; }

/* -------- INSERT FUNCTIONS --------*/
template<typename T>
void RedBlackTree<T>::insert(T data) {
    // Implementation of insert function
}
template<typename T>
void RedBlackTree<T>::insert(Node<T>* node){

}


/* -------- REMOVE FUNCTIONS --------*/
template<typename T>
void RedBlackTree<T>::remove(T data){

}

template<typename T>
void RedBlackTree<T>::remove(Node<T>* node){

}


/* -------- ARRAY FUNCTION --------*/
template<typename T>
std::vector<T> RedBlackTree<T>::getVector(){
    std::vector<T> result;
    inorder(root, result);
    return result; // elements in sorted order
}

template<typename T>
void RedBlackTree<T>::inorder(Node<T>* node, std::vector<T>& out) const {
    if (node == nullptr) return;
    inorder(node->left, out);   // smaller values first
    out.push_back(node->data);  // then this node
    inorder(node->right, out);  // then larger values
}


/* -------- FIND FUNCTIONS --------*/
template<typename T>
Node<T>* RedBlackTree<T>::find(Node<T>* root, T data) {
    Node<T>* current = root;
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
Node<T>* RedBlackTree<T>::find(T data){
        return find(this->root, data);
}


/* -------- DEINITIALIZE FUNCTION --------*/
template<typename T>
void RedBlackTree<T>::deinitialize() {
    // Implementation of deinitialization
    //For each node, delete the node and set its pointer to nullptr, freeing up memory and preventing memory leaks.
}


/* -------- ROTATION FUNCTIONS --------*/
template<typename T>
void RedBlackTree<T>::leftRotate(Node<T> *&root, Node<T> *&x) {
    if (x == nullptr || x->right == nullptr) return;

    Node<T>* y = x->right;
    x->right = y->left;

    if (y->left) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

template<typename T>
void RedBlackTree<T>::rightRotate(Node<T>*& root, Node<T>*& x) {
    if (x == nullptr || x->left == nullptr) return;

    Node<T>* y = x->left;
    x->left = y->right;

    if (y->right) y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    y->right = x;
    x->parent = y;
}

#endif