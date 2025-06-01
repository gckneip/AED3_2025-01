#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "brutePermut.hpp"
#include "heldKarp.hpp"

#include "christofides.hpp"

int main(int argc, char *argv[]) {
    //verifies number of arguments

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

        for(const auto& row : graph){
            std::cout << "|";
            for(int val : row){
                std::cout << val << " ";
            }
            std::cout << "|" << "\n";
        }

    if (argv[2][0] == '0'){
        permutations(graph);
    } else if(argv[2][0] == '1'){
        heldKarp(graph); //held karp
    }

    return 0;
};