#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* file_pointer = fopen(argv[1], "r");
    if (!file_pointer) {
        perror("Error: Failed to open file");
        return EXIT_FAILURE;
    }

    int decimal_number;
    fscanf(file_pointer, "%d", &decimal_number);

    unsigned short binary_number;
    if (decimal_number >= 0) {
        binary_number = decimal_number;
    } else {
        binary_number = ((unsigned short)-decimal_number - 1) ^ 0xFFFF;
    }

    char hexadecimal[5] = "0000";
    for (int value1 = 0; value1 < 4; value1++) {
        int value1_value = (binary_number >> (3 - value1) * 4) & 0xF;
        if (value1_value < 10) {
            hexadecimal[value1] = value1_value + '0';
        } else {
            hexadecimal[value1] = value1_value - 10 + 'A';
        }
    }

    printf("%s\n", hexadecimal);

    fclose(file_pointer);
    return EXIT_SUCCESS;
}
