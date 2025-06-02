#include "brutePermut.hpp"
#include "memoryUsage.hpp"
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

void permutations(std::vector<std::vector<int>> graph){
    int n = graph.size();
    std::vector<int> nodes;
    long permutationCounter = 0;

    for(uint64_t i = 0; i < graph.size(); ++i) {
        nodes.push_back(i);
    }
    long nPermutations = 1;

    for(int i = 1; i < n; ++i) {
        nPermutations *= i;
    }

    std::vector<int> minPath, currentPath;
    int minCost = std::numeric_limits<int>::max();
    int currentCost = 0;

    auto start = std::chrono::high_resolution_clock::now();
    auto timeLimit = std::chrono::seconds(60);

    do{
        bool valid = true;

        for(uint64_t i = 0; i < nodes.size() - 1; ++i){
            if(graph[nodes[i]][nodes[i+1]] == 0){
                valid = false;
                break;
            }
            currentPath.push_back(nodes[i]);
            currentCost += graph[nodes[i]][nodes[i+1]];
        }
        if (valid && graph[nodes[nodes.size()-1]][0] == 0){
            valid = false;
        }
        if(valid){
            currentCost += graph[nodes[nodes.size()-1]][0];
            if(currentCost < minCost){
            minCost = currentCost;
            minPath = nodes;
            }
        }
        currentCost = 0;
        currentPath.clear();
        permutationCounter += 1;

        auto now = std::chrono::high_resolution_clock::now();
        if (now - start > timeLimit){
            std::cout << "Time limit exceeded. Stopping execution.\n";
            std::cout << "Total permutations: " << nPermutations << "\n";
            std::cout << "Permutations executed: " << permutationCounter << std::endl;
            return;
        }
    }
    while(next_permutation(nodes.begin() + 1, nodes.end()));

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    minPath.push_back(0); 
    std::reverse(minPath.begin(), minPath.end());

    std::cout << "Minimum cost: " << minCost << std::endl;
    std::cout << "Path: ";
    for (uint64_t i = 0; i < minPath.size(); ++i) {
        std::cout << minPath[i];
        if (i != minPath.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    std::cout << "Execution time: " << duration.count() << " seconds\n";
    std::cout << "Total permutations: " << nPermutations << "\n";
    std::cout << "Permutations executed: " << permutationCounter << std::endl;

    printMemoryUsage();

}