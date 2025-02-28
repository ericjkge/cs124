#!/usr/bin/env python3

import sys
from graph_generator import Edge, Graph
import csv


# Disjoint set data structure
class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        r1 = self.find(u)
        r2 = self.find(v)
        if r1 != r2:
            if self.rank[r1] > self.rank[r2]:
                self.parent[r2] = r1
            elif self.rank[r2] > self.rank[r1]:
                self.parent[r1] = r2
            else:
                self.parent[r2] = r1
                self.rank[r1] += 1


# Merge sort
def merge_sort(edges):
    if len(edges) <= 1:
        return edges

    mid = len(edges) // 2
    left = merge_sort(edges[:mid])
    right = merge_sort(edges[mid:])
    return merge(left, right)


# Merge function
def merge(left, right):
    sorted_list = []
    i, j = 0, 0
    while i < len(left) and j < len(right):
        if left[i].w < right[j].w:
            sorted_list.append(left[i])
            i += 1
        else:
            sorted_list.append(right[j])
            j += 1

    # Append extra elements from non-empty side
    sorted_list.extend(left[i:])
    sorted_list.extend(right[j:])

    return sorted_list


def kruskals(n, edges):
    sorted_edges = merge_sort(edges)
    ds = DisjointSet(n)
    mst = []
    for edge in sorted_edges:
        if ds.find(edge.u) != ds.find(edge.v):
            mst.append(edge)
            ds.union(edge.u, edge.v)
            if len(mst) == n - 1:  # Max size of MST is n-1 vertices
                break
    return mst


def calculate_average_weight(n, trials, d):
    total_weight = 0
    for _ in range(trials):
        graph = Graph(n, d)
        graph.create_graph()
        mst = kruskals(n, graph.edges)
        if len(mst) == n - 1:  # Additional guardrail in case graph wasn't connected
            total_weight += sum(edge.w for edge in mst)
    return total_weight / trials


def generate_plot_data(d, trials=100, output_file="final_results.csv"):
    n_values = [128 * (2 ** i) for i in range(5)]
    with open(output_file, 'w', newline='') as file:
        writer = csv.writer(file)
        for n in n_values:
            avg_weight = calculate_average_weight(n, trials, d)
            writer.writerow([n, avg_weight])    

def main():
    if len(sys.argv) != 5:
        print("Usage: ./randmst 0 numpoints numtrials dimension")
        sys.exit(1)

    _, _, n, trials, d = sys.argv  # Ignore file name and flag (not used)

    n = int(n)
    trials = int(trials)
    d = int(d)

    average_weight = calculate_average_weight(n, trials, d)

    """
    n = 100
    trials = 20000
    d = 0
    """

    average_weight = calculate_average_weight(n, trials, d)
    print(f"{average_weight} {n} {trials} {d}")


if __name__ == "__main__":
    generate_plot_data(0)
    # main()
