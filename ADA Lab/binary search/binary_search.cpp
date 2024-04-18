#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Binary Search function
int BinarySearch(vector<int> &arr, int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return BinarySearch(arr, l, mid - 1, x);

        return BinarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

// Function to generate sorted array
void generate(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
}

// Function to test binary search in best case
void input_generator1(vector<pair<int, int>> &store)
{
    for (int i = 100; i <= 1000000; i *= 10)
    {
        vector<int> arr(i);
        generate(arr, i);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            BinarySearch(arr, 0, i - 1, i / 2); // Searching for the middle element
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({i, t});
    }
}

// Function to test binary search in worst case
void input_generator2(vector<pair<int, int>> &store)
{
    for (int i = 1; i <= 10000000; i *= 10)
    {
        vector<int> arr(i);
        generate(arr, i);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            BinarySearch(arr, 0, i - 1, i + 2); // Searching for an element outside the array range
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({i, t});
    }
}

int main()
{
    vector<pair<int, int>> store1, store2;

    // Testing best case
    input_generator1(store1);

    cout << "Best case complexity: Time taken (nanoseconds) vs Number of Inputs" << endl;
    for (const auto &i : store1)
    {
        cout << i.first << "\t" << i.second << endl;
    }

    cout << endl << "Worst case complexity: Time taken (nanoseconds) vs Number of Inputs" << endl;

    // Testing worst case
    input_generator2(store2);
    for (const auto &i : store2)
    {
        cout << i.first << "\t" << i.second << endl;
    }

    return 0;
}
