#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // for generate
using namespace std;
using namespace std::chrono;

// Merge function to merge two sorted subarrays
void merge(vector<int>& arr, int start, int mid, int end)
{
    int sizeOne = mid - start + 1;
    int sizeTwo = end - mid;

    vector<int> arr1(sizeOne);
    vector<int> arr2(sizeTwo);

    for (int i = 0; i < sizeOne; i++)
        arr1[i] = arr[start + i];

    for (int i = 0; i < sizeTwo; i++)
        arr2[i] = arr[mid + 1 + i];

    int i = 0, j = 0;
    int curr = start;
    while (i < sizeOne && j < sizeTwo)
    {
        if (arr1[i] <= arr2[j])
            arr[curr++] = arr1[i++];
        else
            arr[curr++] = arr2[j++];
    }
    while (i < sizeOne)
        arr[curr++] = arr1[i++];
    while (j < sizeTwo)
        arr[curr++] = arr2[j++];
}

// MergeSort function
void MergeSort(vector<int>& arr, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        MergeSort(arr, start, mid);
        MergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

// Function to generate input and measure time
void input_generator(vector<pair<int, int>>& store)
{
    for (int n = 10; n <= 1000; n += 500)
    {
        vector<int> arr(n);
        generate(arr.begin(), arr.end(), rand);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            MergeSort(arr, 0, n - 1);
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
    for (const auto& i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
