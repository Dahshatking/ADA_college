#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>  // for generate
using namespace std;
using namespace std::chrono;

// Horner's method for polynomial evaluation
int Horners(vector<int> &arr, int i, int x)
{
    if (i == arr.size())
        return 0;
    return arr[i] + x * Horners(arr, i + 1, x);
}

// Function to generate random numbers for the vector
void generateRandom(vector<int> &arr)
{
    generate(arr.begin(), arr.end(), rand);
}

// Function to measure time taken by Horners function
void input_generator(vector<pair<int, int>> &store)
{
    for (int i = 10; i <= 10000; i += 500)
    {
        vector<int> arr(i);
        generateRandom(arr);

        int t = 0;
        for (int m = 1; m <= 10; m++)
        {
            auto start = high_resolution_clock::now();
            Horners(arr, 0, 4);  // Evaluating polynomial for x = 4
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

    cout << "Number of inputs\tTime taken (microseconds)\n\n";
    for (const auto &i : store)
    {
        cout << i.first << "\t\t\t" << i.second << endl;
    }

    return 0;
}
