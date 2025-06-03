#pragma once
#include <vector>
#include <tuple>

typedef std::tuple<int, int, int> Edge; // (weight, from, to)
std::vector<int> christofides(const std::vector<std::vector<int>>& graph);
std::vector<Edge> prim(const std::vector<std::vector<int>>& graph);
std::vector<int> mstDegrees(const std::vector<std::tuple<int, int, int>>& mst, size_t n);
void matchOddVertices(const std::vector<int>& oddVertices, const std::vector<std::vector<int>>& graph,  std::vector<std::tuple<int,int,int>>& multigraph);
std::vector<int> findEulerianPath(const std::vector<std::tuple<int, int, int>>& multigraph, int startNode);
std::vector<int> shortcutEulerianPath(const std::vector<int>& eulerianPath);
