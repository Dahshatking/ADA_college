#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Recursive function to solve Tower of Hanoi
void TOH(int n, int A, int B, int C)
{
    if (n >= 1)
    {
        TOH(n - 1, A, C, B);
        // Move nth disk from A to C
        TOH(n - 1, B, A, C);
    }
}

// Function to measure time taken to solve Tower of Hanoi
void input_generator(vector<pair<int, int>> &store)
{
    for (int n = 10; n <= 50; n += 5)
    {
        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            TOH(n, 1, 2, 3);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({n, t});
    }
}

int main()
{
    vector<pair<int, int>> store;
    input_generator(store);

    cout << "Number of Disks\tTime taken (milliseconds)\n\n";
    for (const auto &i : store)
    {
        cout << i.first << "\t\t" << i.second << endl;
    }

    return 0;
}
