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


std::vector<Edge> prim(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    int m = n - 1;
    int edge_count = 0;
    std::vector<Edge> mst;
    std::vector<bool> visited(n, false);

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pqueue;

    visited[0] = true;
    for (int i = 0; i < n; i++) {
        if (graph[0][i] != 0) {
            pqueue.push({graph[0][i], 0, i});
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
            if (graph[to][i] != 0 && !visited[i]) {
                pqueue.push({graph[to][i], to, i});
            }
        }
    }

    if (edge_count != m)
        return {};

    return mst;
};


std::vector<int> mstDegrees(const std::vector<std::tuple<int, int, int>>& mst, size_t n) {
    std::vector<int> degree(n, 0);
    for (const auto& [weight, u, v] : mst) {
        degree[u]++;
        degree[v]++;
    }
    return degree;
};

void matchOddVertices(const std::vector<int>& oddVertices, const std::vector<std::vector<int>>& graph, std::vector<std::tuple<int,int,int>>& multigraph) {
    int n = oddVertices.size();

    int edge_count = n * (n - 1) / 2;
    PerfectMatching* pm = new PerfectMatching(n, edge_count);

 
    for (int i = 0; i < n; ++i) {
        int u = oddVertices[i];
        for (int j = i + 1; j < n; ++j) {
            int v = oddVertices[j];
            int weight = graph[u][v];

            pm->AddEdge(i, j, weight);
        }
    }

    pm->Solve();

for (size_t i = 0; i < oddVertices.size(); ++i) {
    size_t j = pm->GetMatch(i);
        if (i < j) { 
            int u = oddVertices[i];
            int v = oddVertices[j];
            int w = graph[u][v];

            multigraph.push_back(std::make_tuple(w, u, v));
        }
    }

    delete pm;
};


std::vector<int> findEulerianPath(const std::vector<std::tuple<int, int, int>>& multigraph, int startNode) {
    std::unordered_map<int, std::multiset<int>> adj;

    for (const auto& [_, u, v] : multigraph) {
        adj[u].insert(v);
        adj[v].insert(u); 
    }

    std::stack<int> currPath;
    std::vector<int> circuit;

    currPath.push(startNode);

    while (!currPath.empty()) {
        int node = currPath.top();

        if (!adj[node].empty()) {
            int neighbor = *adj[node].begin();  
            adj[node].erase(adj[node].begin());
            adj[neighbor].erase(adj[neighbor].find(node)); 

            currPath.push(neighbor);
        } else {
            circuit.push_back(node);
            currPath.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
};

std::vector<int> shortcutEulerianPath(const std::vector<int>& eulerianPath) {
    std::unordered_set<int> visited;
    std::vector<int> hamiltonianPath;

    for (int node : eulerianPath) {
        if (visited.find(node) == visited.end()) {
            visited.insert(node);
            hamiltonianPath.push_back(node);
        }
    }

    hamiltonianPath.push_back(hamiltonianPath[0]);

    return hamiltonianPath;
};

std::vector<int> christofides(const std::vector<std::vector<int>>& graph){

    auto mst = prim(graph);

    auto mstVertexDegree = mstDegrees(mst, graph[0].size());

    std::vector<int> oddVerticesSubGraph;

    for(size_t i = 0; i < mstVertexDegree.size(); ++i){
        if(mstVertexDegree[i] % 2 != 0){
            oddVerticesSubGraph.push_back(i);
        }
    }

    std::vector<Edge> multigraph = mst;

    matchOddVertices(oddVerticesSubGraph, graph, multigraph);

    auto EulerianPath = findEulerianPath(multigraph, 0);

    auto hamiltonianPath = shortcutEulerianPath(EulerianPath);

    return hamiltonianPath;

};