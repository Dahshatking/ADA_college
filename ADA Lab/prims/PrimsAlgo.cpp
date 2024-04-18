#include <bits/stdc++.h>
using namespace std;

class PrimsAlgo
{
private:
    int n, m, minCost;
    vector<vector<int>> G;
    vector<int> near;

public:
    PrimsAlgo(int vertices, int edges) : n(vertices), m(edges), minCost(0)
    {
        G.resize(n + 1, vector<int>(n + 1, 1e9));
        for (int i = 0; i <= n; i++)
            G[i][i] = 0;

        near.resize(n + 1, 0);
    }

    void createGraph()
    {
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cout << "Enter edge " << i + 1 << ":\n";
            cout << "Enter vertex 1: "; cin >> u;
            cout << "Enter vertex 2: "; cin >> v;
            cout << "Enter weight of the edge: "; cin >> w;
            G[u][v] = G[v][u] = w;
        }
    }

    int findMinEdge()
    {
        int u, v, minWeight = 1e9;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (G[i][j] < minWeight)
                {
                    minWeight = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        return v;
    }

    int chooseVertex()
    {
        int u = 0, minWeight = 1e9;
        for (int i = 1; i <= n; i++)
        {
            if (near[i] != 0 && G[i][near[i]] < minWeight)
            {
                minWeight = G[i][near[i]];
                u = i;
            }
        }
        return u;
    }

    void updateNear(int u)
    {
        for (int i = 1; i <= n; i++)
        {
            if (G[i][u] < G[i][near[i]])
                near[i] = u;
        }
    }

    void Prims(vector<vector<int>> &MST)
    {
        int startVertex = findMinEdge();
        near[startVertex] = startVertex;

        for (int j = 2; j <= n; j++)
        {
            int u = chooseVertex();
            MST[j][1] = u;
            MST[j][2] = near[u];
            minCost += G[u][near[u]];
            near[u] = 0;
            updateNear(u);
        }

        cout << "Minimum cost of the spanning tree is: " << minCost << endl;
    }
};

int main()
{
    int n, m;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    PrimsAlgo P(n, m);
    P.createGraph();
    vector<vector<int>> MST(n + 1, vector<int>(3, 0));
    P.Prims(MST);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (int i = 1; i < n; i++)
    {
        cout << MST[i][1] << " - " << MST[i][2] << endl;
    }

    return 0;
}
``
