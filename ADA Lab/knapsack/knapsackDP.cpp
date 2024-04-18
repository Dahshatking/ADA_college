/*
	In 0/1 Knapsack problem, we're given a maximum weight that a bag can hold and according to that we've to choose the items from given list such that profit obtained 
 	is maximised.
*/

#include <iostream>
#include <vector>
#include <climits> // for INT_MIN
using namespace std;

int main() {
    vector<int> profit = {5, 15, 10, 20};
    vector<int> weight = {3, 2, 1, 4};
    int n = profit.size();
    int maxW = 5;

    // Initialize two vectors to store results for previous and current weights
    vector<int> curr(maxW + 1, 0), prev(maxW + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int wt = 0; wt <= maxW; wt++) {
            int notTake = 0 + prev[wt];
            int take = INT_MIN;

            // Check if the current item can be included
            if (weight[i] <= wt) {
                take = profit[i] + prev[wt - weight[i]];
            }

            // Store the maximum of two choices
            curr[wt] = max(take, notTake);
        }
        // Update previous values with current for the next iteration
        prev = curr;
    }

    cout << "Maximum obtainable profit is: " << prev[maxW] << endl;

    return 0;
}
