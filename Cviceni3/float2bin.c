/**
 * @file float2bin.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdlib.h>
#include <stdio.h>

typedef union _f_i{
    float f;
    unsigned int i;
} f_i; 

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char *argv[]){
    f_i x;
    int i;

    if(sizeof(float) != sizeof(unsigned int)){
        printf("Fatal error!");
        return EXIT_FAILURE;
    }

    if (argc < 2){
        printf("Chyba\n");
        return EXIT_FAILURE;
    }

    x.f = atof(argv[1]);
    printf("%f(d) =", x.f);

    for (i = sizeof(unsigned int) * 8 + 1;i >= 0;i--){
        printf("%c", ((x.i >> i) & 1) + '0');
    }   
    printf("(b)\n");
    return EXIT_SUCCESS;
}