//
// Created by Pelikán on 21.10.2020.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <stdlib.h>
#include <stdio.h>

/**
 *
 */
typedef struct _bst_node {
    int key;
    struct _bst_node *left;
    struct _bst_node *rigth;
} bst_node;

int bst_add(bst_node **root, int key);

void bst_print(bst_node *root);

void bst_free(bst_node **root);

int bst_size(bst_node *root);

int bst_dsize(bst_node *root);

#endif //BST_BST_H
