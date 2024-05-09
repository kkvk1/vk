#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Graph {
private:
    int size;
    vector<vector<int>> adjacency_matrix;
    vector<string> cities;

public:
    Graph() {
        cout << "Total Number of Cities: ";
        cin >> size;
        cout << endl;
        adjacency_matrix.resize(size, vector<int>(size, 0));
        cities.resize(size);
    }

    void takeCities() {
        for (int m = 0; m < size; m++) {
            cout << "Enter City " << m + 1 << " Name: ";
            cin >> cities[m];
        }
    }

    void takeFlights() {
        char ch;
        for (int i = 0; i < size; i++) {
            adjacency_matrix[i][i] = 0; // No self-loops

            for (int j = i + 1; j < size; j++) {
                cout << "\nIs there a flight between " << cities[i] << " to " << cities[j] << " (y/n): ";
                cin >> ch;

                if (ch == 'y' || ch == 'Y') {
                    cout << "Enter flight time/cost: ";
                    cin >> adjacency_matrix[i][j];
                    adjacency_matrix[j][i] = adjacency_matrix[i][j]; // Undirected graph
                }
            }
        }
    }

    void displayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << adjacency_matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    bool isConnected() {
        vector<bool> visited(size, false);
        queue<int> bfsQueue;

        // Start BFS from the first city
        bfsQueue.push(0);
        visited[0] = true;

        int count = 1; // Number of visited nodes
        while (!bfsQueue.empty()) {
            int city = bfsQueue.front();
            bfsQueue.pop();

            for (int j = 0; j < size; j++) {
                if (adjacency_matrix[city][j] > 0 && !visited[j]) {
                    visited[j] = true;
                    bfsQueue.push(j);
                    count++;
                }
            }
        }

        return count == size; // True if all cities are reachable
    }
};

int main() {
    Graph flightGraph;

    flightGraph.takeCities();
    flightGraph.takeFlights();
    flightGraph.displayAdjacencyMatrix();

    if (flightGraph.isConnected()) {
        cout << "\nThe flight network is connected.\n";
    } else {
        cout << "\nThe flight network is not connected.\n";
    }

    return 0;
}
