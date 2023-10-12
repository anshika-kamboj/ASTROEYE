#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;

int MST() {
    vector<double> A; // Define the array A to store the second column of correlation.txt

    // Read the second column of correlation.txt into A
    ifstream inFile("correlation.txt");
    double val;
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            break; // stop reading when we encounter an empty line
        }
        istringstream iss(line);
        double v1, v2;
        iss >> v1 >> v2;
        A.push_back(v2);
    }

    // Compute the minimum spanning tree using Kruskal's algorithm
    int n = A.size();
    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            edges.push_back({abs(A[i]-A[j]), {i, j}});
        }
    }
    sort(edges.begin(), edges.end());

    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<pair<int, int>> mst;
    for (auto edge : edges) {
        double w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        int p1 = parent[u];
        int p2 = parent[v];
        if (p1 != p2) {
            mst.push_back({u, v});
            for (int i = 0; i < n; i++) {
                if (parent[i] == p2) {
                    parent[i] = p1;
                }
            }
        }
    }

    // Print the edges of the minimum spanning tree
    for (auto edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }

    return 0;
}
