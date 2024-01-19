#include "../graphutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

// Create variables
int n;
int visitNum[MAX_NODES];
int pth[MAX_NODES];
int pth_size;

// Adjacency list node
typedef struct _node {
    int dest;
    struct _node* next;
} Node;

// Adjacency list
typedef struct _adjList {
    Node* head;
} AdjList;

AdjList gph[MAX_NODES];

// Function to add edge to adjacency list
void addEdge(int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = gph[src].head;
    gph[src].head = newNode;
}

// Function to build adjacency list
void build_gph(const char* file_pth){
    FILE* fp = fopen(file_pth, "r");
    fscanf(fp, "%d", &n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int weight;
            fscanf(fp, "%d", &weight);
            if (weight != 0) {
                addEdge(i, j);
            }
        }
    }
    fclose(fp);
}

// DFS to search for cycles
bool dfs(int node){
    visitNum[node] = 1;
    pth[pth_size++] = node;

    Node* curr = gph[node].head;
    //insert while loop
    while (curr != NULL) {
        int dest = curr->dest;
        if (visitNum[dest] == 0) {
            if (dfs(dest)) {
                return true;
            }
        } else if (visitNum[dest] == 1) {
            int start = 0;
            while (pth[start] != dest) {
                start++;
            }
            printf("%d", pth[start]);
            for (int j = start+1; j < pth_size; j++){
                printf(" %d", pth[j]);
            }
            printf("\n");
            return true;
        }
        //current invoke
        curr = curr->next;
    }
    visitNum[node] = 2;
    //decrease size of path --
    pth_size--;
    return false;
}

// Find cycle method
void find_cycle(){
    for(int i = 0; i < n; i++){
        if (visitNum[i] == 0) {
            if (dfs(i)) {
                return;
            }
        }
    }
    //return type
    printf("GRAPH\n");
}
//process for main
int main ( int argc, char* argv[] ) {
    if(argc < 2){
        fprintf(stderr, "Usage: %s input_file\n ", argv[0]);
        return 1;
    }
    build_gph(argv[1]);
    find_cycle();
    return 0;
}
