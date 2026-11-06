#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

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
        Node *root;
        RedBlackTree();
        RedBlackTree(const RedBlackTree &copy);
        RedBlackTree(Node *root);
        void insert(int data);
        void remove(int data);
        void inorder();
        void deinitialize();
};
#endif