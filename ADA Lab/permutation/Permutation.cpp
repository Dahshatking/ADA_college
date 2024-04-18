#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to generate permutations of an array
void permutationGenerator(vector<int> &arr, int i, vector<pair<int, int>> &store)
{
    if (i == arr.size())
    {
        // Uncomment to print permutations
        // for (auto j : arr)
        //     cout << j << " ";
        // cout << endl;
        return;
    }
    for (int idx = i; idx < arr.size(); idx++)
    {
        swap(arr[idx], arr[i]);
        permutationGenerator(arr, i + 1, store);
        swap(arr[idx], arr[i]);
    }
}

// Function to generate input and measure time
void input_generator(vector<pair<int, int>> &store)
{
    for (int n = 1; n <= 20; n += 1)
    {
        vector<int> arr(n);
        for (int i = 1; i <= n; i++)
        {
            arr[i - 1] = i;
        }

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            permutationGenerator(arr, 0, store);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
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

    cout << "Number of Inputs\tTime taken (microseconds)\n\n";
    for (const auto &i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
