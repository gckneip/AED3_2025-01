#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
#include "brutePermut.hpp"
#include "heldKarp.hpp"
#include <chrono>
#include "christofides.hpp"

int main(int argc, char *argv[]) {

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <0 for brute force, 1 for Held-Karp> <memory_limit_MB>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] <<"\n";
        return 1;
    }
    std::string line;
    std::vector<std::vector<int>> graph;

    while(getline(file, line)){
        std::istringstream iss(line);
        std::vector<int> row;
        int num;

        while(iss >> num){
            row.push_back(num);
        }
        graph.push_back(row);
    }
   

    if (argv[2][0] == '0'){
        permutations(graph);
    } else if(argv[2][0] == '1'){
        heldKarp(graph);
    } else if(argv[2][0] == '2'){
        auto start = std::chrono::high_resolution_clock::now();

        completeGraphFloydWarshall(graph);

        auto minPath = christofides(graph);

        // Print path
        std::cout << "Path: ";
        for(int node : minPath){
            std::cout << node << ", " ;
        }
        std::cout << std::endl;

        //Print cost
        int cost = 0;
        for (size_t i = 0; i < minPath.size() - 1; ++i) {
            cost += graph[minPath[i]][minPath[i+1]];
        }
        std::cout << "cost: " << cost <<std::endl;


        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Execution time: " << duration.count() << " seconds\n";
    }
    return 0;
};
