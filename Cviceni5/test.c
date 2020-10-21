//
// Created by Pelikán on 21.10.2020.
//
#include <stdlib.h>
#include <stdio.h>

int main() {
    int i = 5;
    int j = 5;

    /*printf(" i = %d, j = %d", i,j);*/

    /* i = 5
    i = i++;
    printf("i = i++ -> i = %d",i);
    */

    /* i = 6
    i = ++i;
    printf("%d",i);
    */

    /* NeNeNe
    if (i++ == ++i){
        printf("Dobrý bráško");
    } else {
        printf("NeNeNe");
    }
    */
    /* i == 0 nebo i == -něco FALSE a i == +něco TRUE
    if (i++ && ++i){
        printf("Dobrý bráško");
    } else {
        printf("NeNeNe");
    }
    */

    return EXIT_SUCCESS;
}
