#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../matMul/matMul.h"

unsigned int cost (
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes,
    unsigned int** M
) {
    if ( matrixCount == 1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {
        unsigned int numPossibleSplits = matrixCount - 1;
        unsigned int* costs = malloc(sizeof(unsigned int) * numPossibleSplits);


        for ( unsigned int split = 0; split < numPossibleSplits; split++ ) {
            unsigned int l = rowSizes[split];
            unsigned int m = colSizes[split];
            unsigned int r = colSizes[split + 1];


            if ( M[l][r] == 0 ) {
                M[l][r] = cost( split + 1, rowSizes, colSizes, M ) + cost( matrixCount - split - 1, &rowSizes[split + 1], &colSizes[split + 1], M ) + l * m * r;
            }


            costs[split] = M[l][r];
        }


        unsigned int minCost = costs[0];
        for ( unsigned int split = 1; split < numPossibleSplits; split++ ) {
            if ( costs[split] < minCost ) {
                minCost = costs[split];
            }
        }


        free(costs);
        return minCost;
    }
}


int main(int argc, char const *argv[]) {
    assert( argc == 2 );


    FILE* f = fopen( argv[1], "r" );
    assert( f );


    unsigned int matrixCount;
    if (fscanf( f, "%u", &matrixCount ) != 1) {
        fprintf(stderr, "Error: Invalid input file format\n");
        exit(EXIT_FAILURE);
    }

    unsigned int rowSizes[matrixCount];
    unsigned int colSizes[matrixCount];
    unsigned int** matrices = malloc( sizeof( unsigned int* ) * matrixCount );


    for ( unsigned int i = 0; i < matrixCount; i++ ) {
        unsigned int r, c;
        if (fscanf( f, "%u %u", &r, &c ) != 2) {
            fprintf(stderr, "Error: Invalid input file format\n");
            exit(EXIT_FAILURE);
        }
        rowSizes[i] = r;
        colSizes[i] = c;


        matrices[i] = malloc( sizeof( unsigned int ) * r * c );


        for ( unsigned int j = 0; j < r; j++ ) {
            for ( unsigned int k = 0; k < c; k++ ) {
                if (fscanf( f, "%u", &matrices[i][j * c + k] ) != 1) {
                    fprintf(stderr, "Error: Invalid input file format\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    fclose(f);


    // Initialize M matrix with 0s.
    unsigned int** M = malloc( sizeof( unsigned int* ) * matrixCount);
    for ( unsigned int i = 0; i < matrixCount; i++ ) {
    M[i] = calloc( matrixCount, sizeof( unsigned int ) );
    }
    // Calculate the minimum cost of multiplying the matrices.
    unsigned int minCost = cost( matrixCount, rowSizes, colSizes, M );


    // Print the result.
    printf( "%u\n", minCost );


    // Free memory.
    for ( unsigned int i = 0; i < matrixCount; i++ ) {
        free( matrices[i] );
        free( M[i] );
    }
    free( matrices );
    free( M );


    return 0;
}
