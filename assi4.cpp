#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>  // for memset
#include <climits>  // for INT_MAX

using namespace std;

const int MAX_N = 10; // Define a maximum value for N

int final_path[MAX_N + 1];
bool visited[MAX_N];
int final_res = INT_MAX;

void copyToFinal(int curr_path[], int N) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

int firstMin(int adj[MAX_N][MAX_N], int i, int N) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++) {
        if (adj[i][k] < min && i != k) {
            min = adj[i][k];
        }
    }
    return min;
}

int secondMin(int adj[MAX_N][MAX_N], int i, int N) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

void TSPRec(int adj[MAX_N][MAX_N], int curr_bound, int curr_weight, int level, int curr_path[], int N) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path, N);
                final_res = curr_res;
            }
            return;
        }
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1], N) + firstMin(adj, i, N)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1], N) + firstMin(adj, i, N)) / 2);

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path, N);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;
            visited[i] = false;
        }
    }
}

void TSP(int adj[MAX_N][MAX_N], int N) {
    int curr_path[MAX_N + 1];
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i, N) + secondMin(adj, i, N));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(adj, curr_bound, 0, 1, curr_path, N);
}

int main() {
    int num_cities;

    cout << "Enter the number of cities (maximum " << MAX_N << "): ";
    cin >> num_cities;

    if (num_cities <= 0 || num_cities > MAX_N) {
        cout << "Invalid number of cities. Exiting." << endl;
        return 1;
    }

    int adj[MAX_N][MAX_N];

    cout << "Enter the adjacency matrix (" << num_cities << "x" << num_cities << "):" << endl;
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            cin >> adj[i][j];
        }
    }

    for (int i = 0; i < num_cities; i++) {
        final_path[i] = -1;
        visited[i] = false;
    }

    TSP(adj, num_cities);

    cout << "Minimum cost: " << final_res << endl;
    cout << "Path Taken: ";
    for (int i = 0; i <= num_cities; i++) {
        cout << final_path[i] << " ";
    }

    return 0;
}

