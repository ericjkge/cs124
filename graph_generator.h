#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <vector>
#include <string>

class Edge {
public:
    int u, v;
    double w;

    Edge(int src, int dest, double weight);
};

class Graph {
public:
    int n, d;
    std::vector<Edge> edges;

    Graph(int numVertices, int dimension);
    void createGraph();

private:
    void create_0D();
    void create_1D();
    void create_234D();
    double distance(const std::vector<double>& u, const std::vector<double>& v);
};

void printSampleEdges(Graph& graph, const std::string& label);

#endif
