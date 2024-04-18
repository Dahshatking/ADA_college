// Iterative Quick Sort + Analysis of it's Space Complexity by keeping the track of recursion calls made
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;

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

void IterativeQS(vector<int>& arr, int low, int high, int& recCalls)
{
    stack<pair<int, int>> st;
    while (true)
    {
        while (low < high)
        {
            int j = partition(arr, low, high);
            if (j - low > high - j)
            {
                st.push({low, j - 1});
                low = j + 1;
                recCalls++;
            }
            else
            {
                st.push({j + 1, high});
                high = j - 1;
                recCalls++;
            }
        }
        if (st.empty())
        {
            recCalls--;
            return;
        }
        low = st.top().first;
        high = st.top().second;
        st.pop();
    }
}

void input_generator(vector<pair<int, pair<int, int>>>& store)
{
    for (int i = 1000; i <= 1500; i += 50)
    {
        vector<int> arr(i);
        for (int it = 0; it < i; it++)
        {
            arr[it] = rand() % 50;
        }

        int t = 0;
        int recCalls = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            recCalls = 0;
            IterativeQS(arr, 0, i - 1, recCalls);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            t += duration.count();
        }
        t /= 10;
        recCalls /= 10;
        store.push_back({i, {t, recCalls}});
    }
}

int main()
{
    // Seed random number generator
    srand(time(NULL));

    vector<pair<int, pair<int, int>>> store;
    input_generator(store);

    cout << "Number of inputs \tTime taken (microseconds) \tAverage Recursion Calls\n\n";
    for (auto i : store)
    {
        cout << i.first << " \t\t" << i.second.first << " \t\t\t\t" << i.second.second << endl;
    }
    return 0;
}
