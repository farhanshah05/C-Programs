#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define EXP_SZ 8
#define FRAC_SZ 23


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // Reading the  binary representation (floating point number)
    char buff;
    unsigned int binary = 0;
    for (int i = EXP_SZ + FRAC_SZ; i >= 0; i--) {
        if (fscanf(fp, "%c", &buff) != 1) {
            fprintf(stderr, "Error reading file.\n");
            return EXIT_FAILURE;
        }
        if (buff == '1') {
            binary |= 1 << i;
        }
    }
    fclose(fp);

    // (important step )Extract sign, exponent, and mantissa
    int sign = (binary >> 31) & 1;
    int exponent = (binary >> FRAC_SZ) & 0xff;
    int mantissa = binary & 0x7fffff;

    // Convertion
    int true_exp = exponent - 127;

    // Print Value of FPN
    double m = 1.0 + (double)mantissa / (1 << FRAC_SZ);
    double number = ldexp(m, true_exp);
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;
}
