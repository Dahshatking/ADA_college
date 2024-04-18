#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MultiStageGraph {
    int n, m, k;
    vector<vector<int>> cost;
    vector<int> d, p, fcost;

public:
    MultiStageGraph(int vertices, int edges, const vector<vector<int>>& c)
        : n(vertices), m(edges), cost(c), k(1) {
        d.resize(n + 1);
        fcost.resize(n + 1);
    }

    void getStages(int s) {
        if (s == n) return;
        for (int i = 1; i <= n; ++i) {
            if (cost[s][i] != INT_MAX && cost[s][i] != 0) {
                k++;
                getStages(i);
                break;
            }
        }
    }

    int chooseVertex(int j) {
        int mini = INT_MAX;
        int r = -1;
        for (int i = j + 1; i <= n; ++i) {
            if (cost[j][i] != 0 && cost[j][i] != INT_MAX) {
                if (cost[j][i] + fcost[i] < mini) {
                    mini = cost[j][i] + fcost[i];
                    r = i;
                }
            }
        }
        return r;
    }

    void calculateCost() {
        p.resize(k + 1);
        fcost[n] = 0;  // last vertex cost is zero

        for (int j = n - 1; j >= 1; --j) {
            int r = chooseVertex(j);
            if (r == -1) continue;
            fcost[j] = cost[j][r] + fcost[r];
            d[j] = r;  // storing the next min vertex it came from
        }

        p[0] = 1;
        p[k] = n;
        for (int j = 1; j < k; ++j) {
            p[j] = d[p[j - 1]];
        }

        cout << "Cost: " << fcost[1] << endl;
        cout << "Path taken: ";
        for (int i = 0; i <= k; ++i) {
            cout << p[i] << "\t";
        }
        cout << endl;
    }
};

int main() {
    int n = 4, m = 4;
    
    vector<vector<int>> cost{
        {0, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, 0, 1, 2, INT_MAX},
        {INT_MAX, INT_MAX, 0, INT_MAX, 3},
        {INT_MAX, INT_MAX, INT_MAX, 0, 1},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0}
    };

    MultiStageGraph G(n, m, cost);
    G.getStages(1);
    G.calculateCost();

    return 0;
}
