import random

def generate_adjacency_matrix(n):
    # Create an empty adjacency matrix with 'INF' (using -1 to represent no path)
    INF = -1
    matrix = [[INF] * n for _ in range(n)]
    
    # Ensure that diagonal elements are 0 (distance from a node to itself is always 0)
    for i in range(n):
        matrix[i][i] = 0
    
    # Randomly generate edges with random weights between 1 and 10
    for i in range(n):
        for j in range(n):
            if i != j:
                # Randomly decide if there is an edge (with probability 0.3)
                if random.random() < 0.3:
                    matrix[i][j] = random.randint(1, 10)  # Edge weight between 1 and 10
    
    return matrix

def save_adjacency_matrix_to_file(matrix, filename):
    with open(filename, 'w') as file:
        # Write the number of nodes as the first line
        n = len(matrix)
        file.write(f"{n}\n")
        
        # Write each row of the adjacency matrix
        for row in matrix:
            file.write(" ".join(map(str, row)) + "\n")

def generate_input_for_100_nodes():
    n = 5000  # Number of nodes
    matrix = generate_adjacency_matrix(n)
    save_adjacency_matrix_to_file(matrix, "5000.ip")

# Generate the input and save it to 'sample_input.op'
generate_input_for_100_nodes()