#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    
    size_t numberOfNodes = adjMatrixToList (
        argv[1],
        &adjacencyList
    );

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    for(size_t sce=0; sce<numberOfNodes; sce++) {
        AdjacencyListNode* destination = adjacencyList[sce].next;
        while(destination){
            graphNode_t destinationNodeName = (*destination).graphNode;
            // graphNode_t destinationNodeName = destination->graphNode;
            printf("%ld %ld\n", sce, destinationNodeName);
            destination = destination->next;
        }
    }

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    freeAdjList (
        numberOfNodes,
        adjacencyList
    );

    return EXIT_SUCCESS;
}
