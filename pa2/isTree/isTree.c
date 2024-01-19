#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to determine whether an undirected graph is a tree

// A recursive function that returns true if no cycles found
bool isTreeDFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    graphNode_t parent,
    graphNode_t current
) {

    // First see if current node has already been visited, indicating a cycle found
    if (visited[current]) {
        return false;
    }

    // Current node was not already visited, so now mark it as visited
    visited[current] = true;

    // Now iterate through each of the neighboring graph nodes
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if (neighbor->graphNode!=parent) {
            // If the neighbor nodes is not the parent node (the node from which we arrived at current), call DFS
            if (!isTreeDFS(graphNodeCount, adjacencyList, visited, current, neighbor->graphNode)) {
                return false;
            }
        }
        neighbor = neighbor->next;
    }

    // All DFS searches from current node found no cycles, so graph is a tree from this node
    return true;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    // Array of boolean variables indicating whether graph node has been visited
    bool* visited = calloc ( graphNodeCount, sizeof(bool) );
    
    // Call DFS starting from every unvisited node to check if there are any cycles in the graph
    bool iTree = true;
    for (graphNode_t node = 0; node < graphNodeCount; ++node) {
        if (!visited[node]) {
            iTree &= isTreeDFS(graphNodeCount, adjacencyList, visited, node, node);
        }
    }

    printf(iTree ? "yes" : "no");

    // Free allocated memory for adjacency list and visited nodes
    freeAdjList(graphNodeCount, adjacencyList);
    free(visited);

    return EXIT_SUCCESS;
}
