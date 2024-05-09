#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Graph {
private:
    int size;
    vector<vector<pair<int, int>>> adjacency_list; // adjacency list of (neighbor, cost)
    vector<string> cities;

public:
    Graph() {
        cout << "Total Number of Cities: ";
        cin >> size;
        cout << endl;
        adjacency_list.resize(size);
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
            for (int j = i + 1; j < size; j++) {
                cout << "\nIs there a flight between " << cities[i] << " to " << cities[j] << " (y/n): ";
                cin >> ch;

                if (ch == 'y' || ch == 'Y') {
                    int cost;
                    cout << "Enter flight time/cost: ";
                    cin >> cost;
                    adjacency_list[i].push_back({j, cost});
                    adjacency_list[j].push_back({i, cost}); // Undirected graph
                }
            }
        }
    }

    void displayAdjacencyList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < size; i++) {
            cout << cities[i] << " -> ";
            for (auto neighbor : adjacency_list[i]) {
                cout << cities[neighbor.first] << "(" << neighbor.second << " mins) ";
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

            for (auto neighbor : adjacency_list[city]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    bfsQueue.push(neighbor.first);
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
    flightGraph.displayAdjacencyList();

    if (flightGraph.isConnected()) {
        cout << "\nThe flight network is connected.\n";
    } else {
        cout << "\nThe flight network is not connected.\n";
    }

    return 0;
}
