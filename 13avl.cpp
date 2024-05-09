#include <iostream>
using namespace std;

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

class AVLTree {
public:
    AVLNode* root;

    AVLTree() {
        root = nullptr;
    }

    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

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

    int search(AVLNode* node, string key, int comparisions) {
        if (node == nullptr || node->word == key) {
            if (node != nullptr)
                cout << "Key is present in the tree." << endl;
            return comparisions + 1;
        }

        comparisions++;
        if (key < node->word)
            return search(node->left, key, comparisions);
        else
            return search(node->right, key, comparisions);
    }
};

int main() {
    AVLTree dictionary;
    int choice;
    string word, meaning, key;

    while (true) {
        cout << "\n1. Insert Keyword\n2. Update Meaning\n3. Display Ascending\n4. Display Descending\n5. Search\n6. Exit\n";
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
            cout << "Enter keyword and new meaning: ";
            cin >> word >> meaning;
            dictionary.root = dictionary.insert(dictionary.root, word, meaning);
            cout << "Meaning updated successfully." << endl;
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
