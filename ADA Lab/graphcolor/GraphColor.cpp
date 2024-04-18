/*
  Given a graph G, we've to color it's vertexes such that no two adjacent vertex gets same color. For this we've been provided with a k which denotes the number
  of different colors made available to us.
  We use the concept of backtracking to solve this problem.
*/

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class GraphColor {
private:
    int n, m, colors;
    vector<vector<int>> G;
    vector<int> x;

public:
    GraphColor(int vertices, int edges, int c)
        : n(vertices), m(edges), colors(c), G(n + 1, vector<int>(n + 1, numeric_limits<int>::max())), x(n + 1, 0) {
        for (int i = 0; i <= n; ++i) {
            G[i][i] = 0;
        }
    }

    void createGraph() {
        for (int i = 0; i < m; ++i) {
            int u, v;
            cout << "Enter edge " << i + 1 << ":\n";
            cout << "Enter vertex 1: ";
            cin >> u;
            cout << "Enter vertex 2: ";
            cin >> v;
            G[u][v] = 1;
            G[v][u] = 1;
        }
    }

    bool isSafe(int k, int color) {
        for (int i = 1; i <= n; ++i) {
            if (G[k][i] != numeric_limits<int>::max() && x[i] == color) {
                return false;
            }
        }
        return true;
    }

    void mColor(int k) {
        if (k == n + 1) {
            cout << "Possible to color the graph with " << colors << " colors.\n";
            for (int i = 1; i <= n; ++i) {
                cout << x[i] << "\t";
            }
            cout << endl;
            return;
        }

        for (int color = 1; color <= colors; ++color) {
            if (isSafe(k, color)) {
                x[k] = color;
                mColor(k + 1);
                x[k] = 0; // backtrack
            }
        }
    }
};

int main() {
    int n, m, c;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;
    cout << "Enter number of colors available: ";
    cin >> c;

    GraphColor G(n, m, c);
    G.createGraph();
    G.mColor(1);

    return 0;
}
