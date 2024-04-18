#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Recursive function to calculate the sum of elements in a vector
int get_sum(vector<int> &arr, int i)
{
    if (i == arr.size())
        return 0;
    return arr[i] + get_sum(arr, i + 1);
}

// Function to generate vectors and measure time
void input_generator(vector<pair<int, int>> &store)
{
    for (int i = 1000; i <= 10000; i += 300)
    {
        // Create a vector of size i and initialize with values from 1 to i
        vector<int> arr(i);
        for (int j = 1; j <= i; j++)
            arr[j - 1] = j;

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            get_sum(arr, 0);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            t += duration.count();
        }
        t /= 10; // Calculate average time
        store.push_back({t, i});
    }
}

int main()
{
    vector<pair<int, int>> store;
    input_generator(store);

    cout << "Time (microseconds)\tNumber of Inputs" << endl << endl;
    for (const auto &i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
