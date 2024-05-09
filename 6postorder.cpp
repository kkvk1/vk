#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    node *left;
    node *right;
    char ch;
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

node *newNode(char c) {
    node *temp = new node;
    temp->left = NULL;
    temp->right = NULL;
    temp->ch = c;
    return temp;
}

node *createTree(string expression) {
    node *t, *t1, *t2;
    stack<node *> st;

    for (int i = expression.length() - 1; i >= 0; i--) {
        if (!isOperator(expression[i])) {
            t = newNode(expression[i]);
            st.push(t);
        } else {
            t = newNode(expression[i]);
            t1 = st.top();
            st.pop();
            t2 = st.top();
            st.pop();
            t->left = t1;
            t->right = t2;
            st.push(t);
        }
    }

    t = st.top();
    return t;
}

void postOrder(node *root) {
    if (root == NULL)
        return;

    stack<node *> st;
    stack<char> output;

    st.push(root);

    while (!st.empty()) {
        node *curr = st.top();
        st.pop();
        output.push(curr->ch);

        if (curr->left)
            st.push(curr->left);
        if (curr->right)
            st.push(curr->right);
    }

    while (!output.empty()) {
        cout << output.top() << "\t";
        output.pop();
    }
}

void deleteTree(node *root) {
    if (root == NULL)
        return;

    stack<node *> st;
    st.push(root);

    while (!st.empty()) {
        node *curr = st.top();
        st.pop();

        if (curr->left)
            st.push(curr->left);
        if (curr->right)
            st.push(curr->right);

        cout << "Deleting: " << curr->ch << endl;
        delete curr;
    }
}

int main() {
    string expression;
    cout << "Enter the Prefix Expression: ";
    cin >> expression;

    node *root_node = createTree(expression);

    cout << "\nTree Created successfully" << endl;
    cout << "\nPost-order Traversal:" << endl;
    postOrder(root_node);

    cout << "\n\nDeleting Tree...." << endl;
    deleteTree(root_node);
    cout << "Deleted Successfully" << endl;

    return 0;
}
