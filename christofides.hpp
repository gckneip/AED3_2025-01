#pragma once
#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> Edge; // (weight, from, to)
std::vector<Edge> prim(const std::vector<std::vector<int>>& matrix);
std::vector<int> mstDegrees(const std::vector<std::tuple<int, int, int>>& mst, int n);
void match_odd_vertices(const std::vector<int>& odd_vertices, const std::vector<std::vector<int>>& adj_matrix,  std::vector<std::tuple<int,int,int>>& mst);
std::vector<int> findEulerianCircuit(const std::vector<std::tuple<int, int, int>>& edges, int startNode);
std::vector<int> shortcutEulerianPath(const std::vector<int>& eulerianPath);
