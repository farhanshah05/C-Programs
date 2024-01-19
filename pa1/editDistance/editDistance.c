#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min ( size_t x, size_t y, size_t w ) {
    if(x <= y && x <=w ){
        return x;
    }
    else if (y <= x && y <= w){
        return y;
    }
    else{
        return w;
    }
}
size_t levenshtein_recursive(char* source, char* target) {
    int soLen = strlen(source);
    int taLen = strlen(target);

    int matrix[taLen + 1][soLen + 1];
    for (int i = 0; i <= taLen; i++) {
        matrix[i][0] = i;
    }
    for (int j = 0; j <= soLen; j++) {
        matrix[0][j] = j;
    }
    for (int row = 1; row <= taLen; ++row) {
        for (int col = 1; col <= soLen; ++col) {
            if (target[row - 1] == source[col - 1]) {
                matrix[row][col] = matrix[row - 1][col - 1];
            } else {
                matrix[row][col] = min(matrix[row][col - 1], matrix[row - 1][col], matrix[row - 1][col - 1]) + 1;
            }
        }
    }
    return matrix[taLen][soLen];
}


int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf (inputFile, "%s\n%s", source, target);

    printf("%ld\n", levenshtein_recursive ( source, target ));

    return EXIT_SUCCESS;

}

