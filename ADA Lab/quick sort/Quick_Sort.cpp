// Quick Sort along with comparisons of Time Complexity of Average and Worst case of QS

// As evident from the graph attached the complexity of worst case of Quick Sort(when elements are sorted) is more than the average case(random elements)
// Blue graph depicts the worst case and green one the average case
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

void kthPartition(vector<int>& arr, int low, int high)
{
    if (low < high) 
    {
        int j = Partition(arr, low, high);
        kthPartition(arr, low, j - 1);
        kthPartition(arr, j + 1, high);
    }
}

void input_generator_avg(vector<pair<int, int>>& store)
{
    for (int i = 10; i < 150; i += 10)
    {
        vector<int> arr(i);
        generate(arr.begin(), arr.end(), rand);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            kthPartition(arr, 0, i - 1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({i, t});
    }
}

void input_generator_Worst(vector<pair<int, int>>& store)
{
    for (int i = 10; i < 150; i += 10)
    {
        vector<int> arr(i);
        for (int n = 0; n < i; n++)
            arr[n] = n + 1;

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            kthPartition(arr, 0, i - 1);
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
    input_generator_avg(store);

    cout << "Average Case\n";
    cout << "Number of Inputs\tTime taken (microseconds)\n\n";
    for (const auto& i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    cout << "\nWorst Case Complexity\n\n";

    vector<pair<int, int>> store1;
    input_generator_Worst(store1);
    cout << "Number of Inputs\tTime taken (microseconds)\n\n";
    for (const auto& i : store1)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
