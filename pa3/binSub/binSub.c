#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // First, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[CHAR_BIT];
    for (int i = CHAR_BIT - 1; 0 <= i; i--) {
        if (fscanf(fp, " %c", &buff) != 1) {
            perror("fscanf failed");
            return EXIT_FAILURE;
        }
        minuend[i] = buff - '0';
    }

    // Second, read the subtrahend (number to subtract)
    bool subtrahend[CHAR_BIT];
    for (int i = CHAR_BIT - 1; 0 <= i; i--) {
        if (fscanf(fp, " %c", &buff) != 1) {
            perror("fscanf failed");
            return EXIT_FAILURE;
        }
        subtrahend[i] = buff - '0';
    }

    fclose(fp);

    // Negate the subtrahend by flipping all bits and adding one
    bool carry = true;
    for (int i = 0; i < CHAR_BIT; i++) {
        subtrahend[i] = !subtrahend[i];
        bool sum = subtrahend[i] ^ carry;
        carry = subtrahend[i] & carry;
        subtrahend[i] = sum;
    }

    // Add the minuend and the negated subtrahend
    carry = false;
    bool difference[CHAR_BIT];
    for (int i = 0; i < CHAR_BIT; i++) {
        bool sum = minuend[i] ^ subtrahend[i] ^ carry;
        carry = (minuend[i] & subtrahend[i]) | (minuend[i] & carry) | (subtrahend[i] & carry);
        difference[i] = sum;
    }

    // Print the difference bit string
    for (int i = CHAR_BIT - 1; 0 <= i; i--) {
        printf("%d", difference[i]);
    }

    return EXIT_SUCCESS;
}
