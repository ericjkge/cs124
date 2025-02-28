import random
import math


class Edge:
    def __init__(self, u, v, w):
        self.u = u  # Source
        self.v = v  # Destination
        self.w = w  # Weight


class Graph:
    def __init__(self, n, d):
        self.n = n  # Number of vertices
        self.d = d  # Graph dimension
        self.edges = []  # List of edges

    def create_graph(self):
        if self.d == 0:
            self.create_0D()
        elif self.d == 1:
            self.create_1D()
        else:
            self.create_234D()

    # Complete
    def create_0D(self):
        for i in range(1, self.n):
            for j in range(i):
                weight = random.random()  # CHECK CHECK CHECK – range is [0, 1)
                self.edges.append(Edge(i, j, weight))

    # Hypercube
    def create_1D(self):
        for i in range(1, self.n):
            for j in range(i):
                diff = i - j
                if diff & (diff - 1) == 0:  # Check if diff is a power of 2
                    weight = random.random()
                    self.edges.append(Edge(i, j, weight))

    # Geometric
    def create_234D(self):
        vertices = []  # Create list of n-dimensional vertices
        for i in range(self.n):
            vertex = []
            for j in range(self.d):
                vertex.append(random.random())
            vertices.append(vertex)

        for i in range(1, self.n):
            for j in range(i):
                weight = self.distance(vertices[i], vertices[j])
                self.edges.append(Edge(i, j, weight))

    # Calculate the Euclidean distance between two vertices (dimension = len(u))
    def distance(self, u, v):
        return math.sqrt(sum((u[i] - v[i]) ** 2 for i in range(len(u))))


def main():
    n = 10
    graphs = {
        "0D": Graph(n, 0),
        "Hypercube": Graph(n, 1),
        "2D": Graph(n, 2),
        "3D": Graph(n, 3),
        "4D": Graph(n, 4),
    }

    # Print sample edges
    for label, graph in graphs.items():
        graph.create_graph()
        print(
            f"Sample edges from {label} graph:",
            [(e.u, e.v, e.w) for e in graph.edges[:5]],
        )


if __name__ == "__main__":
    main()

# NOTE: include threshold function on edges? From "Hint" in the assignment
