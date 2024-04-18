#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to generate power set of a boolean array
void powerSetGenerator(vector<bool> &arr, int i)
{
    if (i == arr.size())
    {
        // Uncomment to print subsets
        // for (auto j : arr)
        //     cout << j << " ";
        // cout << endl;
        return;
    }

    arr[i] = true;
    powerSetGenerator(arr, i + 1);

    arr[i] = false;
    powerSetGenerator(arr, i + 1);
}

// Function to generate input and measure time
void input_generator(vector<pair<int, int>> &store)
{
    for (int n = 1; n <= 20; n += 2)
    {
        vector<bool> arr(n, true);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            powerSetGenerator(arr, 0);
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

    cout << "Number of Inputs\tTime taken (milliseconds)\n\n";
    for (const auto &i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
