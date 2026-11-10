#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP



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
        RedBlackTree(const RedBlackTree &copy);
        RedBlackTree(Node<T> *root);
        void insert(int data);
        void insert(Node<T>* node);
        void remove(int data);
        void remove(Node<T>* )
        void inorder();
        Node* find(int data);
        void deinitialize();
    private:
        void leftRotate(Node<T> *&root, Node<T> *&x);
        void rightRotate(Node<T> *&root, Node<T> *&x);
        void fixViolation(Node<T> *&root, Node<T> *&x);
        Node* find(Node<T>* root, int data);
};
#endif