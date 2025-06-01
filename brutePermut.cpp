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

    for(int i = 0; i < graph.size(); ++i) {
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

    do{ //if graph isnt fully connected it need to verify if the next step exists and if not break the current permutation
        bool valid = true;

        for(int i = 0; i < nodes.size() - 1; ++i){
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
            break;
        }
    }
    while(next_permutation(nodes.begin() + 1, nodes.end()));

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds\n";
    std::cout << "Total permutations: " << nPermutations << "\n" << "Permutations executed: " << permutationCounter << std::endl;

    std::cout << minCost << std::endl;

    for(int node : minPath){
        std::cout << node << " -> ";
    }
    std::cout << nodes[0] << std::endl;
    printMemoryUsage();
}