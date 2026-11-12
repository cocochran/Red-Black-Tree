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
        Node<T>* root;
        RedBlackTree();
        RedBlackTree(const RedBlackTree&);
        RedBlackTree(Node<T>*);
        RedBlackTree(T);
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
        void fixViolation(Node* root, Node* node);
        Node<T>* find(Node<T>*, T);
        void insert(Node<T>* root, Node<T>* node);
        void remove(Node<T>* root, Node<T>* node);
        void inorder(Node<T>*, std::vector<T>&) const;

};

/* -------- CONSTRUCTORS --------*/

/*
    Empty constructor.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr), numberOfNodes(0), heightOfTree(0) {}

/*
    Copy constructor.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &copy) {
    // Implementation of copy constructor
}

/*
    Constructor, inserting just the root.using pointer.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(Node<T> *r) : root(nullptr), numberOfNodes(0), heightOfTree(0) {
    root = r;
}

/*
    Constructor, inserting just the root.using provided node data.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(T data) : root(nullptr), numberOfNodes(0), heightOfTree(0) {
    
}

/* -------- SIZE FUNCTION --------*/
/*
    Returns the number of nodes in the tree.
*/
template<typename T>
int RedBlackTree<T>::size(){ return this->numberOfNodes; }

/* -------- INSERT FUNCTIONS --------*/

/*
    Helper function to insert a node into the table.
*/
template<typename T>
void RedBlackTree<T>::insert(Node<T>* root, Node<T>* node){
    Node<T>* current = root;
    if (current == nullptr) {
        current = node;
        return;
    }
    if (root->data >= node->data) current = node->left;
    else current = node->right;
    insert(current, node);
    fixViolation(root, node);
}

/*
    Uses helper function to insert an already created node with a particular address.
*/
template<typename T>
void RedBlackTree<T>::insert(Node<T>* node){
    insert(root, node);
    numberOfNodes++;
    heightOfTree = findHeight();
}

/*
    Uses insert(Node<T>*) in order to insert a node into the tree given only data content.
*/
template<typename T>
void RedBlackTree<T>::insert(T data) {
    Node node = Node(data);
    insert(node);
    size++;
}



/* -------- REMOVE FUNCTIONS --------*/

/*
    Helper function to remove and delete a node.
    Node-to-delete's address must be the address of the node in the tree.
*/
template<typename T>
void RedBlackTree<T>::remove(Node<T>* root, Node<T>* node){
    //needs implementation
    fixViolation(root, node);
    delete node;
}

/*
    Uses helper function to delete node with particular address.
*/
template<typename T>
void RedBlackTree<T>::remove(Node<T>* node){
    remove(root, node);
    numberOfNodes--;
    heightOfTree = findHeight();
}

/*
    Uses remove(Node<T>*) in order to delete node from tree given only its data content.
*/
template<typename T>
void RedBlackTree<T>::remove(T data){
    Node<T>* node = find(data);
    remove(node);
}



/* -------- ARRAY FUNCTION --------*/

/*
    Returns a vector with the data of each node in the tree in ascending order.
*/
template<typename T>
std::vector<T> RedBlackTree<T>::getVector(){
    std::vector<T> result;
    inorder(root, result);
    return result; // elements in sorted order
}

/*
    Helper function to get a vector with all node data in order.
*/
template<typename T>
void RedBlackTree<T>::inorder(Node<T>* node, std::vector<T>& out) const {
    if (node == nullptr) return;
    inorder(node->left, out);   // smaller values first
    out.push_back(node->data);  // then this node
    inorder(node->right, out);  // then larger values
}


/* -------- FIND FUNCTIONS --------*/

/*
    Helper function to do a traditional binary search.
*/
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

/*
    Utilize the helper to find the node's address.
    If node is not in tree, return nullptr.
*/
template<typename T>
Node<T>* RedBlackTree<T>::find(T data){
        return find(this->root, data);
}


/* -------- DEINITIALIZE FUNCTION --------*/
/*
    Deinitializes the tree, frees up memory previously utilized by the nodes.
    No nodes will be able to be accessed after deinitialization.
*/
template<typename T>
void RedBlackTree<T>::deinitialize() {
    
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