// Дебажим код, сгенерированный ChatGPT

#include <iostream>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    // Изначально пропущенная ChatGPT часть
    ~TreeNode() {
        delete left;
        delete right;
    }
};

int modify_val(int val) {
    if (val == 0) {
        return 100 / val;
    }

    return val;
}

class BinaryTree {
private:
    TreeNode* root;

    // Recursive function to insert a new node
    TreeNode* insertRecursive(TreeNode* current, int value) {
        if (current == nullptr) {
            // ищем с гдб, где происходит FPE.
            // return new TreeNode(modify_val(value));
            return new TreeNode(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }

        // If the value is already in the tree, do nothing
        return current;
    }

public:
    BinaryTree() : root(nullptr) {}

    // Public method to insert a new node
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Example: In-order traversal (left, root, right)
    void inOrderTraversal(TreeNode* current) {
        if (current != nullptr) {
            inOrderTraversal(current->left);
            std::cout << current->data << " ";
            inOrderTraversal(current->right);
        }
    }

    // Public method to perform in-order traversal starting from the root
    void inOrderTraversal() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    // Изначально пропущенная ChatGPT часть
    ~BinaryTree() {
        delete root;
    }
};

int main() {
    BinaryTree myTree;

    int val;
    while(std::cin >> val) {
        myTree.insert(val);
    }

    // Perform in-order traversal
    std::cout << "In-order traversal: ";
    myTree.inOrderTraversal();

    return 0;
}

