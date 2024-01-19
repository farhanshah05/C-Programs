#include <stdio.h>
#include <stdlib.h>
#include "../bstReverseOrder/bst.h"
#include "../queue/queue.h"

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

int main(int argc, char* argv[]) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while (fscanf(fp, "%d", &key) != EOF) {
        root = insert(root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front = NULL, .back = NULL };
    //enqueue address of queue and root
    enqueue(&queue, root);

    //create a while loop to print the key with conditions to check the left and right childs
    while (queue.front != NULL) {
        BSTNode* curr = dequeue(&queue);
        printf("%d\n ", curr->key);
        //check left child
        if (curr->l_child) {
            enqueue(&queue, curr->l_child);
        }
        //check right child
        if (curr->r_child) {
            enqueue(&queue, curr->r_child);
        }
    }

    // CLEAN UP MEMORY
    delete_bst(root);

    return EXIT_SUCCESS;
}
