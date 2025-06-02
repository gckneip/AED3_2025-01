#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "brutePermut.hpp"
#include "heldKarp.hpp"
#include <chrono>

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
    }

    return 0;
};