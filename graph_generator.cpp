#include "graph_generator.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Edge Constructor
Edge::Edge(int src, int dest, double weight) : u(src), v(dest), w(weight) {}

// Graph Constructor
Graph::Graph(int numVertices, int dimension) : n(numVertices), d(dimension) {}

// Create Graph Function
void Graph::createGraph() {
    if (d == 0) {
        create_0D();
    } else if (d == 1) {
        create_1D();
    } else {
        create_234D();
    }
}

void Graph::create_0D() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double weight = dist(gen);  // Generates a random weight
            edges.emplace_back(i, j, weight);
        }
    }
}

void Graph::create_1D() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int diff = i - j;
            if ((diff & (diff - 1)) == 0) { // Check if diff is a power of 2
                double weight = dist(gen);
                edges.emplace_back(i, j, weight);
            }
        }
    }
}

void Graph::create_234D() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    vector<vector<double>> vertices(n, vector<double>(d));

    // Generate random vertices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            vertices[i][j] = dist(gen);  // Assign random coordinate
        }
    }

    // Compute Euclidean distance
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double weight = distance(vertices[i], vertices[j]);
            edges.emplace_back(i, j, weight);
        }
    }
}

double Graph::distance(const vector<double>& u, const vector<double>& v) {
    double sum = 0.0;
    for (size_t i = 0; i < u.size(); i++) {
        sum += pow(u[i] - v[i], 2);
    }
    return sqrt(sum);
}

void printSampleEdges(Graph& graph, const string& label) {
    cout << "Sample edges from " << label << " graph:\n";
    for (size_t i = 0; i < min(graph.edges.size(), size_t(5)); i++) {
        cout << "(" << graph.edges[i].u << ", " << graph.edges[i].v 
             << ", " << graph.edges[i].w << ")\n";
    }
    cout << endl;
}

