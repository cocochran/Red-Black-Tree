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
        ~RedBlackTree();
        int size();
        int height();

        void insert(T);
        void insert(Node<T>*);

        void remove(T);
        void remove(Node<T>*);

        std::vector<T> getVector();
        Node<T>* find(T);
        
    private:
        int numberOfNodes;

        void leftRotate(Node<T>*&, Node<T>*&);
        void rightRotate(Node<T>*&, Node<T>*&);
        Node<T>* find(Node<T>*, T);
        void insert(Node<T>*, Node<T>*);
        void remove(Node<T>*, Node<T>*&);
        void transplant(Node<T>*&, Node<T>*, Node<T>*);
        void insertFixup(Node<T>*, Node<T>*);
        void removeFixup(Node<T>*&, Node<T>*, Node<T>*);
        void inorder(Node<T>*, std::vector<T>&) const;
        Node<T>* getSuccessor(Node<T>*);

        static Node<T>* copySubtree(const Node<T>*, Node<T>*);
        static int countNodes(const Node<T>*);
        static int subtreeHeight(const Node<T>*);
        void deinitialize();

iolation
};

/* -------- CONSTRUCTORS --------*/

/*
    Empty constructor.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr), numberOfNodes(0) {}

/*
    Copy constructor. Performs a deep copy so the two trees share no nodes.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &copy)
    : root(copySubtree(copy.root, nullptr)),
      numberOfNodes(copy.numberOfNodes),

/*
    Constructor, using an existing node as the root.
    The root is recolored black, as required by red-black tree rules.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(Node<T> *r) : root(r), numberOfNodes(0) {
    if (root == nullptr) return;
    root->parent = nullptr;
    root->color = BLACK;
    numberOfNodes = countNodes(root);
}

/*
    Constructor, creating a black root node from the provided data.
*/
template<typename T>
RedBlackTree<T>::RedBlackTree(T data)
    : root(new Node<T>(data, BLACK)), numberOfNodes(1) {}

/* -------- DESTRUCTOR --------*/

/*
    Destructor. Frees every node in the tree via deinitialize().
*/
template<typename T>
RedBlackTree<T>::~RedBlackTree() { deinitialize(); }

/* -------- MISC. HELPERS --------*/

/*
    Recursively deep-copies a subtree, preserving colors and wiring parent pointers.
*/
template<typename T>
Node<T>* RedBlackTree<T>::copySubtree(const Node<T>* source, Node<T>* parent) {
    if (source == nullptr) return nullptr;
    Node<T>* node = new Node<T>(source->data, source->color);
    node->parent = parent;
    node->left = copySubtree(source->left, node);
    node->right = copySubtree(source->right, node);
    return node;
}

/*
    Counts the nodes in a subtree.
*/
template<typename T>
int RedBlackTree<T>::countNodes(const Node<T>* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

/*
    Height of a subtree, counted in nodes (empty = 0, single node = 1).
*/
template<typename T>
int RedBlackTree<T>::subtreeHeight(const Node<T>* node) {
    if (node == nullptr) return 0;
    int leftSubtreeHeight = subtreeHeight(node->left);
    int rightSubtreeHeight = subtreeHeight(node->right);
    return 1 + (leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight : rightSubtreeHeight);
}

template<typename T>
Node<T>* RedBlackTree<T>::getSuccessor(Node<T>* curr){
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr){
        curr = curr->left;
    }
    return curr;
}

/* -------- SIZE FUNCTIONS --------*/
/*
    Returns the number of nodes in the tree.
*/
template<typename T>
int RedBlackTree<T>::size(){ return this->numberOfNodes; }

template<typename T>
int RedBlackTree<T>::height() {
    if (this->root == nullptr) return 0;
    return subtreeHeight(this->root);
}

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
}

/*
    Uses insert(Node<T>*) in order to insert a node into the tree given only data content.
*/
template<typename T>
void RedBlackTree<T>::insert(T data) {
    Node node = Node(data);
    insert(node);
    numberOfNodes++;
}



/* -------- REMOVE FUNCTIONS --------*/

/*
    Node-to-delete's address must be the address of the node in the tree.
*/
template<typename T>
void RedBlackTree<T>::remove(Node<T>* root, Node<T>*& node){
    if (node == nullptr) return;

    Color nodeColor = node->color;
    Node<T>* x = nullptr;        // node that moves into the removed spot (may be nullptr)
    Node<T>* xParent = nullptr;  // x's parent, tracked separately since x may be nullptr

    // Node has no children
    if (node->left == nullptr && node->right == nullptr){
        xParent = node->parent;
        if (this->root == node){
            this->root = nullptr;
        }
        //Node is a left child
        else if (node == node->parent->left){
            node->parent->left = nullptr;
        }
        //Node is a right child
        else {
            node->parent->right = nullptr;
        }
    }

    // Node has one child
    else if ((node->right != nullptr) != (node->left != nullptr)){
        if (node->left != nullptr){
            if (this->root == node){
                this->root = node->left;
            }
            //Node is a left child
            else if (node == node->parent->left){
                node->parent->left = node->left;
            }
            //Node is a right child
            else {
                node->parent->right = node->left;
            }

            node->left->parent = node->parent;
            x = node->left;

        } else {
            if (this->root == node){
                this->root = node->right;
            }
            //Node is a left child
            else if (node == node->parent->left){
                node->parent->left = node->right;
            }
            //Node is a right child
            else {
                node->parent->right = node->right;
            }

            node->right->parent = node->parent;
            x = node->right;
        }

        xParent = node->parent;
    }

    // Node has two children
    else{
        Node<T>* successor = getSuccessor(node);
        nodeColor = successor->color;   // successor is the node that actually leaves its spot
        x = successor->right;           // successor never has a left child

        // Detach successor from its old spot (unless it's node's direct right child)
        if (successor->parent == node){
            xParent = successor;
        } else {
            xParent = successor->parent;
            successor->parent->left = successor->right;
            if (successor->right != nullptr) successor->right->parent = successor->parent;
            successor->right = node->right;
            successor->right->parent = successor;
        }

        // Put successor in node's spot
        successor->parent = node->parent;
        if (this->root == node){
            this->root = successor;
        } else if (node == node->parent->left){
            node->parent->left = successor;
        } else {
            node->parent->right = successor;
        }

        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }

    delete node;
    node = nullptr;

    if (nodeColor == BLACK) removeFixup(this->root, x, xParent);
}

/*
    Uses helper function to delete node with particular address.
*/
template<typename T>
void RedBlackTree<T>::remove(Node<T>* node){
    remove(root, node);
    numberOfNodes--;
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
    // Remove every node except the root. Rotations during removal can change
    // which node is the root, so re-check the current root on each pass
    // instead of iterating over a snapshot of the nodes.
    while (root != nullptr && (root->left != nullptr || root->right != nullptr)) {
        Node<T>* child = (root->left != nullptr) ? root->left : root->right;
        remove(child);
    }

    // Only the root is left; free it directly.
    delete root;
    root = nullptr;
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