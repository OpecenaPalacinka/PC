/**
 * @file dec2bin.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 
 * 
 */
#define APP_USAGE "Pouziti: dec2bin <pozitivni-hodnota>\n"
#define MAX_OUTPUT_LENGTH 32

int main(int argc, char *argv[]){
    char bin_out[MAX_OUTPUT_LENGTH] = { 0 };
    int dec,i;

    /** kontrola, jestli uživatel zadal parametr*/
    if(argc < 2){
        printf(APP_USAGE);
        return EXIT_FAILURE;
    }
    /* Převod řetězce na celé číslo a zkontrolovali jsme, že je <=0.*/
    dec = atoi(argv[1]);
    if(dec <= 0){
        printf(APP_USAGE);
        return EXIT_FAILURE;
    }

    printf("%d(d) =", dec);
    i = 0;
    while (dec != 0)
    {
        bin_out[i] = dec % 2 + '0';
        dec /= 2;
        i++; 
    }
    
    for(i--; i >= 0; i--){
        printf("%c",bin_out[i]);
    }

    return EXIT_SUCCESS;
}