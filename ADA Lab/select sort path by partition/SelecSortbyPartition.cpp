// Read-up : In selection sort, we iterate through the array from idx-> 0 to n and each time we get the shortest element from the array particularly from idx+1 till the end.
// Now instead of getting that smallest elt by iterating through array yet again , we're doing the same using quick sort and partition wherein the index of smlst elt is being returned and then back to Selection sort, we're swapping both of them
#include <bits/stdc++.h>
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
            i++;
        while (arr[j] > pivot && j >= low + 1)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

int QuickSelect(vector<int>& arr, int low, int high, int k = 0)
{
    if (low < high)
    {
        int j = Partition(arr, low, high);
        if (j == k)
            return j;
        else if (j > k)
            QuickSelect(arr, low, j - 1, k);
        else
            QuickSelect(arr, j + 1, high, k);
    }
}

void SelectionSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int iThSmallest = QuickSelect(arr, i, n - 1, i);
        swap(arr[i], arr[iThSmallest]);
    }
}

void input_generator(vector<pair<int, int>>& store)
{
    for (int i = 1000; i <= 10000; i += 500)
    {
        vector<int> arr(i);
        for (int n = 0; n < i; n++)
            arr[n] = rand() % 100;

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            SelectionSort(arr);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            t += duration.count();
        }
        t /= 10;
        store.push_back({i, t});
    }
}

int main()
{
    vector<pair<int, int>> store;
    input_generator(store);

    cout << "Number of inputs \tTime taken\n\n";
    for (auto i : store)
    {
        cout << i.first << " \t" << i.second << endl;
    }
    return 0;
}
