#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void printPath(const vector<vector<int>>& l, int lastTrack, int i) {
    if (i < 0) return;
    cout << lastTrack << " ";
    int lst = l[lastTrack][i];
    printPath(l, lst, i - 1);
}

int AssemblyLine(const vector<vector<int>>& A, const vector<vector<int>>& t,
                 int e1, int e2, int x1, int x2, int n) {
    vector<vector<int>> f(2, vector<int>(n, 0));
    vector<vector<int>> l(2, vector<int>(n, 0));

    f[0][0] = e1 + A[0][0];
    f[1][0] = e2 + A[1][0];

    for (int j = 1; j < n; ++j) {
        if (f[0][j - 1] + A[0][j] < f[1][j - 1] + t[1][j - 1] + A[0][j]) {
            f[0][j] = f[0][j - 1] + A[0][j];
            l[0][j] = 0;
        } else {
            f[0][j] = f[1][j - 1] + t[1][j - 1] + A[0][j];
            l[0][j] = 1;
        }

        if (f[1][j - 1] + A[1][j] < f[0][j - 1] + t[0][j - 1] + A[1][j]) {
            f[1][j] = f[1][j - 1] + A[1][j];
            l[1][j] = 1;
        } else {
            f[1][j] = f[0][j - 1] + t[0][j - 1] + A[1][j];
            l[1][j] = 0;
        }
    }

    int minT, lastTrack;
    if (f[0][n - 1] + x1 < f[1][n - 1] + x2) {
        minT = f[0][n - 1] + x1;
        lastTrack = 0;
    } else {
        minT = f[1][n - 1] + x2;
        lastTrack = 1;
    }

    cout << "Minimum time: " << minT << endl;
    cout << "Path taken: ";
    printPath(l, lastTrack, n - 1);
    cout << endl;
}

void SolveAssemblyLine() {
    int n;
    cout << "Enter the number of stages: ";
    cin >> n;

    vector<vector<int>> A(2, vector<int>(n));
    for (int i = 0; i < 2; ++i) {
        cout << "Enter time durations for each stage of Assembly line " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    vector<vector<int>> t(2, vector<int>(n));
    for (int i = 0; i < 2; ++i) {
        cout << "Enter transfer time for each stage of Assembly line " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> t[i][j];
        }
    }

    int e1, e2, x1, x2;
    cout << "Enter entry time for first Assembly Line: ";
    cin >> e1;
    cout << "Enter entry time for second Assembly Line: ";
    cin >> e2;
    cout << "Enter exit time for first Assembly Line: ";
    cin >> x1;
    cout << "Enter exit time for second Assembly Line: ";
    cin >> x2;

    AssemblyLine(A, t, e1, e2, x1, x2, n);
}

int main() {
    SolveAssemblyLine();
    return 0;
}
