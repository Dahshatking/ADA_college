// Given a list of n random numbers, Find kth smallest number without sorting the list.
// Using concept of partition and Binary Search

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // for generate
using namespace std;
using namespace std::chrono;

int Partition(vector<int>& arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[low];

    while (i < j) 
    {
        while (arr[i] <= pivot && i <= high - 1) 
        {
            i++;
        }
        while (arr[j] > pivot && j >= low + 1) 
        {
            j--;
        }
        if (i < j) 
        {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    return j;
}

// kth smallest element using QuickSelect algorithm
int kthPartition(vector<int>& arr, int low, int high, int k)
{
    if (low < high) 
    {
        int j = Partition(arr, low, high);
        
        if (j == k) 
        {
            return arr[j];
        } 
        else if (j > k) 
        {
            return kthPartition(arr, low, j - 1, k);
        } 
        else 
        {
            return kthPartition(arr, j + 1, high, k);
        }
    }
    return -1; // Return -1 if k is out of bounds
}

void input_generator(vector<pair<int, int>>& store)
{
    for (int i = 10; i <= 10000; i += 1000)
    {
        vector<int> arr(i);
        generate(arr.begin(), arr.end(), rand);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            kthPartition(arr, 0, i - 1, i + 6);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({i, t});
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
