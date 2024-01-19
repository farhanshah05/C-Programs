#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>


#define EXP_SZ 11
#define FRAC_SZ 52


int main(int argc, char *argv[]) {
    // SETUP
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }
    double value;
    fscanf(fp, "%lf", &value);
    if (isnan(value) || isinf(value)) {
        printf("NaN or infinity\n");
        return 0;
    }
    bool sign = signbit(value);
    printf("%d_",sign);
    double frac_num = sign ? -value : value;
    unsigned short exp = 0;
    if (frac_num != 0.0) {
        if (frac_num < 0.0) {
            printf("negative #\n");
            return 0;
        } else if (frac_num == INFINITY) {
            exp = (1 << EXP_SZ) - 1;
        } else {

            int exp_guess = 1023;
            while (frac_num < 1.0 || frac_num >= 2.0) {
                if (frac_num >= 2.0) {
                    frac_num /= 2.0;
                    exp_guess++;
                } else if (frac_num < 1.0) {
                    frac_num *= 2.0;
                    exp_guess--;
                }
            }
            exp = (unsigned short) exp_guess;
            frac_num -= 1.0; 
        }
    } else {
        printf("%011d_", 0);
        for (int i = 0; i < FRAC_SZ; i++) {
            printf("%d", 0);
        }
        return 0;
    }
    for (int exp_index = EXP_SZ - 1; exp_index >= 0; exp_index--) {
        bool exp_bit = 1 & (exp >> exp_index);
        printf("%d", exp_bit);
    }
    printf("_");
    bool frac_array[FRAC_SZ];
    for (int frac_index = FRAC_SZ - 1; frac_index >= 0; frac_index--) {
        int bit = (int) floor(frac_num * 2.0);
        frac_array[frac_index] = bit;
        frac_num = frac_num * 2.0 - bit;
    }
    for (int frac_index = FRAC_SZ - 1; frac_index >= 0; frac_index--) {
        bool frac_bit = frac_array[frac_index];
        printf("%d", frac_bit);
    }
    return 0;
}
