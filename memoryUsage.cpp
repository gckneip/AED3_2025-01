#include "memoryUsage.hpp"
#include <iostream>
#include <fstream>

void printMemoryUsage() {
    std::ifstream status("/proc/self/status");
    std::string line;
    while (std::getline(status, line)) {
        if (line.find("VmRSS:") == 0) {
            std::cout << "Memory usage: " << line << std::endl;
            break;
        }
    }
}