#include <iostream>
#include <limits>
#include <vector>

#define INF std::numeric_limits<int>::max()

using namespace std;

class AdjacencyMatrix {
private:
    vector<vector<int> > matrix;  // Use vector for better memory management
    int node_count;

public:
    // Constructor to initialize the matrix and node count
    AdjacencyMatrix(int nodes_count) : node_count(nodes_count) {
        matrix.resize(node_count, vector<int>(node_count, INF));
        for (int i = 0; i < node_count; ++i) {
            matrix[i][i] = 0;  // Distance to self is 0
        }
    }

    // Function to add an edge with a specific weight
    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < node_count && v >= 0 && v < node_count) {
            if (weight < 0) {
                cout << "Error: Negative weights are not allowed." << endl;
                return;
            }
            if (weight < matrix[u][v]) {  // Update only if the new weight is less
                matrix[u][v] = weight;
            }
        } else {
            cout << "Error: Node indices out of bounds." << endl;
        }
    }

    // Function to get the weight of an edge
    int get_edge(int u, int v) const {
        return matrix[u][v];
    }

    // Function to print the adjacency matrix
    void print_matrix() const {
        for (int i = 0; i < node_count; ++i) {
            for (int j = 0; j < node_count; ++j) {
                if (matrix[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << matrix[i][j] << ' ';
                }
            }
            cout << endl;
        }
    }

    friend class GraphAlgorithms;
};

class GraphAlgorithms {
public:
    // Function to find the minimum distance vertex
    static int Min_Distance(const vector<int>& dist, const vector<bool>& visited, int V) {
        int min = INF, min_index = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    // Dijkstra's Algorithm
    static void Dijkstra_Algorithm(const AdjacencyMatrix& graph, int source) {
        int V = graph.node_count;
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);

        dist[source] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = Min_Distance(dist, visited, V);
            visited[u] = true;

            for (int v = 0; v < V; ++v) {
                if (!visited[v] && graph.get_edge(u, v) != INF && dist[u] != INF &&
                    dist[u] + graph.get_edge(u, v) < dist[v]) {
                    dist[v] = dist[u] + graph.get_edge(u, v);
                }
            }
        }

        cout << "Shortest Distance from vertex " << source << ":\n";
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
            }
    }

    // Bellman-Ford Algorithm
    static void BellmanFord_Algorithm(const AdjacencyMatrix& graph, int V, vector<int>& dist) {
        dist.assign(V, INF);
        dist[0] = 0;

        for (int i = 0; i < V - 1; ++i) {
            for (int u = 0; u < V; ++u) {
                for (int v = 0; v < V; ++v) {
                    int weight = graph.get_edge(u, v);
                    if (weight != INF && dist[u] != INF && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
    }

    static void JohnsonAlgorithm(AdjacencyMatrix& graph) {
        int V = graph.node_count;
        vector<int> altered_weights(V);
        BellmanFord_Algorithm(graph, V, altered_weights);

        AdjacencyMatrix altered_graph(V);

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                int weight = graph.get_edge(i, j);
                if (weight != INF) {
                    altered_graph.add_edge(i, j, weight + altered_weights[i] - altered_weights[j]);
                }
            }
        }

        cout << "Modified Graph (after re-weighting):\n";
        altered_graph.print_matrix();

        for (int source = 0; source < V; ++source) {
            cout << "\nShortest Distance with vertex " << source << " as the source:\n";
            Dijkstra_Algorithm(altered_graph, source);
        }
    }
};

// Main function to run the algorithms
int main() {
    int num_nodes;
    cout << "Enter the number of nodes: ";
    cin >> num_nodes;

    AdjacencyMatrix graph(num_nodes);

    int num_edges;
    cout << "Enter the number of edges: ";
    cin >> num_edges;

    for (int i = 0; i < num_edges; ++i) {
        int u, v, weight;
        cout << "Enter source node, destination node, and weight for edge " << i + 1 << ": ";
        cin >> u >> v >> weight;
        graph.add_edge(u, v, weight);
    }

    GraphAlgorithms::JohnsonAlgorithm(graph);

    return 0;
}