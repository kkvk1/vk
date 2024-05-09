#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Edge {
    int to;
    int cost;

    Edge(int _to, int _cost) : to(_to), cost(_cost) {}
};

struct CompareEdge {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.cost > e2.cost;
    }
};

void primsMST(int n, const vector<vector<int>>& cost, const vector<string>& offices) {
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    vector<bool> visited(n, false);
    visited[0] = true;

    cout << "\nSelected Edges in MST:" << endl;
    int totalMinCost = 0;

    for (int j = 0; j < n; j++) {
        if (cost[0][j] != -1) {
            pq.push(Edge(j, cost[0][j]));
        }
    }

    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();

        if (visited[e.to]) {
            continue;
        }

        visited[e.to] = true;
        cout << "Edge: " << offices[e.to] << " - " << offices[e.to] << endl;
        totalMinCost += e.cost;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[e.to][j] != -1) {
                pq.push(Edge(j, cost[e.to][j]));
            }
        }
    }

    cout << "\nTotal Min Cost: " << totalMinCost << endl;
}

int main() {
    int n;
    cout << "\nEnter the number of offices: ";
    cin >> n;
    cout << endl;

    vector<string> offices(n);
    vector<vector<int>> cost(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        cout << "Enter office " << i + 1 << " name: ";
        cin >> offices[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char op;
            cout << "\nIs there a connection between " << offices[i] << " and " << offices[j] << " (y/n)?: ";
            cin >> op;

            if (op == 'y' || op == 'Y') {
                cout << "Enter Cost: ";
                cin >> cost[i][j];
                cost[j][i] = cost[i][j];
            }
        }
    }

    cout << endl;
    primsMST(n, cost, offices);

    return 0;
}
