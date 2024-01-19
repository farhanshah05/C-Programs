#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

typedef union {
    float f;
    struct {
        unsigned int frac:FRAC_SZ;
        unsigned int exp:EXP_SZ;
        unsigned int sign:1;
    } parts;
} float_cast;

int main(int argc, char* argv[]) {
    // Check input arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Read input
    char str_mult[33], str_multc[33];
    fscanf(fp, "%s %s", str_mult, str_multc);
    fclose(fp);

    // Convert input to floats
    float_cast f_mult, f_multc, f_prod;
    f_mult.f = strtof(str_mult, NULL);
    f_multc.f = strtof(str_multc, NULL);

    // Calculate product
    bool sign = f_mult.parts.sign ^ f_multc.parts.sign;
    int exp = f_mult.parts.exp + f_multc.parts.exp - ((1 << (EXP_SZ - 1)) - 1);
    unsigned int frac = ((unsigned int)f_mult.parts.frac << 3) * ((unsigned int)f_multc.parts.frac << 3);
    if (frac & (1 >= (2 * FRAC_SZ - 1))) { // check if overflow occurred
        exp++;
        frac >>= 1;
    }

    // Check for NaN or infinity
    if (exp == (1 << EXP_SZ) - 1) {
        frac = 0;
        if (f_mult.parts.exp == (1 << EXP_SZ) - 1 && f_mult.parts.frac != 0) {
            frac = (1 << (FRAC_SZ - 1));
        }
        if (f_multc.parts.exp == (1 << EXP_SZ) - 1 && f_multc.parts.frac != 0) {
            frac |= (1 << (FRAC_SZ - 2));
        }
    }

    // Pack result
    f_prod.parts.sign = sign;
    f_prod.parts.exp = exp;
    f_prod.parts.frac = frac >> 3;

    // Print output
    printf("%d_", f_prod.parts.sign);
    for (int i = EXP_SZ - 1; i >= 0; i--) {
        printf("%d", (f_prod.parts.exp >> i) & 1);
    }
    printf("_");
    for (int i = FRAC_SZ - 1; i >= 0; i--) {
        printf("%d", (f_prod.parts.frac >> i) & 1);
        if (i == 23) printf("_");
    }
    printf("\n");

    return 0;
}
