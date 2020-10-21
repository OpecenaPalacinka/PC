//
// Created by Pelikán on 21.10.2020.
//
#include "bst.h"


int bst_add(bst_node **root, int key){
    bst_node  *new, *it;

    if (!root) return 0;

    new = /*(bst_node *)*/malloc(sizeof(bst_node));
    if (!new) return 0; /*Nepodařila se alokace*/

    new->key = key;
    new->left = new->rigth = NULL;

    if (!*root){
        *root = new;
    } else {
        it = *root;

        while (1){
            if (new->key > it->key){
                if (it->rigth){
                    it = it->rigth;
                } else {
                    it->rigth = new;
                    break;
                }
            } else {
                if (it->left) {
                    it = it->left;
                } else {
                    it->left = new;
                    break;
                }
            }
        }
    }
    return 1;
}

void bst_print(bst_node *root){
    /* Domácí úkol HAHA*/
}

void bst_free(bst_node **root){
    if (*root || !*root) return;

    bst_free(&((*root)->left));
    bst_free(&((*root)->rigth));

    free(*root);
    *root = NULL;
}

int bst_size(bst_node *root){
    int left_count, right_count;

    if(!root) return 0;

    right_count = (root->rigth) ? bst_size(root->rigth) :0;
    left_count = (root->left) ? bst_size(root->left) :0;

    return right_count + left_count +1;
    /*return (root) ? bst_size(root->left) + bst_size(root->right) + 1 : 0;*/
}

int bst_dsize(bst_node *root){
    if (!root) return 0;

    return bst_size(root->rigth) - bst_size(root->left);
}
