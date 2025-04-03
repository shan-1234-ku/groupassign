#include <iostream>

using namespace std;

// Node structure for the binary tree
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }
};

// Binary Tree class
class BinaryTree
{
public:
    Node *root;

    BinaryTree() : root(nullptr) {}

    // Destructor to prevent memory leaks
    ~BinaryTree()
    {
        destroyTree(root);
    }

    // Helper function to destroy the tree
    void destroyTree(Node *node)
    {
        if (node != nullptr)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Insert function
    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        { // Added check for equality
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Preorder Traversal (Root -> Left -> Right)
    void preorder(Node *node)
    {
        if (node == nullptr)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Inorder Traversal (Left -> Root -> Right)
    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Postorder Traversal (Left -> Right -> Root)
    void postorder(Node *node)
    {
        if (node == nullptr)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Search function
    bool search(Node *node, int key)
    {
        if (node == nullptr)
            return false;
        if (node->data == key)
            return true;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    // Finding the minimum value node
    Node *findMin(Node *node)
    {
        if (node == nullptr)
            return nullptr;

        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Deleting a node from the tree
    Node *delNode(Node *node, int key)
    {
        if (node == nullptr)
            return nullptr;

        if (key < node->data)
        {
            node->left = delNode(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = delNode(node->right, key);
        }
        else
        {
            // Case 1: No child
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            Node *temp = findMin(node->right);
            if (temp == nullptr)
                return nullptr; // Added safety check
            node->data = temp->data;
            node->right = delNode(node->right, temp->data);
        }
        return node;
    }

    // Added helper methods for public interface
    void insert(int value)
    {
        root = insert(root, value);
    }

    void remove(int key)
    {
        root = delNode(root, key);
    }

    bool search(int key)
    {
        return search(root, key);
    }
};

int main()
{
    BinaryTree tree;

    // Inserting nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Preorder Traversal: ";
    tree.preorder(tree.root);
    cout << endl;

    cout << "Inorder Traversal: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "Postorder Traversal: ";
    tree.postorder(tree.root);
    cout << endl;

    // Searching for a node
    int key = 40;
    cout << "Searching for " << key << ": " << (tree.search(key) ? "Found" : "Not Found") << endl;

    // Deleting a node
    cout << "Deleting node " << key << "..." << endl;
    tree.remove(key);

    cout << "Inorder Traversal after deletion: ";
    tree.inorder(tree.root);
    cout << endl;

    return 0;
}