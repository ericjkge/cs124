#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "graph_generator.h"

using namespace std;

// Disjoint Set Data Structure
class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int r1 = find(u);
        int r2 = find(v);
        if (r1 != r2) {
            if (rank[r1] > rank[r2]) {
                parent[r2] = r1;
            } else if (rank[r2] > rank[r1]) {
                parent[r1] = r2;
            } else {
                parent[r2] = r1;
                rank[r1]++;
            }
        }
    }
};

// Merge Sort Implementation
vector<Edge> mergeSort(vector<Edge>& edges) {
    if (edges.size() <= 1) return edges;
    
    int mid = edges.size() / 2;
    vector<Edge> left(edges.begin(), edges.begin() + mid);
    vector<Edge> right(edges.begin() + mid, edges.end());
    
    left = mergeSort(left);
    right = mergeSort(right);
    
    vector<Edge> sorted;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].w < right[j].w) {
            sorted.push_back(left[i++]);
        } else {
            sorted.push_back(right[j++]);
        }
    }
    while (i < left.size()) sorted.push_back(left[i++]);
    while (j < right.size()) sorted.push_back(right[j++]);
    
    return sorted;
}

// Kruskal's Algorithm
vector<Edge> kruskals(int n, vector<Edge>& edges) {
    edges = mergeSort(edges);
    DisjointSet ds(n);
    vector<Edge> mst;
    
    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            mst.push_back(edge);
            ds.unionSets(edge.u, edge.v);
            if (mst.size() == n - 1) break;
        }
    }
    return mst;
}

// Function to calculate the average MST weight
double calculateAverageWeight(int n, int trials, int d) {
    double totalWeight = 0.0;
    for (int i = 0; i < trials; i++) {
        Graph graph(n,d);
        graph.createGraph();
        vector<Edge> edges = graph.edges; // Generate edges for a graph here based on n and d
        vector<Edge> mst = kruskals(n, edges);
        if (mst.size() == n - 1) {
            for (const auto& edge : mst) {
                totalWeight += edge.w;
            }
        }
    }
    return totalWeight / trials;
}

// Generate plot data and save to CSV
void generatePlotData(int d, int trials = 100) {
    vector<int> nValues;
    string outputFile = "final_results(d=" + to_string(d) + ").csv"; 
    if (d == 1) {
        nValues = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};
    } else if (d == 0 || d == 2 || d == 3 || d == 4) {
        nValues = { 4096, 8192, 16384, 32768};
    } else {
        cerr << "Invalid dimension value. Exiting function." << endl;
        return;
    }

    ofstream file(outputFile);
    
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    
    for (int n : nValues) {
        int trials; //adjust number of trials based on graph size
        if (d == 1) {
            // Hypercube Graph
            if (n <= 2048) trials = 100;
            else if (n <= 65536) trials = 50;
            else trials = 10;
        } else {
            // Complete Graphs
            if (n <= 1024) trials = 100;
            else if (n <= 16384) trials = 50;
            else trials = 10;
        }
        double avgWeight = calculateAverageWeight(n, trials, d);
        file << n << "," << avgWeight << "\n";
        cout << n << "," << avgWeight << "\n";
    }
    file.close();
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: ./randmst 0 numpoints numtrials dimension" << endl;
        return 1;
    }
    
    int n = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int d = atoi(argv[4]);
    
    double averageWeight = calculateAverageWeight(n, trials, d);
    cout << averageWeight << " " << n << " " << trials << " " << d << endl;
    
    generatePlotData(0);
    return 0;
}
