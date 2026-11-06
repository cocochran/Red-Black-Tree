enum Color { RED, BLACK };

struct Node{
    int data;
    Color color;
    Node *left, *right, *parent;
    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int data, Color color) : data(data), color(color), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
    public:
        enum Color { RED, BLACK };
        Node *root;
        RedBlackTree();
        RedBlackTree(const RedBlackTree &copy);
        RedBlackTree(Node *root);
        void insert(int data);
        void remove(int data);
        void inorder();
        int* find(int data);
        int* find(Node* root, int data);
        void deinitialize();
};


RedBlackTree::RedBlackTree(const RedBlackTree &copy) {
    // Implementation of copy constructor
}

RedBlackTree::RedBlackTree(Node *root) {
    // Implementation of constructor with root node
}

void RedBlackTree::insert(int data) {
    // Implementation of insert function
}

void RedBlackTree::remove(int data) {
    // Implementation of remove function
}

void RedBlackTree::inorder() {
    // Implementation of inorder traversal
}

Node* RedBlackTree::find(Node* root, int data) {
    Node* current = root;
    if (current == nullptr) {
        return nullptr; // Base case: node not found
    }

    if (data == current->data) {
        return *current; // Node found, return pointer to data
    } else if (data < current->data) {
        return find(current->left, data); // Search in the left subtree
    } else {
        return find(current->right, data); // Search in the right subtree
    }

    return nullptr; // Placeholder return
}
void RedBlackTree::deinitialize() {
    // Implementation of deinitialization
    //For each node, delete the node and set its pointer to nullptr, freeing up memory and preventing memory leaks.
}