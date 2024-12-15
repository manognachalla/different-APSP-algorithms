#include <iostream>
using namespace std;

const int INF = 999999; // Constant to represent infinity

// Function to find the shortest distance in a multistage graph
void shortestDist(int** graph, int N) {
    int* dist = new int[N]; // Distance array to store shortest distances from node 0 to every other node
    
    // Initialize distances to a large value (manual INF)
    for (int i = 0; i < N; i++) {
        dist[i] = INF; // Setting a large value as INF
    }

    // The distance to the first node (0) from itself is 0
    dist[0] = 0;

    // Calculate the shortest path for all nodes from the first node to the last node
    for (int i = 0; i < N; i++) {
        // Check all possible connections from the current node to later nodes (multistage graph)
        for (int j = i + 1; j < N; j++) {
            // If there's an edge from i to j
            if (graph[i][j] != INF) {
                // Update the shortest distance to node j through node i
                if (dist[j] > graph[i][j] + dist[i]) {
                    dist[j] = graph[i][j] + dist[i];
                }
            }
        }
    }

    // Print the shortest distances from node 0 to all nodes
    cout << "\nShortest distances from node 0 to all other nodes:\n";
    for (int i = 0; i < N; i++) {
        if (dist[i] == INF) {
            cout << "No path available to node " << i << endl;
        } else {
            cout << "Shortest distance to node " << i << ": " << dist[i] << endl;
        }
    }

    // Free dynamically allocated memory
    delete[] dist;
}

// Driver code
int main() {
    int N;
    cout << "Enter the number of nodes: ";
    cin >> N;

    // Declare the adjacency matrix (using dynamically allocated 2D array)
    int** graph = new int*[N];
    for (int i = 0; i < N; i++) {
        graph[i] = new int[N];
        for (int j = 0; j < N; j++) {
            graph[i][j] = INF; // Initialize with a large value to represent INF
        }
    }

    // Input the number of edges
    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Input edge data: source node, destination node, and weight
    // Input edge data: source node, destination node, and weight
for (int i = 0; i < edges; i++) {
    int source, dest, weight;
    cout << "Enter source node, destination node, and weight for edge " << i + 1 << ": ";
    cin >> source >> dest >> weight;

    // Check if source and dest are within bounds
    if (source < 0 || source >= N || dest < 0 || dest >= N) {
        cout << "Invalid edge: " << source << " to " << dest << endl;
        continue; // Skip this edge if invalid
    }

    // Set the weight in the adjacency matrix
    graph[source][dest] = weight;

    // Debug print to verify edge addition
    cout << "Edge added: " << source << " -> " << dest << " with weight " << weight << endl;
}

    // Print the adjacency matrix (optional)
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << graph[i][j] << "\t";
            }
        }
        cout << endl;
    }

    // Compute and print the shortest distance from node 0 to all other nodes
    shortestDist(graph, N);

    // Free the dynamically allocated memory
    for (int i = 0; i < N; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
