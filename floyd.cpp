#include <iostream>
#include <vector>
#include <limits>
#include <thread>
#include <chrono>

const int INF = std::numeric_limits<int>::max();

// Function to implement a computationally intensive Floyd-Warshall algorithm
void floydWarshall(std::vector<std::vector<int> >& graph, int n) {
    std::vector<std::vector<int> > dist = graph;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Simulate extra computation with an artificial delay
                std::this_thread::sleep_for(std::chrono::nanoseconds(100));

                // Additional non-optimized conditional to increase computation time
                if ((i + j) % 2 == 0 || (k % 3 == 0 && i != j)) {
                    // Check if path through vertex k is shorter
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    std::cout << "Finished computation of shortest distances.\n";
}

int main() {
    int n;
    std::cout << "Enter the number of vertices (e.g., 1000): ";
    std::cin >> n;

    // Initialize adjacency matrix with INF
    std::vector<std::vector<int> > graph(n, std::vector<int>(n, INF));

    // Populate the adjacency matrix with sample weights and 0 on the diagonal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                // Assign random weights (just as an example, here we use a fixed pattern)
                graph[i][j] = (i + j) % 10 + 1;
            }
        }
    }

    // Run the intensive Floyd-Warshall algorithm
    floydWarshall(graph, n);

    return 0;
}