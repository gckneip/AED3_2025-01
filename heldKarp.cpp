#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "heldKarp.hpp"
#include "memoryUsage.hpp"

const int INF = std::numeric_limits<int>::max();

void heldKarp(std::vector<std::vector<int>>& graph) {
    const int n = graph.size();
    std::cout << n << "\n";

    const uint64_t FULL_MASK = 1ULL << n; 
    std::cout << FULL_MASK << "\n";

    completeGraphFloydWarshall(graph);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> dp(FULL_MASK, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(FULL_MASK, std::vector<int>(n, -1));  

    dp[1][0] = 0;

    for (uint64_t mask = 1; mask < FULL_MASK; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                if (graph[u][v] == INF) continue;  

                int nextMask = mask | (1 << v);
                int newCost = dp[mask][u] + graph[u][v];
                if (newCost < dp[nextMask][v]) {
                    dp[nextMask][v] = newCost;
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    int res = INF;
    int last = -1;
    for (int i = 1; i < n; ++i) {
        if (graph[i][0] == INF) continue;
        if (dp[FULL_MASK - 1][i] == INF) continue;

        int cost = dp[FULL_MASK - 1][i] + graph[i][0];
        if (cost < res) {
            res = cost;
            last = i;
        }
    }

    if (res == INF) {
        std::cout << "No Hamiltonian cycle found.\n";
        return;
    }

    std::vector<int> path;
    uint64_t mask = FULL_MASK - 1;
    int curr = last;
    while (curr != -1) {
        if (curr < 0 || curr >= n || mask >= FULL_MASK) {
            std::cout << "Erro na reconstrução: curr ou mask fora do intervalo\n";
            return;
        }

        path.push_back(curr);
        int temp = parent[mask][curr];
        mask ^= (1 << curr);
        curr = temp;
    }
    std::reverse(path.begin(), path.end());
    path.push_back(0); 

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Minimum cost: " << res << std::endl;
    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << std::endl;

    std::cout << "Execution time: " << duration.count() << " seconds\n";
    printMemoryUsage();
}

void completeGraphFloydWarshall(std::vector<std::vector<int>>& graph) {
    int n = graph.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                graph[i][j] = 0;
            } else if (graph[i][j] <= 0) {  
                graph[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (graph[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (graph[k][j] == INF) continue;
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }   
}