#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
int main() {
    bst_node *tree = NULL;
    int i;

    for (i = 0; i < 10; i++){
        bst_add(&tree, i);
    }

        bst_print(tree);
        printf("\n");

        printf("Velikost bst je %d \n", bst_size(tree));
        printf("DSize bst je %d", bst_dsize(tree));

        bst_free(&tree);



    return 0;
}
