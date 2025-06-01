#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <stack>
#include "heldKarp.hpp"
#include "memoryUsage.hpp"

void heldKarp(const std::vector<std::vector<int>>& graph) {
    const int n = graph.size();
    const int INF = std::numeric_limits<int>::max();
    const int FULL_MASK = 1 << n;

    std::vector<std::vector<int>> dp(FULL_MASK, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(FULL_MASK, std::vector<int>(n, -1));

    dp[1][0] = 0;

    for (int mask = 1; mask < FULL_MASK; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                if (graph[u][v] == 0) continue;
                int nextMask = mask | (1 << v);
                if (dp[mask][u] != INF && dp[nextMask][v] > dp[mask][u] + graph[u][v]) {
                    dp[nextMask][v] = dp[mask][u] + graph[u][v];
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    int res = INF;
    int last = -1;
    for (int i = 1; i < n; ++i) {
        if (graph[i][0] != 0 && dp[FULL_MASK - 1][i] != INF) {
            int cost = dp[FULL_MASK - 1][i] + graph[i][0];
            if (cost < res) {
                res = cost;
                last = i;
            }
        }
    }

    if (res == INF) {
        std::cout << "No Hamiltonian cycle found.\n";
        return;
    }

    std::vector<int> path;
    int mask = FULL_MASK - 1;
    int curr = last;
    while (curr != -1) {
        path.push_back(curr);
        int temp = parent[mask][curr];
        mask ^= (1 << curr);
        curr = temp;
    }

    path.push_back(0);

    std::reverse(path.begin(), path.end());

    std::cout << "Minimum cost of Hamiltonian cycle: " << res << "\n";
    std::cout << "Path: ";
    for (int city : path) {
        std::cout << city << " ";
    }
    std::cout << "\n";

    printMemoryUsage(); 
}
