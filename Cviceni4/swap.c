#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Prohodí hodnoty dvou zadaných proměnných typnu int.
 */
void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int cislo_1 = 5, cislo_2 = 10;
    int *pointer_na_cislo;
    int **pointer_na_pointer_na_cislo;

    /* & zjišťuje adresu*/
    pointer_na_pointer_na_cislo = &pointer_na_cislo;

    printf("cislo_1 = %d, cislo_2 = %d", cislo_1,cislo_2);
    swap(&cislo_1,&cislo_2);
    printf("cislo_1 = %d, cislo_2 = %d", cislo_1, cislo_2);


    return EXIT_SUCCESS;
}