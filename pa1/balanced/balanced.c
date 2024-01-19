#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold the close braces and the pointer to the next element.
struct element {
    char close;
    struct element* next;
};

// Append the new element to the start of the stack
struct element* push (struct element* stack, char close) {
    struct element* n_element = (struct element*) malloc(sizeof(struct element));
    n_element->close = close;
    n_element->next = stack;
    return n_element;
}

// Remove element from the top of the stack
char pop ( struct element** stack ) {
    struct element* count = *stack;
    if (count != NULL) {
        char close = count->close;
        *stack = count->next;
        free(count);
        return close;
    } else {
        return '\0';
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element* root = NULL;
    bool balanced = true;

    char buff;
    while ( fscanf(fp, "%c", &buff)==1 ) {

        switch(buff) {
            case '<' :
                root = push(root, '>');
                break;
            case '(' :
                root = push(root, ')');
                break;
            case '[' :
                root = push(root, ']');
                break;
            case '{' :
                root = push(root, '}');
                break;
            case '>' :
                if (pop(&root) != '>') {
                    balanced = false;
                }
                break;
            case ')' :
                if (pop(&root) != ')') {
                    balanced = false;
                }
                break;
            case ']' :
                if (pop(&root) != ']') {
                    balanced = false;
                }
                break;
            case '}' :
                if (pop(&root) != '}') {
                    balanced = false;
                }
                break;
            default :
                printf("Invalid character\n" );
        }
    }

    if (root != NULL) {
        balanced = false;
    }

    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
