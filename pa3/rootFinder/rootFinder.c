#include <stdlib.h>
#include <stdio.h>
#include <float.h>

double fabs(double value) {
    return value < 0.0 ? -value : value;
}

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    double x;
    fscanf(fp, "%lf", &x);

    size_t n;
    fscanf(fp, "%ld", &n);

    double precision;
    fscanf(fp, "%lf", &precision);

    double guess_r_max = x < 1.0 ? 1.0 : x;
    double guess_r_min = 0.0;
    double guess_r = (guess_r_max + guess_r_min) / 2.0;

    double guess_r_old = guess_r;
    double error = DBL_MAX;

    while (precision < fabs(error)) {
        double r_n = 1.0;
        for (size_t i = 1; i <= n; ++i) {
            r_n *= guess_r;
        }
        double fx = r_n - x;
        if (fx == 0.0) {
            break;
        }
        if (fx < 0.0) {
            guess_r_min = guess_r;
        } else {
            guess_r_max = guess_r;
        }
        guess_r_old = guess_r;
        guess_r = (guess_r_max + guess_r_min) / 2.0;
        error = guess_r - guess_r_old;
    }

    printf("%.*f\n", DBL_DIG, guess_r);

    return EXIT_SUCCESS;
}
