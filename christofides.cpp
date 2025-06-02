#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include "christofides.hpp"
#include "blossom/PerfectMatching.h"


std::vector<Edge> prim(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    int m = n - 1;  // number of edges in MST
    int edge_count = 0;
    std::vector<Edge> mst;
    std::vector<bool> visited(n, false);

    // Min-heap priority queue: (weight, from, to)
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pqueue;

    visited[0] = true;
    for (int i = 0; i < n; i++) {
        if (matrix[0][i] != 0) {
            pqueue.push({matrix[0][i], 0, i});
        }
    }

    while (!pqueue.empty() && edge_count != m) {
        auto [weight, from, to] = pqueue.top();
        pqueue.pop();

        if (visited[to])
            continue;

        mst.push_back({weight, from, to});
        edge_count++;
        visited[to] = true;

        for (int i = 0; i < n; i++) {
            if (matrix[to][i] != 0 && !visited[i]) {
                pqueue.push({matrix[to][i], to, i});
            }
        }
    }

    if (edge_count != m)
        return {};

    return mst;
}


std::vector<int> mstDegrees(const std::vector<std::tuple<int, int, int>>& mst, int n) {
    std::vector<int> degree(n, 0);
    for (const auto& [weight, from, to] : mst) {
        degree[from]++;
        degree[to]++;
    }
    return degree;
}

void match_odd_vertices(const std::vector<int>& odd_vertices, const std::vector<std::vector<int>>& adj_matrix, std::vector<std::tuple<int,int,int>>& mst) {
    int n = odd_vertices.size();
    if (n % 2 != 0) {
        std::cerr << "Odd number of odd-degree vertices! Cannot compute perfect matching.\n";
        return;
    }


    int edge_count = n * (n - 1) / 2;
    PerfectMatching* pm = new PerfectMatching(n, edge_count);

 
    for (int i = 0; i < n; ++i) {
        int u = odd_vertices[i];
        for (int j = i + 1; j < n; ++j) {
            int v = odd_vertices[j];
            int weight = adj_matrix[u][v];

            pm->AddEdge(i, j, weight);
        }
    }

    pm->Solve();

    std::cout << "Perfect matching among odd-degree vertices:\n";
    for (int i = 0; i < n; ++i) {
        int match = pm->GetMatch(i);
        if (i < match) {
            int original_u = odd_vertices[i];
            int original_v = odd_vertices[match];
            std::cout << original_u << " -- " << original_v
                      << " (cost: " << adj_matrix[original_u][original_v] << ")\n";
        }
    }

    // Assume oddVertices contains the original node indices in the full graph
// and the subgraph passed to Blossom is between them

for (int i = 0; i < odd_vertices.size(); ++i) {
    int j = pm->GetMatch(i);
    if (i < j) { // avoid duplicates
        int u = odd_vertices[i];
        int v = odd_vertices[j];
        int w = adj_matrix[u][v]; // the original graph weight

        mst.push_back(std::make_tuple(w, u, v));
    }
}
    delete pm;
}


std::vector<int> findEulerianCircuit(const std::vector<std::tuple<int, int, int>>& edges, int startNode) {
    std::unordered_map<int, std::multiset<int>> adj;

    // Step 1: Build adjacency list
    for (const auto& [_, u, v] : edges) {
        adj[u].insert(v);
        adj[v].insert(u);  // undirected
    }

    // Step 2: Hierholzer's Algorithm
    std::stack<int> currPath;
    std::vector<int> circuit;

    currPath.push(startNode);

    while (!currPath.empty()) {
        int node = currPath.top();

        if (!adj[node].empty()) {
            int neighbor = *adj[node].begin();  // pick one neighbor
            adj[node].erase(adj[node].begin());
            adj[neighbor].erase(adj[neighbor].find(node));  // remove both directions

            currPath.push(neighbor);
        } else {
            circuit.push_back(node);
            currPath.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
}

std::vector<int> shortcutEulerianPath(const std::vector<int>& eulerianPath) {
    std::unordered_set<int> visited;
    std::vector<int> hamiltonianPath;

    for (int node : eulerianPath) {
        if (visited.find(node) == visited.end()) {
            visited.insert(node);
            hamiltonianPath.push_back(node);
        }
    }

    // Optional: return to starting node to complete the tour
    hamiltonianPath.push_back(hamiltonianPath[0]);

    return hamiltonianPath;
}
