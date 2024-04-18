#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Linear search function
int search(vector<int> &arr, int i, int x)
{
    if (i == arr.size())
        return -1; // Element not found
    if (arr[i] == x)
        return x; // Element found
    else
        return search(arr, i + 1, x);
}

// Function to generate input and measure time
void input_generator(vector<pair<int, int>> &store)
{
    for (int n = 100; n < 10000; n += 100)
    {
        vector<int> arr(n);
        for (int i = 1; i <= n; i++)
            arr[i - 1] = i;
        
        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            search(arr, 0, n + 2); // Searching for an element that is not present
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
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

    cout << "Number of Inputs\tTime taken (nanoseconds)\n\n";
    for (const auto &i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
