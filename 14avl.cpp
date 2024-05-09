#include <iostream>
using namespace std;

// AVL Node structure
class AVLNode {
public:
    string word;
    string meaning;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string word, string meaning) {
        this->word = word;
        this->meaning = meaning;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// AVL Tree class
class AVLTree {
public:
    AVLNode* root;

    AVLTree() {
        root = nullptr;
    }

    // Function to get height of a node
    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Function to get balance factor of a node
    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Function to perform right rotation
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    // Function to perform left rotation
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    // Function to insert a node into AVL tree
    AVLNode* insert(AVLNode* node, string word, string meaning) {
        if (node == nullptr)
            return new AVLNode(word, meaning);

        if (word < node->word)
            node->left = insert(node->left, word, meaning);
        else if (word > node->word)
            node->right = insert(node->right, word, meaning);
        else {
            // Word already exists, update the meaning
            node->meaning = meaning;
            return node;
        }

        // Update height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Check balance factor and perform rotations if needed
        int balance = getBalanceFactor(node);

        if (balance > 1 && word < node->left->word)
            return rotateRight(node);

        if (balance < -1 && word > node->right->word)
            return rotateLeft(node);

        if (balance > 1 && word > node->left->word) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && word < node->right->word) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Function to perform inorder traversal (ascending or descending)
    void inorderTraversal(AVLNode* node, bool ascending) {
        if (node == nullptr)
            return;

        if (ascending) {
            inorderTraversal(node->left, ascending);
            cout << node->word << " = " << node->meaning << endl;
            inorderTraversal(node->right, ascending);
        } else {
            inorderTraversal(node->right, ascending);
            cout << node->word << " = " << node->meaning << endl;
            inorderTraversal(node->left, ascending);
        }
    }

    // Function to search for a keyword and count comparisons
    int search(AVLNode* node, string key, int comparisons) {
        if (node == nullptr || node->word == key) {
            if (node != nullptr)
                cout << "Key is present in the tree." << endl;
            return comparisons + 1;
        }

        comparisons++;
        if (key < node->word)
            return search(node->left, key, comparisons);
        else
            return search(node->right, key, comparisons);
    }

    // Function to find the maximum value node (rightmost node)
    AVLNode* findMaxNode(AVLNode* node) {
        if (node == nullptr || node->right == nullptr)
            return node;
        return findMaxNode(node->right);
    }

    // Function to delete a node from AVL tree
    AVLNode* deleteNode(AVLNode* node, string key) {
        if (node == nullptr)
            return node;

        if (key < node->word)
            node->left = deleteNode(node->left, key);
        else if (key > node->word)
            node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                AVLNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                AVLNode* temp = node->left;
                delete node;
                return temp;
            }

            AVLNode* temp = findMaxNode(node->left);
            node->word = temp->word;
            node->meaning = temp->meaning;
            node->left = deleteNode(node->left, temp->word);
        }

        // Update height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Check balance factor and perform rotations if needed
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
};

int main() {
    AVLTree dictionary;
    int choice;
    string word, meaning, key;

    while (true) {
        cout << "\n1. Insert Keyword\n2. Delete Keyword\n3. Display Ascending\n4. Display Descending\n5. Search\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword and meaning: ";
            cin >> word >> meaning;
            dictionary.root = dictionary.insert(dictionary.root, word, meaning);
            cout << "Keyword inserted successfully." << endl;
            break;

        case 2:
            cout << "Enter keyword to delete: ";
            cin >> word;
            dictionary.root = dictionary.deleteNode(dictionary.root, word);
            cout << "Keyword deleted successfully." << endl;
            break;

        case 3:
            cout << "Displaying dictionary in ascending order:" << endl;
            dictionary.inorderTraversal(dictionary.root, true);
            break;

        case 4:
            cout << "Displaying dictionary in descending order:" << endl;
            dictionary.inorderTraversal(dictionary.root, false);
            break;

        case 5:
            cout << "Enter keyword to search: ";
            cin >> key;
            cout << "Maximum comparisons required: " << dictionary.search(dictionary.root, key, 0) << endl;
            break;

        case 6:
            cout << "Exiting..." << endl;
            exit(0);
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
