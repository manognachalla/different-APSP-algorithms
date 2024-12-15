#include <iostream>

using namespace std;

const int MAX_NODES = 100000;
const int INF = 1000000; // A large value to represent infinity

// Define graph as adjacency list
struct Edge {
    int weight;
    int node;
    Edge* next;
};

struct Node {
    Edge* head;
};

Node nodes[MAX_NODES];
int distances[MAX_NODES];
bool inQueue[MAX_NODES];
int nodeCount;

// Queue implemented using an array with front and back pointers
struct Queue {
    int arr[MAX_NODES];
    int front, back;
    
    Queue() : front(0), back(0) {}
    
    bool isEmpty() {
        return front == back;
    }

    void pushFront(int value) {
        if (front == 0) front = MAX_NODES;
        arr[--front] = value;
    }

    void pushBack(int value) {
        arr[back++] = value;
        if (back == MAX_NODES) back = 0;
    }

    int popFront() {
        int value = arr[front++];
        if (front == MAX_NODES) front = 0;
        return value;
    }
};

void addEdge(int u, int v, int weight) {
    Edge* newEdge = new Edge{weight, v, nodes[u].head};
    nodes[u].head = newEdge;

    newEdge = new Edge{weight, u, nodes[v].head}; // Since it's an undirected graph
    nodes[v].head = newEdge;
}

void initializeDistances(int source) {
    for (int i = 0; i < nodeCount; ++i) {
        distances[i] = INF;
        inQueue[i] = false;
    }
    distances[source] = 0;
}

void desopoPape(int source) {
    Queue q;
    q.pushBack(source);
    inQueue[source] = true;

    while (!q.isEmpty()) {
        int u = q.popFront();
        inQueue[u] = false;

        for (Edge* e = nodes[u].head; e != nullptr; e = e->next) {
            int v = e->node;
            int weight = e->weight;
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                if (!inQueue[v]) {
                    if (distances[v] == INF) {
                        q.pushBack(v);
                    } else {
                        q.pushFront(v);
                    }
                    inQueue[v] = true;
                }
            }
        }
    }
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodeCount;

    cout << "Enter the number of edges: ";
    int edgeCount;
    cin >> edgeCount;

    cout << "Enter the edges (format: node1 node2 weight):\n";
    for (int i = 0; i < edgeCount; ++i) {
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        addEdge(node1, node2, weight);
    }

    cout << "Enter the source node: ";
    int source;
    cin >> source;

    initializeDistances(source);
    desopoPape(source);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < nodeCount; ++i) {
        cout << "Distance to node " << i << ": ";
        if (distances[i] == INF) {
            cout << "unreachable";
        } else {
            cout << distances[i];
        }
        cout << endl;
    }

    return 0;
}
