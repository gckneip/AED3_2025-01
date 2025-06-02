#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
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
        //permutations(graph);
    } else if(argv[2][0] == '1'){
        heldKarp(graph);
    } else if(argv[2][0] == '2'){
        auto start = std::chrono::high_resolution_clock::now();

        auto a = prim(graph);
        for(auto [b, c, d] : a){
            std::cout << b << " - " << c << " -> " << d <<std::endl;
        }

        auto b = mstDegrees(a, graph[0].size());
        for(auto c : b){
            std::cout << c << " ";
        }

        std::vector<int> c;

        for(int i = 0; i < b.size(); ++i){
            if(b[i] % 2 != 0){
                c.push_back(i);
                std::cout << "added node: " << i << std::endl;
            }
        }

        match_odd_vertices(c, graph, a);
        for(auto [b, c, d] : a){
            std::cout << b << " - " << c << " -> " << d <<std::endl;
        }

        auto d = findEulerianCircuit(a, 0);

        for(int e : d){
            std::cout << e << ", ";
        }
        std::cout << std::endl;
        auto e = shortcutEulerianPath(d);

        for(int f : e){ 
            std::cout << f << ", " ;
        }
        int cost = 0;

    for (size_t i = 0; i < e.size() - 1; ++i) {
        int from = e[i];
        int to = e[i + 1];
        cost += graph[from][to];
    }
    std::cout << cost <<std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds\n";

    return 0;
};
};