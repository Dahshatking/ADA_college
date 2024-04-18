// Sorting Profits/Weights in non-increasing order comes out to be the most optimal one in Knapsack
#include <iostream>
#include <vector>
#include <algorithm> // for swap, reverse
using namespace std;

// QuickSort for pairs based on the first element
int partition(vector<pair<int, int>>& arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[low].first;

    while (i < j)
    {
        while (arr[i].first <= pivot && i <= high - 1)
            i++;
        while (arr[j].first > pivot && j >= low + 1)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void QuickSort(vector<pair<int, int>>& arr, int low, int high)
{
    if (low < high)
    {
        int j = partition(arr, low, high);
        QuickSort(arr, low, j - 1);
        QuickSort(arr, j + 1, high);
    }
}

// QuickSort for pairs based on the first element of the second pair
int partitionPW(vector<pair<float, pair<float, float>>>& arr, int low, int high)
{
    int i = low;
    int j = high;
    float pivot = arr[low].first;

    while (i < j)
    {
        while (arr[i].first <= pivot && i <= high - 1)
            i++;
        while (arr[j].first > pivot && j >= low + 1)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void QuickSortPW(vector<pair<float, pair<float, float>>>& arr, int low, int high)
{
    if (low < high)
    {
        int j = partitionPW(arr, low, high);
        QuickSortPW(arr, low, j - 1);
        QuickSortPW(arr, j + 1, high);
    }
}

void KnapSack(vector<int>& profit, vector<int>& weight, float maxW)
{
    int n = profit.size();
    vector<pair<int, int>> arr(n);
    vector<int> X(n, 0); // for tracking selected items

    // Sorting according to non-decreasing weights
    for (int i = 0; i < n; i++)
    {
        arr[i] = {weight[i], profit[i]};
    }
    QuickSort(arr, 0, n - 1);

    float prft = 0;
    float W = maxW;
    for (int it = 0; it < n && arr[it].first <= W; it++)
    {
        prft += arr[it].second;
        X[it] = 1;
        W -= arr[it].first;
    }
    cout << "Sorting weights in non-decreasing order: " << prft << endl;

    // Sorting profits in non-increasing order
    for (int i = 0; i < n; i++)
    {
        arr[i] = {profit[i], weight[i]};
    }
    QuickSort(arr, 0, n - 1);
    reverse(arr.begin(), arr.end());

    prft = 0;
    W = maxW;
    for (int it = 0; it < n && arr[it].first <= W; it++)
    {
        prft += arr[it].first;
        X[it] = 1;
        W -= arr[it].second;
    }
    cout << "Sorting profits in non-increasing order: " << prft << endl;

    // Sorting in non-increasing order of profits/weights ratio
    vector<pair<float, pair<float, float>>> A(n);
    for (int i = 0; i < n; i++)
    {
        A[i] = {static_cast<float>(profit[i]) / weight[i], {profit[i], weight[i]}};
    }
    QuickSortPW(A, 0, n - 1);
    reverse(A.begin(), A.end());

    prft = 0;
    W = maxW;
    for (int it = 0; it < n && A[it].second.second <= W; it++)
    {
        prft += A[it].second.first;
        W -= A[it].second.second;
    }
    cout << "Sorting profits/weights ratio in non-increasing order: " << prft << endl;
}

int main()
{
    vector<int> profit = {5, 15, 10, 20};
    vector<int> weight = {3, 2, 1, 4};
    
    KnapSack(profit, weight, 5);

    return 0;
}
