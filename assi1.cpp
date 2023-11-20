#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent items in the knapsack
struct Item {
    int weight;
    int value;
    double ratio; // Value-to-weight ratio
};

// Function to compare items based on their value-to-weight ratio
bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Fractional Knapsack using Greedy algorithm
double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), compareItems);
    
    double max_value = 0.0;

    for (int i = 0; i < items.size(); i++) {
        if (capacity == 0)
            break;

        if (items[i].weight <= capacity) {
            max_value += items[i].value;
            capacity -= items[i].weight;
        } 
        else {
            max_value += (items[i].ratio * capacity);
            break;
        }
    }

    return max_value;
}

// 0/1 Knapsack using dynamic programming
int knapsackDP(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;
    cout << "Enter the number of items: ";
    cin >> n;
    vector<Item> items(n);

    cout << "Enter the weight and value of each item:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
    }

    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    double greedyResult = fractionalKnapsack(items, capacity);
    int dpResult = knapsackDP(items, capacity);

    cout << "Greedy Approach (Fractional Knapsack) Maximum Value: " << greedyResult << endl;
    cout << "Dynamic Programming Approach (0/1 Knapsack) Maximum Value: " << dpResult << endl;

    if (greedyResult != dpResult) {
        cout << "The Greedy strategy does not necessarily yield an optimal solution." << endl;
    } else {
        cout << "Both approaches yield the same optimal solution." << endl;
    }

    return 0;
}

